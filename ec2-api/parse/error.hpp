/*
 * @file   error.hpp
 * @date   2011-10-17
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

#ifndef _xml_parse_error_hpp_
#define _xml_parse_error_hpp_

#include <stdexcept>
#include <string>
#include <sstream>

#include <boost/filesystem.hpp>

namespace ec2 {
  namespace xml {
    namespace parse {
      namespace error {
      // ******************************************************************* //

      class generic : public std::runtime_error
      {
      public:
        generic (const std::string & msg)
          : std::runtime_error ("ERROR: " + msg)
        {}

        generic (const std::string & msg, const std::string & pre)
          : std::runtime_error ("ERROR: " + pre + ": " + msg)
        {}
      };

      // ******************************************************************* //

      class unexpected_element : public generic
      {
      public:
        unexpected_element ( const std::string & name
                           , const std::string & pre
                           )
          : generic
        (pre + ": unexpected element with name " + util::quote(name))
        {}
      };

      // ******************************************************************* //

      class wrong_node : public generic
      {
      public:
        wrong_node ( const rapidxml::node_type & want
                   , const rapidxml::node_type & got
                   )
          : generic ("wrong node type"
                    , "expexted node of type "
                    + util::quote(util::show_node_type (want))
                    + ": got node of type "
                    + util::quote(util::show_node_type (got))
                    )
        {}

        wrong_node ( const rapidxml::node_type & want1
                   , const rapidxml::node_type & want2
                   , const rapidxml::node_type & got
                   )
          : generic ("wrong node type"
                    , "expexted node of type "
                    + util::quote(util::show_node_type (want1))
                    + " or "
                    + util::quote(util::show_node_type (want2))
                    + ": got node of type "
                    + util::quote(util::show_node_type (got))
                    )
        {}
      };

      class missing_node : public generic
      {
      public:
        missing_node (const rapidxml::node_type & want)
          : generic ( "missing node"
                    , "expected node of type "
                    + util::quote(util::show_node_type (want))
                    )
        {}

        missing_node ( const rapidxml::node_type & want1
                     , const rapidxml::node_type & want2
                     )
          : generic ( "missing node"
                    , "expected node of type "
                    + util::quote(util::show_node_type (want1))
                    + " or " 
                    + util::quote(util::show_node_type (want2))
                    )
        {}
      };

      // ******************************************************************* //

     class missing_attr : public generic
      {
      public:
        missing_attr ( const std::string & pre
                     , const std::string & attr
                     )
          : generic
            (pre + ": missing attribute " + util::quote(attr))
        {}
      };

      // ******************************************************************* //

      class no_elements_given : public generic
      {
      public:
        no_elements_given (const std::string & pre)
          : generic ("no elements given at all!?", pre)
        {}
      };

      // ******************************************************************* //

      class more_than_one_definition : public generic
      {
      public:
        more_than_one_definition (const std::string & pre)
          : generic ("more than one definition in one file", pre)
        {}
      };

      // ******************************************************************* //

      class top_level_anonymous_function : public generic
      {
      public:
        top_level_anonymous_function ( const std::string & file
                                     , const std::string & pre
                                     )
          : generic ( "try to include top level anonymous function from " 
                    + file
                    , pre
                    )
        {}
      };

      // ******************************************************************* //

      class file_not_found : public generic
      {
      public:
        file_not_found ( const std::string & pre
                       , const std::string & file
                       )
          : generic (pre, "file not found: " + file)
        {}
      };

      // ******************************************************************* //

      template<typename IT>
      class include_loop : public generic
      {
      private:
        std::string nice (IT pos, const IT & end) const
        {
          std::ostringstream ss;

          IT loop (pos);

          for  (; pos != end; ++pos)
            {
              ss << *pos << " -> ";
            }

          ss << *loop;

          return ss.str();
        }
        
      public:
        include_loop ( const std::string & pre
                     , IT pos, const IT & end
                     )
          : generic (pre, "include loop: " + nice (pos, end))
        {}
      };

      // ******************************************************************* //

      class cannot_resolve : public generic
      {
      private:
        std::string nice ( const std::string & field
                         , const std::string & type
                         , const boost::filesystem::path & path
                         ) const
        {
          std::ostringstream s;

          s << "cannot resolve " << field << " :: " << type
            << ", defined in " << path;

          return s.str();
        }
        
      public:
        cannot_resolve ( const std::string & field
                       , const std::string & type
                       , const boost::filesystem::path & path
                       )
          : generic (nice (field, type, path))
        {}
      };

      // ******************************************************************* //

      template<typename T>
      class struct_redefined : public generic
      {
      private:
        std::string nice (const T & early, const T & late) const
        {
          std::ostringstream s;

          s << "redefinition of struct with name " << late.name
            << " in " << late.path
            << ", first definition was in " << early.path
            ;

          return s.str();
        }

      public:
        struct_redefined (const T & early, const T & late)
          : generic (nice (early, late))
        {}
      };

      // ******************************************************************* //

      class place_type_unknown : public generic
      {
      private:
        std::string nice ( const std::string & place
                         , const std::string & type
                         , const boost::filesystem::path & path
                         ) const
        {
          std::ostringstream s;

          s << "unknown type " << type
            << " given to place " << place
            << " in " << path
            ;

          return s.str();
        }
      public:
        place_type_unknown ( const std::string & place
                           , const std::string & type
                           , const boost::filesystem::path & path
                           )
          : generic (nice (place, type, path))
        {}
      };

      // ******************************************************************* //

      class parse_lift : public generic
      {
      private:
        std::string nice ( const std::string & place
                         , const std::string & field
                         , const boost::filesystem::path & path
                         , const std::string & msg
                         ) const
        {
          std::ostringstream s;

          s << "when reading a value for place " << place;

          if (field != "")
            {
              s << " for field " << field;
            }

          s << " from "<< path
            << ": " << msg
            ;

          return s.str();
        }

      public:
        parse_lift ( const std::string & place
                   , const std::string & field
                   , const boost::filesystem::path & path
                   , const std::string & msg
                   )
          : generic (nice (place, field, path, msg))
        {}
      };

      // ******************************************************************* //

      template<typename T>
      class forbidden_shadowing : public generic
      {
      private:
        std::string nice ( const T & early
                         , const T & late
                         , const std::string & port_name
                         ) const
        {
          std::ostringstream s;

          s << "struct with name " << late.name
            << " in " << late.path
            << " shadows definition from " << early.path
            << " but this is forbidden, since it is a type used for port "
            << port_name
            ;

          return s.str();
        }

      public:
        forbidden_shadowing ( const T & early
                            , const T & late
                            , const std::string & port_name
                            )
          : generic (nice (early, late, port_name))
        {}
      };

      // ******************************************************************* //

      class duplicate_place : public generic
      {
      private:
        std::string nice ( const std::string & place
                         , const boost::filesystem::path & path
                         ) const
        {
          std::ostringstream s;

          s << "duplicate place " << place << " in " << path;

          return s.str();
        }

      public:
        duplicate_place ( const std::string & place
                        , const boost::filesystem::path & path
                        )
          : generic (nice (place, path))
        {}
      };

      // ******************************************************************* //

      class duplicate_port : public generic
      {
      private:
        std::string nice ( const std::string & direction
                         , const std::string & port
                         , const boost::filesystem::path & path
                         ) const
        {
          std::ostringstream s;

          s << "duplicate " << direction << "-port " << port
            << " in " << path
            ;

          return s.str();
        }

      public:
        duplicate_port ( const std::string & direction
                       , const std::string & port
                       , const boost::filesystem::path & path
                       )
          : generic (nice (direction, port, path))
        {}
      };

      // ******************************************************************* //

      class duplicate_connect : public generic
      {
      private:
        std::string nice ( const std::string & type
                         , const std::string & name
                         , const std::string & trans
                         , const boost::filesystem::path & path
                         ) const
        {
          std::ostringstream s;

          s << "duplicate " << "connect-" << type << " " << name
            << " for transition " << trans 
            << " in " << path;

          return s.str();
        }

      public:
        duplicate_connect ( const std::string & type
                          , const std::string & name
                          , const std::string & trans
                          , const boost::filesystem::path & path
                          )
          : generic (nice (type, name, trans, path))
        {}
      };

      // ******************************************************************* //

      template<typename T>
      class duplicate_transition : public generic
      {
      private:
        std::string nice (const T & t, const T & old) const
        {
          std::ostringstream s;

          s << "duplicate transition " << t.name << " in " << t.path
            << " first defintion was in " << old.path
            ;

          return s.str();
        }
      public:
        duplicate_transition (const T & t, const T & old)
          : generic (nice (t, old))
        {}
      };

      // ******************************************************************* //

      template<typename T>
      class duplicate_function : public generic
      {
      private:
        std::string nice (const T & t, const T & old) const
        {
          std::ostringstream s;

          s << "duplicate function " << t.name << " in " << t.path
            << " first defintion was in " << old.path
            ;

          return s.str();
        }
      public:
        duplicate_function (const T & t, const T & old)
          : generic (nice (t, old))
        {}
      };

      // ******************************************************************* //

      class port_connected_place_nonexistent : public generic
      {
      private:
        std::string nice ( const std::string & direction
                         , const std::string & port
                         , const std::string & place
                         , const boost::filesystem::path & path
                         ) const
        {
          std::ostringstream s;

          s << direction << "-port " << port 
            << " connected to non-existing place " << place
            << " in " << path
            ;
       
          return s.str();
        }
      public:
        port_connected_place_nonexistent ( const std::string & direction
                                         , const std::string & port
                                         , const std::string & place
                                         , const boost::filesystem::path & path
                                         )
          : generic (nice (direction, port, place, path))
        {}
      };

      // ******************************************************************* //

      class port_not_connected : public generic
      {
      private:
        std::string nice ( const std::string & direction
                         , const std::string & port
                         , const boost::filesystem::path & path
                         ) const
        {
          std::ostringstream s;

          s << direction << "-port " << port 
            << " not connected"
            << " in " << path
            ;
       
          return s.str();
        }
      public:
        port_not_connected ( const std::string & direction
                           , const std::string & port
                           , const boost::filesystem::path & path
                           )
          : generic (nice (direction, port, path))
        {}
      };

      // ******************************************************************* //

      template<typename PORT, typename PLACE>
      class port_connected_type_error : public generic
      {
      private:
        std::string nice ( const std::string & direction
                         , const PORT & port
                         , const PLACE & place
                         , const boost::filesystem::path & path
                         ) const
        {
          std::ostringstream s;

          s << "type error: port-" << direction << " " << port.name
            << " of type " << port.type
            << " connected to place " << place.name
            << " of type " << place.type
            << " in " << path
            ;

          return s.str();
        }

      public:
        port_connected_type_error ( const std::string & direction
                                  , const PORT & port
                                  , const PLACE & place
                                  , const boost::filesystem::path & path
                                  )
          : generic (nice (direction, port, place, path))
        {}
      };

      // ******************************************************************* //

      class connect_to_nonexistent_place : public generic
      {
      private:
        std::string nice ( const std::string & direction
                         , const std::string & trans
                         , const std::string & place
                         , const boost::filesystem::path & path
                         ) const
        {
          std::ostringstream s;

          s << "in transition " << trans << "in " << path << ": "
            << "connect-" << direction << " to nonexistent place " << place
            ;

          return s.str();
        }
      public:
        connect_to_nonexistent_place ( const std::string & direction
                                     , const std::string & trans
                                     , const std::string & place
                                     , const boost::filesystem::path & path
                                     )
          : generic (nice (direction, trans, place, path))
        {}
      };

      // ******************************************************************* //

      class connect_to_nonexistent_port : public generic
      {
      private:
        std::string nice ( const std::string & direction
                         , const std::string & trans
                         , const std::string & port
                         , const boost::filesystem::path & path
                         ) const
        {
          std::ostringstream s;

          s << "in transition " << trans << " in " << path << ": " 
            << "connect-" << direction << " to nonexistent port " << port
            ;

          return s.str();
        }
      public:
        connect_to_nonexistent_port ( const std::string & direction
                                    , const std::string & trans
                                    , const std::string & port
                                    , const boost::filesystem::path & path
                                    )
          : generic (nice (direction, trans, port, path))
        {}
      };

      // ******************************************************************* //

      class unknown_function : public generic
      {
      private:
        std::string nice ( const std::string & fun
                         , const std::string & trans
                         , const boost::filesystem::path & path
                         ) const
        {
          std::ostringstream s;

          s << "in transition " << trans << " in " << path << ": " 
            << "unknown function " << fun
            ;

          return s.str();
        }
      public:
        unknown_function ( const std::string & fun
                         , const std::string & trans
                         , const boost::filesystem::path & path
                         )
          : generic (nice (fun, trans, path))
        {}
      };

      // ******************************************************************* //

      template<typename PORT, typename PLACE>
      class connect_type_error : public generic
      {
      private:
        std::string nice ( const std::string & direction
                         , const std::string & trans
                         , const PORT & port
                         , const PLACE & place
                         , const boost::filesystem::path & path
                         ) const
        {
          std::ostringstream s;

          s << "in transition " << trans << " in " << path << ": "
            << "type error: connect-" << direction 
            << " place " << place.name
            << " of type " << place.type
            << " with port " << port.name
            << " of type " << port.type
            ;

          return s.str();
        }

      public:
        connect_type_error ( const std::string & direction
                           , const std::string trans
                           , const PORT & port
                           , const PLACE & place
                           , const boost::filesystem::path & path
                           )
          : generic (nice (direction, trans, port, place, path))
        {}
      };

      // ******************************************************************* //

      class synthesize_anonymous_function : public generic
      {
      private:
        std::string nice (const boost::filesystem::path & path) const
        {
          std::ostringstream s;

          s << "try to synthesize anonymous function in " << path;

          return s.str();
        }
      public:
        synthesize_anonymous_function (const boost::filesystem::path & path)
          : generic (nice (path))
        {}
      };

      // ******************************************************************* //

      class weparse : public generic
      {
      public:
        weparse (const std::string & msg)
          : generic (msg)
        {}
      };

      // ******************************************************************* //

      class strange : public generic
      {
      public:
        strange (const std::string & msg) 
          : generic ("this is STRANGE and should not happen", msg)
        {}
      };

#define THROW_STRANGE(msg) do { std::ostringstream s; s << __FILE__ << " [" << __LINE__ << "]: " << msg; throw error::strange (s.str()); } while (0)
      } // namespace error
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

#endif /* _xml_parse_error_hpp_ */
