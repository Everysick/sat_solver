#include "solver.h"

#include <iostream>

template <class T>
Solver<T>::Solver(const T & n) : value_(n)
{
  std::cout << "init!" << std::endl;
}

template <class T>
Solver<T>::~Solver()
{
  std::cout << "delete!" << std::endl;
}

template<class T>
T Solver<T>::get()
{
  return value_;
}

template class Solver<int>;
