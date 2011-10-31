/*
 * @file   RequestCore.hpp
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


#ifndef _RequestCore_hpp_
#define _RequestCore_hpp_

#include <string>
#include <map>
#include <iterator>

#include <ec2-api/shared_ptr.hpp>

#include <ec2-api/ResponseCore.hpp>
#include <ec2-api/RequestObserver.hpp>

namespace ec2 {


  class RequestCore {
  public:
    typedef ec2::shared_ptr<RequestCore> Ptr;
    typedef std::map<const std::string, std::string>  MapType;
    typedef MapType::iterator        MapTypeIterator;
    typedef MapType::const_iterator  MapTypeConstIterator;

    RequestCore(const std::string &url, const std::string &proxy);
    virtual ~RequestCore();
    
    void add_header(const std::string &key, const std::string &value);
    void set_body(const std::string &body);
    void set_request_url(const std::string &url);
    
    virtual void send_request(ec2::RequestObserver::Ptr) = 0;
    
    const std::string response_data() const { return _response->get_response(); }
    const std::string response_body() const { return _response->body(); }
    const std::string response_header() const { return _response->header(); }

    void setDebug() { _debug_mode = 1; }
    void unsetDebug() { _debug_mode = 0; }
    
  protected:
    const bool debug_mode()    { return _debug_mode; }
    const std::string &url()   { return _url; };
    const std::string &proxy() { return _proxy; };
    const std::string &body()  { return _body; };
    ResponseCore *response()   { return _response.get(); }

    void clear_response()              { _response->clear_response(); }
    void split_response(size_t n)      { _response->split_response(n); }
    
  private:
    bool _debug_mode;
    
    std::string _url;
    std::string _proxy;
    std::string _body;
    
    MapType  _request_headers;
    
    ResponseCore::Ptr _response;

  };
    
} // namespace ec2
#endif /* _RequestCore_hpp_ */

/*
 * Local variables:
 *  tab-width: 2
 *  c-indent-level: 2
 *  c-basic-offset: 2
 *  project-name: ec2-api
 * End:
 */
