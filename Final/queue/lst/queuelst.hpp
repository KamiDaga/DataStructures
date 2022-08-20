
#ifndef QUEUELST_HPP
#define QUEUELST_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueLst: virtual private List<Data>, virtual public Queue<Data>{
                  

private:

protected:

  using List<Data>::size;
  using List<Data>::elements;


public:

  QueueLst();

  // Specific constructor
  QueueLst(const LinearContainer<Data>&); // A queue obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  QueueLst(const QueueLst<Data>&);

  // Move constructor
  QueueLst(QueueLst<Data>&&);

  // Destructor
  ~QueueLst() = default;

  // Copy assignment
  void operator=(const QueueLst<Data>&);

  // Move assignment
  void operator=(QueueLst<Data>&&);

  // Comparison operators
  bool operator==(const QueueLst<Data>&) const;
  bool operator!=(const QueueLst<Data>&) const;

  // Specific member functions (inherited from Queue)

  const Data& Head()const override; // Override Queue member (constant version; must throw std::length_error when empty)
  Data& Head() override; // Override Queue member (must throw std::length_error when empty)
  void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)
  void Enqueue(const Data&) override; // Override Queue member (copy of the value)
  void Enqueue(Data&&) override; // Override Queue member (move of the value)

  // Specific member functions (inherited from Container)

  void Clear() noexcept override; // Override Container member

};

/* ************************************************************************** */

}

#include "queuelst.cpp"

#endif
