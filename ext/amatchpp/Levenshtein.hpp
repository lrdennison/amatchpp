#ifndef __LEVENSHTEIN_H__
#define __LEVENSHTEIN_H__

#include "DynProg.hpp"

namespace Amatchpp
{

  class Levenshtein : public DynProg {
  public:

    Levenshtein(const std::string pat);

    Rice::Object match(Rice::Object arg);
    Rice::Object similar(Rice::Object arg);
    Rice::Object search(Rice::Object arg);

  private:
    void compute();

    double _match(const std::string &text);
    double _similar(const std::string &text);
    double _search(const std::string &text);
    
  };

}

#endif
