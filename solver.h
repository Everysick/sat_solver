#ifndef __SAT_H_
#define __SAT_H_

template<class T>
class Solver{
  T value_;
 public:
  Solver(const T & n);
  ~Solver();
  T get();
};

#endif
