/*
 * @file   reservationSet.hpp
 *  @date   2011-08-11
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

#ifndef _reservationSet_hpp_
#define _reservationSet_hpp_

#include <vector>

#include <ec2-api/parse/types.hpp>

#include <ec2-api/parse/type/instancesSet.hpp>
#include <ec2-api/parse/type/groupSet.hpp>

namespace ec2 {
  namespace xml {
  namespace parse {
    namespace type {

      struct reservationSet_t {
        private:
        std::string _reservationId;
        std::string _ownerId; 
        std::vector<groupSet_t>  _groupSet; 
        std::vector<instancesSet_t>  _instancesSet; 
        
      public:
        typedef std::vector<reservationSet_t>::iterator        Iterator;
        typedef std::vector<reservationSet_t>::const_iterator  ConstIterator;
          reservationSet_t (){}
        const std::string&     reservationId() const { return _reservationId; }
        const std::string&     ownerId() const { return _ownerId; }
        const std::vector<groupSet_t> &groupSet() const { return _groupSet; }
        const std::vector<instancesSet_t> &instancesSet() const { return _instancesSet; }

        void reservationId(const std::string&v) { _reservationId = v; }
        void ownerId(const std::string&v) { _ownerId = v; }
        void instancesSet(const instancesSet_t& v) { _instancesSet.push_back(v); }
        void groupSet(const groupSet_t &v) { _groupSet.push_back(v); }
        
        const std::string toString() const {
          std::ostringstream oss;
          oss << "    <reservationId>" << reservationId() << "</reservationId>\n"
              << "    <ownerId>" << ownerId() << "</ownerId>\n"
              << "    <groupSet>\n"
            ;
          for ( std::vector<groupSet_t>::const_iterator item (_groupSet.begin())
                    ; item != _groupSet.end()
                    ; ++item
                  ) {
            oss<< "<item>" << *item << "</item>\n";
          }
          oss << "    </groupSet>\n";
          oss << "    <instancesSet> " << _instancesSet.size() << "\n";
          for ( std::vector<instancesSet_t>::const_iterator item (_instancesSet.begin())
                    ; item != _instancesSet.end()
                    ; ++item
                  ) {
            oss<< "      <item>\n    " << *item << "      </item>\n";
          }
          oss << "    </instancesSet>\n"
            ;
          return oss.str();
          }
        };

        // ******************************************************************* //
        inline
        std::ostream & operator << (std::ostream &s, const reservationSet_t &l) {
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
#endif /* _reservationSet_hpp_ */
