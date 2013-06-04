#ifndef __UTILS_H__
#define __UTILS_H__


#define CPP_DECL_RW_ATTR( type, name)		\
  type name;					\
  type get_##name() { return name; }		\
  void set_##name(type vvv) {name = vvv; }


#define RUBY_DECL_RW_ATTR( klass, prototype, type, name)	\
  prototype.define_method( #name, &klass::get_##name);		\
  prototype.define_method( #name "=", &klass::set_##name);



#endif
