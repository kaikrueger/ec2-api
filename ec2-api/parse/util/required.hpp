// mirko.rahn@itwm.fraunhofer.de

#ifndef _XML_PARSE_UTIL_REQUIRED_HPP
#define _XML_PARSE_UTIL_REQUIRED_HPP

#include <ec2-api/parse/rapidxml/1.13/rapidxml.hpp>

#include <ec2-api/parse/types.hpp>
#include <ec2-api/parse/error.hpp>

namespace ec2 {
namespace xml
{
  namespace parse
  {
    static std::string
    required ( const std::string & pre
             , const xml_node_type * node
             , const Ch * attr
             )
    {
      if (!node->first_attribute (attr))
        {
          throw error::missing_attr (pre, attr);
        }

      return node->first_attribute (attr)->value();
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
