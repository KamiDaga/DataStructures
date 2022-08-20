
#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackLst: virtual private List<Data>,
                virtual public Stack<Data>
                {
                  

private:

protected:

  using List<Data>::size;
  using typename List<Data>::FoldFunctor;

  using List<Data>::Node;
  using List<Data>::elements;

public:
  
  StackLst();

  // Specific constructor
  StackLst(LinearContainer<Data>&); // A stack obtained from a LinearContainer

  // Copy constructor
  StackLst(const StackLst<Data>&);

  // Move constructor
  StackLst(StackLst<Data>&&);

  // Destructor
  ~StackLst() = default;

  // Copy assignment
  void operator=(const StackLst<Data>&);

  // Move assignment
  void operator=(StackLst<Data>&&);

  // Comparison operators
  bool operator==(const StackLst<Data>&) const;
  bool operator!=(const StackLst<Data>&) const;

  // Specific member functions (inherited from Stack)

  const Data& Top() const override; // Override Stack member (constant version; must throw std::length_error when empty)
  Data& Top() override; // Override Stack member (must throw std::length_error when empty)
  void Pop() override; // Override Stack member (must throw std::length_error when empty)
  Data TopNPop() override; // Override Stack member (must throw std::length_error when empty)
  void Push(const Data&) override; // Override Stack member (copy of the value)
  void Push(Data&&) override; // Override Stack member (move of the value)

  // Specific member functions (inherited from Container)

  void Clear() noexcept override;


};


}

#include "stacklst.cpp"

#endif
