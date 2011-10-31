/*
 * @file   ResponseCore.hpp
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

#ifndef _ResponseCore_hpp_
#define _ResponseCore_hpp_

#include <sstream>

#include <ec2-api/shared_ptr.hpp>

namespace ec2 {
  class RequestCore;
  
  class ResponseCore {
  public:
    typedef ec2::shared_ptr<ResponseCore> Ptr;

    ResponseCore() : _header(""), _body(""){ clear_response(); };
    ~ResponseCore() {};
    
    const std::string get_response() { return _response_data; }
    const std::string body() const   { return _body; }
    const std::string header() const { return _header; }

    void clear_response() { _response_data.clear(); }
    void split_response(size_t n);
    
    // callbacks
    void header_callback(const std::string &data);
    void write_callback(const std::string &data);
    void debug_callback(const std::string &data);
    int  progress_callback(void *clientp, double dltotal, double dlnow
                           , double ultotal, double ulnow);

  protected:
    void response(const std::string &v) { _response_data = v; }
    
  private:
    std::string _response_data;
    std::string _header;
    std::string _body;
    
    
};
  
    
} // namespace ec2

#endif /* _ResponseCore_hpp_ */
