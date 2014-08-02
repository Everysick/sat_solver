#include "ruby/ruby.h"
#include "solver.h"

#include <iostream>
#include <new>

using namespace std;

VALUE wrap_solver_init(VALUE self, VALUE literal_num)
{
  cout << "initialize!" << endl;

  Solver<int> solve_handle(NUM2INT(literal_num));
  cout << solve_handle.get() << endl;
  return Qnil;
}

extern "C" void Init_SATSolver()
{
  VALUE val = rb_define_class("SatSolver", rb_cObject);

  rb_define_private_method(val, "initialize", RUBY_METHOD_FUNC(wrap_solver_init), 1);

  cout << "Hello World!" << endl;
}
