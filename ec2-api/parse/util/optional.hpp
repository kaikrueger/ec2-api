// mirko.rahn@itwm.fraunhofer.de

#ifndef _XML_PARSE_UTIL_OPTIONAL_HPP
#define _XML_PARSE_UTIL_OPTIONAL_HPP

#include <ec2-api/parse/rapidxml/1.13/rapidxml.hpp>

#include <ec2-api/parse/types.hpp>
#include <ec2-api/parse/util/maybe.hpp>

#include <string>

namespace ec2 {
namespace xml
{
  namespace parse
  {
    inline maybe<std::string>
    optional (const xml_node_type * node, const Ch * attr)
    {
      return node->first_attribute (attr) 
        ? Just<>(std::string(node->first_attribute (attr)->value()))
        : Nothing<std::string>()
        ;
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
