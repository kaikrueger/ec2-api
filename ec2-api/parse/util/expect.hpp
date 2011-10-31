// mirko.rahn@itwm.fraunhofer.de

#ifndef _XML_PARSE_UTIL_EXPECT_HPP
#define _XML_PARSE_UTIL_EXPECT_HPP

#include <ec2-api/parse/rapidxml/1.13/rapidxml.hpp>

#include <ec2-api/parse/types.hpp>
#include <ec2-api/parse/error.hpp>

#include <ec2-api/parse/util/skip.hpp>

namespace ec2 {
namespace xml
{
  namespace parse
  {
    inline void expect (xml_node_type * & node, const rapidxml::node_type t)
    {
      skip (node, rapidxml::node_comment);

      if (!node)
        {
          throw error::missing_node (t);
        }

      if (node->type() != t)
        {
          throw error::wrong_node (t, node->type());
        }
    }

    inline void expect ( xml_node_type * & node
                , const rapidxml::node_type t1
                , const rapidxml::node_type t2
                )
    {
      skip (node, rapidxml::node_comment);

      if (!node)
        {
          throw error::missing_node (t1, t2);
        }

      if (node->type() != t1 && node->type() != t2)
        {
          throw error::wrong_node (t1, t2, node->type());
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
