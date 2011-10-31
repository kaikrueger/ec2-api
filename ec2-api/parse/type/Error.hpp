/*
 * @file   Error.hpp
 * @date   2011-09-06
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

/** Parsed ec2 Errors Response, subitem Error
 * see
 http://docs.amazonwebservices.com/fws/latest/DeveloperGuide/index.html?UnderstandingResponses.html
 http://docs.amazonwebservices.com/AmazonSimplePay/latest/ASPAdvancedUserGuide/index.html?ErrorResponse.html
 **/
/*---------------------------------------------------------------------*/

#ifndef _Error_hpp_
#define _Error_hpp_
namespace ec2 {
  namespace xml {
    namespace parse {
      namespace type {

        struct Error_t {
        private:
          std::string _code;
          std::string _message;

        public:
          Error_t() {}
          
          const std::string &code() const { return _code; }
          const std::string &message() const { return _message; }
          
          void code(const std::string &v) { _code = v; }
          void message(const std::string &v) { _message = v; }
          
          const std::string toString() const {
          std::ostringstream oss;
          oss << "<Error>\n"
              << "  <Code>" << code() << "</Code>\n"
              << "  <Message>" << message() << "</Message>\n"
              << "</Error>\n"
            ;
          return oss.str();
          }
        };

        // ******************************************************************* //
        inline
        std::ostream & operator << (std::ostream &s, const Error_t &l) {
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
#endif /* _Error_hpp_ */
