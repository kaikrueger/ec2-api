/*
 * @file   securityGroupInfo.hpp
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


#include <vector>

#include <ec2-api/parse/types.hpp>

#include <ec2-api/parse/type/ipPermissions.hpp>

namespace ec2 {
  namespace xml {
  namespace parse {
    namespace type {

      struct securityGroupInfo_t {
        private:
        std::string _ownerId;
        std::string _groupId;
        std::string _groupName;
        std::string _groupDescription;
        std::vector<ipPermissions_t> _ipPermissions;
        
      public:
        securityGroupInfo_t() {}
        const std::string &ownerId() const { return _ownerId; }
        const std::string &groupId() const { return _groupId; }
        const std::string &groupName() const { return _groupName; }
        const std::string &groupDescription() const { return _groupDescription; }
        const std::vector<ipPermissions_t> &ipPermissions() const { return _ipPermissions; }

        void ownerId(const std::string& v)  { _ownerId = v; }
        void groupId(const std::string& v)  { _groupId = v; }
        void groupName(const std::string& v)  { _groupName = v; }
        void groupDescription(const std::string& v)  { _groupDescription = v; }
        void ipPermissions(const ipPermissions_t& v)  { _ipPermissions.push_back(v); }
        

        const std::string toString() const {
          std::ostringstream oss;
          oss << "        <ownerId>" << ownerId() << "</ownerId>" << std::endl
              << "        <groupId>" << groupId() << "</groupId>" << std::endl
              << "        <groupName>" << groupName() << "</groupName>" << std::endl
              << "        <groupDescription>" << groupDescription() << "</groupDescription>" << std::endl
              << "        <ipPermissions>" << std::endl
            ;
          for ( std::vector<ipPermissions_t>::const_iterator item (_ipPermissions.begin())
                    ; item != _ipPermissions.end()
                    ; ++item
                  ) {
            oss<< "        <item>" << std::endl << *item << "        </item>\n";
          }
          oss << "    </ipPermissions>\n"
              << "    <ipPermissionsEgress/>" << std::endl
            ;
          return oss.str();
          }
        };

        // ******************************************************************* //
        inline
        std::ostream & operator << (std::ostream &s, const securityGroupInfo_t &l) {
          s<< l.toString();
          return s;
        }


      } // namespace type
  } // namespace parse
  } // namespace xml
} // namespace ec2
