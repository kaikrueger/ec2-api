/*
 * @file   ipPermissions.hpp
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


#ifndef _ipPermissions_hpp_
#define _ipPermissions_hpp_
#include <ec2-api/parse/types.hpp>

namespace ec2 {
  namespace xml {
  namespace parse {
    namespace type {

      struct ipPermissions_t {
        private:
        std::string _ipProtocol;
        std::string _fromPort;
        std::string _toPort;
        std::string _groups;
        std::string _ipRanges;
        
      public:
        ipPermissions_t() {}
        const std::string &ipProtocol() const { return _ipProtocol; }
        const std::string &fromPort() const { return _fromPort; }
        const std::string &toPort() const { return _toPort; }
        const std::string &groups() const { return _groups; }
        const std::string &ipRanges() const { return _ipRanges; }

        void ipProtocol(const std::string& v)    { _ipProtocol = v; }     
        void fromPort(const std::string& v)    { _fromPort = v; }     
        void toPort(const std::string& v)    { _toPort = v; }     
        void groups(const std::string& v)    { _groups = v; }     
        void ipRanges(const std::string& v)    { _ipRanges = v; }     

        const std::string toString() const {
          std::ostringstream oss;
          oss << "          <ipProtocol>" << ipProtocol() << "</ipProtocol>" << std::endl
             << "          <fromPort>" << fromPort() << "</fromPort>" << std::endl
             << "          <toPort>" << toPort() << "</toPort>" << std::endl
             << "          <groups>" << groups() << "</groups>" << std::endl
             << "          <ipRanges>" << ipRanges() << "</ipRanges>" << std::endl
            ;
          
          return oss.str();
          }
        };

        // ******************************************************************* //
        inline
        std::ostream & operator << (std::ostream &s, const ipPermissions_t &l) {
          s<< l.toString();
          return s;
        }


      } // namespace type
  } // namespace parse
  } // namespace xml
} // namespace ec2
#endif /* _ipPermissions_hpp_ */
