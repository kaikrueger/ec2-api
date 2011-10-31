// mirko.rahn@itwm.fraunhofer.de

#ifndef _XML_PARSE_UTIL_CDATA_HPP
#define _XML_PARSE_UTIL_CDATA_HPP

#include <ec2-api/parse/rapidxml/1.13/rapidxml.hpp>

#include <ec2-api/parse/types.hpp>
#include <ec2-api/parse/error.hpp>
#include <ec2-api/parse/util/skip.hpp>
#include <ec2-api/parse/util/expect.hpp>

namespace ec2 {
  namespace xml {
    namespace parse {
      inline void
    cdata (xml_node_type * & node)
    {
      skip (node, rapidxml::node_comment);

      try
        {
          expect (node, rapidxml::node_data, rapidxml::node_cdata);
        }
      catch (const error::missing_node &)
        {
          // do nothing, there was just no (c)data given
        }

      return;
    }

      inline std::vector<std::string>
    parse_cdata (const xml_node_type * node)
    {
      std::vector<std::string> v;

      for ( xml_node_type * child (node->first_node())
          ; child
          ; child = child ? child->next_sibling() : child
          )
        {
          cdata (child);

          if (child)
            {
              v.push_back (std::string (child->value()));
            }
        }

      return v;
    }
  }
  }
} // namespace ec2

#endif
