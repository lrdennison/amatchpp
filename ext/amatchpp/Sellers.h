#define CPP_DECL_RW_ATTR( type, name)		\
  type name;					\
  type get_##name() { return name; }		\
  void set_##name(type vvv) {name = vvv; }


#define RUBY_DECL_RW_ATTR( klass, prototype, type, name)	\
  prototype.define_method( #name, &klass::get_##name);		\
  prototype.define_method( #name "=", &klass::set_##name);


namespace Amatchpp
{

  class Sellers {
  public:

    CPP_DECL_RW_ATTR( std::string, pattern)

    CPP_DECL_RW_ATTR( double, substitution)
    CPP_DECL_RW_ATTR( double, deletion)
    CPP_DECL_RW_ATTR( double, insertion)
    ;
    
  private:
    // Local variables
    const char *a_ptr, *b_ptr;
    int a_len, b_len;

    double *v[2];
    int  c, p;


  public:

    Sellers()
    {
      substitution = 1.0;
      deletion     = 1.0;
      insertion    = 1.0;
    }

    std::string hello()
    {
      return "Hello";
    }


    void setup(std::string &text)
    {
      a_ptr = pattern.c_str();
      a_len = pattern.length();
      b_ptr = text.c_str();
      b_len = text.length();

      for( int ix=0; ix<2; ++ix) {
	v[ix] = ALLOC_N(double, b_len + 1);
	MEMZERO(v[ix], double, b_len + 1);
      }
    }

    void teardown()
    {
      a_ptr = 0;
      a_len = 0;
      b_ptr = 0;
      b_len = 0;
  
      for( int ix=0; ix<2; ++ix) {
	if( v[ix]) {
	  free(v[ix]);
	  v[ix] = 0;
	}
      }
    }


    void compute()
    {
      int i, j;
      double weight;

      for (i = 1, c = 0, p = 1; i <= a_len; i++) {				
	c = i % 2;                      /* current row */                   
	p = (i + 1) % 2;                /* previous row */                  
	v[c][0] = i * deletion; /* first column */                  
	for (j = 1; j <= b_len; j++) {                                      
	  /* Bellman's principle of optimality: */				
	  weight = v[p][j - 1] +						
	    (a_ptr[i - 1] == b_ptr[j - 1] ? 0 : substitution);	
	  if (weight > v[p][j] + insertion) {			
	    weight = v[p][j] + insertion;				
	  }									
	  if (weight > v[c][j - 1] + deletion) {			
	    weight = v[c][j - 1] + deletion;			
	  }									
	  v[c][j] = weight;							
	}                                                                   
	p = c;                                                              
	c = (c + 1) % 2;                                                    
      }
    }


    double search(std::string &text)
    {
      setup( text);
      compute();

      double min = a_len;
      for (int i = 0; i <= b_len; i++) {
	if (v[p][i] < min) {
	  min = v[p][i];
	}
      }

      teardown();
      return( min);
    }

    
  };

}
