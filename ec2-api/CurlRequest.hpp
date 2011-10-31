/*
 * @file CurlRequest.hpp
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

#ifndef _CurlRequest_hpp_
#define _CurlRequest_hpp_

#include <curl/curl.h>

#include <ec2-api/RequestCore.hpp>


namespace ec2 {
  class CurlRequest : public RequestCore, public enable_shared_from_this<CurlRequest> {
  public:
    typedef ec2::shared_ptr<CurlRequest> Ptr;

    CurlRequest(const std::string &url, const std::string &proxy);
    ~CurlRequest();

    CURL *prep_request(ec2::RequestObserver::Ptr);
    
    void send_request(ec2::RequestObserver::Ptr);
    
    private:
    
      // volatil
    char _errorBuffer[CURL_ERROR_SIZE];
    struct curl_httppost *_formpost;
    struct curl_httppost *_lastptr;
    struct curl_slist    *_headerlist;
    FILE *_bodyfile;
  };
} // namespace ec2
#endif /* _CurlRequest_hpp_ */

/*
 * Local variables:
 *  tab-width: 2
 *  c-indent-level: 2
 *  c-basic-offset: 2
 *  project-name: ec2-api
 * End:
 */
