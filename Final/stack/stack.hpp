
#ifndef STACK_HPP
#define STACK_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Stack:
            virtual public Container
          {
              

private:

protected:

public:

  virtual ~Stack() = default;

  // Copy assignment
  void operator=(Stack<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  void operator=(Stack<Data>&&) = delete; // Move assignment of abstract types should not be possible.

  bool operator!=(Stack<Data>&) = delete; // Comparison of abstract types might not be possible.

  // Specific member functions

  virtual const Data& Top() const = 0 ; // (constant version; concrete function must throw std::length_error when empty)
  virtual Data& Top() = 0; // (concrete function must throw std::length_error when empty)
  virtual void Pop() = 0; // (concrete function must throw std::length_error when empty)
  virtual Data TopNPop() = 0; // (concrete function must throw std::length_error when empty)
  virtual void Push(const Data&)  = 0; // Copy of the value
  virtual void Push(Data&&)  = 0; // Move of the value

};


}

#endif
