#ifndef __LONGESTSUBSTRING_H__
#define __LONGESTSUBSTRING_H__

#include "General.hpp"

namespace Amatchpp
{

  class LongestSubstring : public General {
  public:

    LongestSubstring(const std::string pat);

    Rice::Object match(Rice::Object arg);
    Rice::Object similar(Rice::Object arg);

  private:
    int compute();

    double _match(const std::string &text);
    double _similar(const std::string &text);
    
  };

}


#endif
