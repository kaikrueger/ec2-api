/*
 * @file CurlCallback.cpp
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

#include <string>
#include <iostream>

#include <ec2-api/CurlCallback.hpp>
#include <ec2-api/ResponseCore.hpp>
#include <ec2-api/RequestObserver.hpp>


using namespace ec2;

size_t CurlCallback::header_callback(
  char *ptr
  , size_t size
  , size_t nmemb
  , void *userdata 
  ) {
  const std::string data(ptr, nmemb);

  ResponseCore *resp = static_cast<ResponseCore*> (userdata);
  resp->header_callback(data);
  
  return size*nmemb;
}

size_t CurlCallback::write_callback(
  char *ptr
  , size_t size
  , size_t nmemb
  , void *userdata 
  ) {
  const std::string data(ptr, nmemb);

  ResponseCore *resp = static_cast<ResponseCore*> (userdata);
  resp->write_callback(data);
  
  return size*nmemb;
}

size_t CurlCallback::debug_callback(
  CURL *hCurl
  , curl_infotype infotype
  , char *info
  , size_t size
  , void *userdata 
  ) {
  const std::string data(info, size);
  RequestObserver *observer = static_cast<RequestObserver*> (userdata);
  observer->debug_callback(data);
  
  return 0;
}

int CurlCallback::progress_callback(
  void *clientp
  , double dltotal
  , double dlnow
  , double ultotal
  , double ulnow)
{
  return 0;
}

/*
 * Local variables:
 *  tab-width: 2
 *  c-indent-level: 2
 *  c-basic-offset: 2
 *  project-name: ec2-api
 * End:
 */
