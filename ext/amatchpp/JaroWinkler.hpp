#ifndef __JAROWINKLER_H__
#define __JAROWINKLER_H__

#include <ctype.h>
#include "Jaro.hpp"

namespace Amatchpp
{

  class JaroWinkler : public Jaro {
  public:

    JaroWinkler(const std::string pat);

    CPP_DECL_RW_ATTR( double, scaling_factor)

    Rice::Object match(Rice::Object arg);

  private:

    double _match(const std::string &text);


  };

}


#endif
