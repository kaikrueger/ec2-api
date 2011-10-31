// mirko.rahn@itwm.fraunhofer.de

#ifndef _XML_PARSE_UTIL_SKIP_HPP
#define _XML_PARSE_UTIL_SKIP_HPP

#include <ec2-api/parse/types.hpp>

namespace ec2 {
namespace xml
{
  namespace parse
  {
    inline void skip (xml_node_type * & node, const rapidxml::node_type t)
    {
      while (node && (node->type() == t))
        {
          node = node->next_sibling();
        }
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
