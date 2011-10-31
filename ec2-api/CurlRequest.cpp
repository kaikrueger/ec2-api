/*
 * @file CurlRequest.cpp
 * @date   2011-08-10
 *
 * Created by Kai Krueger <kai.krueger@itwm.fraunhofer.de>
 *
 * Copyright (c) 2011 Fraunhofer ITWM
 * All rights reserved.
 * 
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <string.h>
#include <iostream>
#include <exception>

#include <ec2-api/CurlRequest.hpp>
#include <ec2-api/CurlCallback.hpp>

#include <ec2-api/EC2Exception.hpp>

using namespace ec2;

CurlRequest::CurlRequest(
  const std::string &url
  , const std::string &proxy
  )
    : RequestCore(url, proxy)
    , _formpost(NULL) 
    , _lastptr(NULL)
    , _headerlist(NULL)
    , _bodyfile(NULL)
{}

CurlRequest::~CurlRequest() {
}

CURL *CurlRequest::prep_request(
  ec2::RequestObserver::Ptr observer
  )
{
  //Handle to the curl
  CURL *hCurl = curl_easy_init();
  if(NULL == hCurl) {
    throw false;
  }

  /* initalize custom header list (stating that Expect: 100-continue is not
     wanted */ 
  static const char buf[] = "Expect:";
  _headerlist = curl_slist_append(_headerlist, buf);

  /* what URL that receives this POST */ 
  curl_easy_setopt(hCurl, CURLOPT_URL, url().c_str());

  if( _formpost != NULL ) {
    curl_easy_setopt(hCurl, CURLOPT_HTTPPOST, _formpost);
  }
  
  memset(_errorBuffer, 0, sizeof(_errorBuffer));
  curl_easy_setopt(hCurl, CURLOPT_ERRORBUFFER , _errorBuffer);
  curl_easy_setopt(hCurl, CURLOPT_FAILONERROR, 0);
//CURLOPT_PROXY 
//CURLOPT_PROXYPORT 

  curl_easy_setopt(hCurl, CURLOPT_FILETIME, true);
  curl_easy_setopt(hCurl, CURLOPT_FRESH_CONNECT, false);
  curl_easy_setopt(hCurl, CURLOPT_CLOSEPOLICY, CURLCLOSEPOLICY_LEAST_RECENTLY_USED);
  curl_easy_setopt(hCurl, CURLOPT_MAXREDIRS, 5);
  curl_easy_setopt(hCurl, CURLOPT_HEADER, true);
  // //curl_easy_setopt(hCurl, CURLOPT_RETURNTRANSFER, true);
  curl_easy_setopt(hCurl, CURLOPT_TIMEOUT, 5184000);
  curl_easy_setopt(hCurl, CURLOPT_CONNECTTIMEOUT, 120);
  curl_easy_setopt(hCurl, CURLOPT_NOSIGNAL, true);

  //curl_easy_setopt(hCurl, CURLOPT_HEADERFUNCTION , &(ec2::CurlCallback::header_callback));
  //curl_easy_setopt(hCurl, CURLOPT_WRITEHEADER , response());

  curl_easy_setopt(hCurl, CURLOPT_WRITEFUNCTION , &(ec2::CurlCallback::write_callback));
  clear_response();
  curl_easy_setopt(hCurl, CURLOPT_WRITEDATA , response());

  // Debug mode
  curl_easy_setopt(hCurl, CURLOPT_DEBUGFUNCTION , &(ec2::CurlCallback::debug_callback));
  curl_easy_setopt(hCurl, CURLOPT_DEBUGDATA , observer.get());
  if (debug_mode()) {
    curl_easy_setopt(hCurl, CURLOPT_VERBOSE, true);
  } else {
    curl_easy_setopt(hCurl, CURLOPT_VERBOSE, false);
  }

  return hCurl;
}

void CurlRequest::send_request(
  ec2::RequestObserver::Ptr observer
  )
{
  CURL *hCurl = prep_request(observer);

  if(hCurl == NULL) {
    throw ec2::ConnectionException("Cannot get connection handle.");
  }
  
	CURLcode hResult;

  int header_size;
  hResult = curl_easy_perform(hCurl);
  
  if(CURLE_OK == hResult) {
    curl_easy_getinfo(hCurl, CURLINFO_HEADER_SIZE, &header_size); 
    const std::string resp ( response_data() );
    split_response(header_size);
  } else {
    std::ostringstream oss;
    oss << "Call failed: ["<< hResult << "] "<< _errorBuffer;
    
    observer->Logger(oss.str());
    observer->debug_callback(oss.str());
  }
  //observer->debug_callback(response()->body());
  
  curl_easy_cleanup(hCurl);
  hCurl = NULL;

  // written to file ? */
  if( _bodyfile != NULL) {
    fclose(_bodyfile);
    _bodyfile=NULL;
  }
  
  /* then cleanup the formpost chain */ 
  if(_formpost!=NULL) {
    curl_formfree(_formpost);
    _formpost=NULL;
  }

  /* free slist */ 
  if(_headerlist!=NULL) {
    curl_slist_free_all (_headerlist);
    _headerlist=NULL;
  }

  if(hResult !=CURLE_OK ) {
    throw ec2::ConnectionException(curl_easy_strerror(hResult));
  }

}

/*
 * Local variables:
 *  tab-width: 2
 *  c-indent-level: 2
 *  c-basic-offset: 2
 *  project-name: ec2-api
 * End:
 */
