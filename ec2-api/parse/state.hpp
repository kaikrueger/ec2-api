/*
 * @file   state.hpp
 * @date   2010-07-15
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

#ifndef _xml_parse_state_hpp_
#define _xml_parse_state_hpp_
#include <iostream>

#include <list>
#include <deque>

#include <stdexcept>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>


namespace ec2 {
  namespace xml {
    namespace parse {
      namespace state {

        namespace fs = boost::filesystem;
        namespace po = boost::program_options;

        typedef std::vector<fs::path> search_path_type;
        typedef std::vector<fs::path> in_progress_type;

        // ******************************************************************* //
        struct type {
        private:
          int _level;
          search_path_type _search_path;
          in_progress_type _in_progress;
          bool _Werror;
          bool _Wunexpected_element;

          std::string _ns1;
          std::string _ns2;

          template<typename W>
          void generic_warn (const W & w, const bool & active) const {
            if (active)
            {
              if (_Werror)
              {
                throw w;
              }
              else
              {
                std::cerr << w.what() << std::endl;
              }
            }
          }

          fs::path expand (const std::string & file) const
            {
              fs::path direct (file);

              if (fs::exists (direct))
              {
                return direct;
              }

              for ( search_path_type::const_iterator dir (_search_path.begin())
                      ; dir != _search_path.end()
                      ; ++dir
                    )
              {
                if (! fs::exists (*dir))
                {
                  continue;
                }

                fs::path path (*dir / file);

                if (fs::exists (path))
                {
                  return path;
                }
              }

              throw error::file_not_found ("expand", file);
            }

        public:
          type(void) 
              : _Werror (false) 
              , _Wunexpected_element (true)
            {}

          void setNS1(const std::string &ns) { _ns1 = ns; }
          void setNS2(const std::string &ns) { _ns2 = ns; }
          
          const std::string ns1(const std::string &n) const { return _ns1+n; }
          const std::string ns2(const std::string &n) const { return _ns2+n; }
          
          // ***************************************************************** //
          void warn (const warning::unexpected_element & w) const {
            generic_warn (w, _Wunexpected_element);
          }

          // ***************************************************************** //

          template<typename T>
          T generic_include ( T (*parse)(std::istream &, type &)
                              , const std::string & file
                              )
            {
              const fs::path path (expand (file));

              for ( in_progress_type::const_iterator pos (_in_progress.begin())
                      ; pos != _in_progress.end()
                      ; ++pos
                    )
              {
                if (*pos == path)
                {
                  throw error::include_loop<in_progress_type::const_iterator>
                    ("generic_include", pos, _in_progress.end());
                }
              }

              _in_progress.push_back (path);

              std::ifstream stream (path.string().c_str());

              const T x (parse (stream, *this));

              _in_progress.pop_back ();

              return x;
            }

        };

      } // namesapce state
    } // namespace parse
  } // namespace xml
} // namespace ec2

#endif /* _xml_parse_state_hpp_ */

/*
 * Local variables:
 *  tab-width: 2
 *  c-indent-level: 2
 *  c-basic-offset: 2
 * End:
 */
