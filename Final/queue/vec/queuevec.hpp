
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueVec: virtual protected Vector<Data>, virtual public Queue<Data>{
              

private:

protected:

  using Vector<Data>::size;
  using Vector<Data>::elements;

  ulong trueSize = 0;
  ulong head = 0;
  ulong tail = 0;

public:


  QueueVec();

  ~QueueVec() = default;

  QueueVec(const LinearContainer<Data>&); // A queue obtained from a LinearContainer

  // Copy constructor
  QueueVec(const QueueVec<Data>&);

  // Move constructor
  QueueVec(QueueVec<Data>&&);

  // Copy assignment
  void operator=(const QueueVec<Data>&);

  // Move assignment
  void operator=(QueueVec<Data>&&);

  // Comparison operators
  bool operator==(const QueueVec<Data>&) const;
  bool operator!=(const QueueVec<Data>&) const;

  // Specific member functions (inherited from Queue)

  const Data& Head()const override; // Override Queue member (constant version; must throw std::length_error when empty)
  Data& Head()override; // Override Queue member (must throw std::length_error when empty)
  void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  Data HeadNDequeue()override; // Override Queue member (must throw std::length_error when empty)
  void Enqueue(const Data&) override; // Override Queue member (copy of the value)
  void Enqueue(Data&&) override; // Override Queue member (move of the value)


  // Specific member functions (inherited from Container)

  inline bool Empty() const noexcept override {return trueSize == 0;}; // Override Container member

  inline ulong Size() const noexcept override { return trueSize;}; // Override Container member

  void Clear() noexcept override; // Override Container member

protected:

  // Auxiliary member functions

  void Expand();
  void Reduce();
  // type SwapVectors(arguments) specifiers;

};

/* ************************************************************************** */

}

#include "queuevec.cpp"

#endif
