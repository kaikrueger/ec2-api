/*
 * @file   DescribeSecurityGroupsResponse.hpp
 *  @date   2011-09-07
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

/** Parsed ec2 DescribeSecurityGroupsResponse
 * see
http://docs.amazonwebservices.com/AWSEC2/latest/APIReference/index.html?ApiReference-query-DescribeSecurityGroups.html
 **/

#ifndef _DescribeSecurityGroupsResponse_hpp_
#define _DescribeSecurityGroupsResponse_hpp_
#include <vector>

#include <ec2-api/parse/types.hpp>

#include <ec2-api/parse/type/securityGroupInfo.hpp>

namespace ec2 {
  namespace xml {
  namespace parse {
    namespace type {

      struct DescribeSecurityGroupsResponse_t {
      private:
        std::string _requestId;
        std::vector<securityGroupInfo_t> _securityGroupInfo;
  
      public:
        DescribeSecurityGroupsResponse_t() {}
        const std::string &requestId() const { return _requestId; }
        const std::vector<securityGroupInfo_t> securityGroupInfo() const { return _securityGroupInfo; }
        

        void requestId(const std::string &v) { _requestId = v; }
        void securityGroupInfo(const securityGroupInfo_t&v) { _securityGroupInfo.push_back(v); }
        
        const std::string toString() const {
          std::ostringstream oss;
          oss << "<DescribeSecurityGroupsResponse>\n"
              << "  <requestId>" << requestId() << "</requestId>\n"
            ;
          oss << "    <securityGroupInfo> " << _securityGroupInfo.size() << "\n";
          for ( std::vector<securityGroupInfo_t>::const_iterator item (_securityGroupInfo.begin())
                    ; item != _securityGroupInfo.end()
                    ; ++item
                  ) {
            oss<< "      <item>\n" << *item << "      </item>\n";
          }
          oss << "    </securityGroupInfo>\n"
              << "</DescribeSecurityGroupsResponse>\n"
            ;
           return oss.str();
          }
        };
        // ******************************************************************* //
        inline
        std::ostream & operator << (std::ostream &s, const DescribeSecurityGroupsResponse_t &l) {
          s<< l.toString();
          return s;
        }


      } // namespace type
  } // namespace parse
  } // namespace xml
} // namespace ec2
#endif /* _DescribeSecurityGroupsResponse_hpp_ */
