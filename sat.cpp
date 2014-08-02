#include "ruby/ruby.h"
#include <iostream>

using namespace std;

VALUE wrap_solver_init(VALUE self)
{
  cout << "initialize!" << endl;
  return Qnil;
}

extern "C" void Init_SATSolver()
{
  VALUE val = rb_define_class("SatSolver", rb_cObject);

  rb_define_private_method(val, "initialize", RUBY_METHOD_FUNC(wrap_solver_init), 0);

  cout << "Hello World!" << endl;
}
