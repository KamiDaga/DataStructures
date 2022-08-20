
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackVec: virtual public Stack<Data>, virtual protected Vector<Data>{


private:

protected:

  using Vector<Data>::size;
  using Vector<Data>::elements;
  using Vector<Data>::Resize;

  ulong head;

public:

  ~StackVec();
  StackVec();

  // Specific constructor
  StackVec(LinearContainer<Data>&); // A stack obtained from a LinearContainer


  // Copy constructor
  StackVec(const StackVec<Data>&);

  // Move constructor
  StackVec(StackVec<Data>&&);

  // Copy assignment
  void operator=(const StackVec<Data>&);

  // Move assignment
  void operator=(StackVec<Data>&&);

  // Comparison operators
  bool operator==(const StackVec<Data>& ) const;
  bool operator!=(const StackVec<Data>& )const ;

  // Specific member functions (inherited from Stack)

  const Data& Top()const override; // Override Stack member (constant version; must throw std::length_error when empty)
  Data& Top() override; // Override Stack member (must throw std::length_error when empty)
  void Pop() override; // Override Stack member (must throw std::length_error when empty)
  Data TopNPop() override; // Override Stack member (must throw std::length_error when empty)
  void Push(const Data&) override; // Override Stack member (copy of the value)
  void Push(Data&&) override; // Override Stack member (move of the value)

  // Specific member functions (inherited from Container)

  inline bool Empty()const noexcept override { return head == 0;}; // Override Container member

  inline ulong Size()const noexcept override { return head;}; // Override Container member

  void Clear()noexcept override; // Override Container member

protected:

  // Auxiliary member functions

  void Expand();
  void Reduce();

};


}

#include "stackvec.cpp"

#endif
