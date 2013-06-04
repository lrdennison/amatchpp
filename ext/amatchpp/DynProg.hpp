#ifndef __DYNAMICPROGRAMMING_H__
#define __DYNAMICPROGRAMMING_H__

#include "General.hpp"

namespace Amatchpp
{

  class DynProg : public General {
  public:

    CPP_DECL_RW_ATTR( double, substitution)
    CPP_DECL_RW_ATTR( double, deletion)
    CPP_DECL_RW_ATTR( double, insertion)
    ;
    

    double *v[2];
    int  c, p;


    DynProg(const std::string pat);

    void reset_weights();
    double max_weight();

    void setup(const std::string &text);
    void setup_v_deletion();
    void teardown();

    
  };

}


#endif
