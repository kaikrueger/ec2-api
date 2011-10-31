// mirko.rahn@itwm.fraunhofer.de

#ifndef _XML_PARSE_UTIL_READ_BOOL_HPP
#define _XML_PARSE_UTIL_READ_BOOL_HPP

#include <ec2-api/parse/rapidxml/1.13/rapidxml.hpp>

namespace ec2 {
namespace xml
{
  namespace parse
  {
    inline bool
    read_bool (const std::string & inp)
    {
      if (inp == "true")
        {
          return true;
        }
      else if (inp == "false")
        {
          return false;
        }
      else
        {
          throw std::runtime_error ("failed to read a bool from: " + inp);
        }
    }
  }
}
} //namespace ec2
/*
 * Local variables:
 *  tab-width: 2
 *  c-indent-level: 2
 *  c-basic-offset: 2
 * End:
 */
#endif
