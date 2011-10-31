// mirko.rahn@itwm.fraunhofer.de

#ifndef _XML_PARSE_UTIL_NAME_ELEMENT_HPP
#define _XML_PARSE_UTIL_NAME_ELEMENT_HPP

#include <ec2-api/parse/rapidxml/1.13/rapidxml.hpp>

#include <ec2-api/parse/types.hpp>
#include <ec2-api/parse/error.hpp>
#include <ec2-api/parse/util/skip.hpp>
#include <ec2-api/parse/util/expect.hpp>

namespace ec2 {
namespace xml
{
  namespace parse
  {
    inline std::string
    name_element (xml_node_type * & node)
    {
      skip (node, rapidxml::node_comment);

      try
        {
          expect (node, rapidxml::node_element);
        }
      catch (const error::missing_node &)
        {
          return "<missing_node>";
        }

      return node->name();
    }
  }
}
} // namespace ec2
/*
 * Local variables:
 *  tab-width: 2
 *  c-indent-level: 2
 *  c-basic-offset: 2
 * End:
 */


#endif
