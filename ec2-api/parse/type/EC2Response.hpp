/*
 * @file   EC2Response.hpp
 *  @date   2011-08-15
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

/** 
    Main ec2-response class, holding all implemented valid responses
 */
#ifndef _EC2Response_hpp_
#define _EC2Response_hpp_

#include <ec2-api/parse/types.hpp>

#include <boost/variant.hpp>

#include <ec2-api/parse/type/visitor_getter.hpp>

namespace ec2 {
  namespace xml {
  namespace parse {
    namespace type {

      struct EC2Response_t {
        public:
        typedef boost::variant <Response_t
                                , AuthorizeSecurityGroupIngressResponse_t
                                , CreateSecurityGroupResponse_t
                                , DescribeSecurityGroupsResponse_t
                                , DescribeImagesResponse_t
                                , DescribeInstancesResponse_t
                                , RunInstancesResponse_t
                                , TerminateInstancesResponse_t
                                > f_Response_t;
        
        EC2Response_t () :_isErrorResponse(false) {}
        const f_Response_t getResponse() const { return _response; }

        // getter
        const bool IsErrorResponse() const { return _isErrorResponse; }
        
        const Response_t Response() const {
          return boost::get<Response_t>(_response);
        }
        const AuthorizeSecurityGroupIngressResponse_t AuthorizeSecurityGroupIngressResponse() const {
          return boost::get<AuthorizeSecurityGroupIngressResponse_t>(_response);
        }
        const CreateSecurityGroupResponse_t CreateSecurityGroupResponse() const {
          return boost::get<CreateSecurityGroupResponse_t>(_response);
        }
        const DescribeSecurityGroupsResponse_t DescribeSecurityGroupsResponse() const {
          return boost::get<DescribeSecurityGroupsResponse_t>(_response);
        }
        const DescribeImagesResponse_t DescribeImagesResponse() const {
          return boost::get<DescribeImagesResponse_t>(_response);
        }
        const DescribeInstancesResponse_t DescribeInstancesResponse() const {
          return boost::get<DescribeInstancesResponse_t>(_response);
        }
        const RunInstancesResponse_t RunInstancesResponse() const {
          return boost::get<RunInstancesResponse_t>(_response);
        }
        const TerminateInstancesResponse_t TerminateInstancesResponse() const {
          return boost::get<TerminateInstancesResponse_t>(_response);
        }

        // setter
        void Response(const Response_t &v) { _isErrorResponse=true; _response = v; }
        void AuthorizeSecurityGroupIngressResponse(const AuthorizeSecurityGroupIngressResponse_t &v) { _response = v; }
        void CreateSecurityGroupResponse(const CreateSecurityGroupResponse_t &v) { _response = v; }
        void DescribeSecurityGroupsResponse(const DescribeSecurityGroupsResponse_t &v) { _response = v; }
        void DescribeImagesResponse(const DescribeImagesResponse_t &v) { _response = v; }
        void DescribeInstancesResponse(const DescribeInstancesResponse_t &v) { _response = v; }
        void RunInstancesResponse(const RunInstancesResponse_t &v) { _response = v; }
        void TerminateInstancesResponse(const TerminateInstancesResponse_t &v) { _response = v; }

        const std::string toString() const {
          std::ostringstream oss;
          oss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
          oss << getResponse()
            ;
          return oss.str();
          }
        
      private:
        f_Response_t   _response;
        bool           _isErrorResponse;
        int            _httpErrorCode;
        
      };

      // ******************************************************************* //
      inline
      std::ostream & operator << (std::ostream &s, const EC2Response_t &l) {
        s<< l.toString();
        return s;
      }
    } // namespace type
  } // namespace parse
  } // namespace xml
} // namespace ec2

/*
 * Local variables:
 *  tab-width: 2
 *  c-indent-level: 2
 *  c-basic-offset: 2
 * End:
 */
#endif /* _EC2Response_hpp_ */
