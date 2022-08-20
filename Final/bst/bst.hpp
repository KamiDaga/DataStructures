
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../binarytree/binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST: virtual public BinaryTreeLnk<Data>, virtual public DictionaryContainer<Data>{ // Must extend BinaryTreeLnk<Data>

private:

protected:

  using BinaryTreeLnk<Data>::size;
  using BinaryTreeLnk<Data>::root;

public:

  // Default constructor
  BST() = default;

  /* ************************************************************************ */

  // Specific constructors
  BST(const LinearContainer<Data>&) ; // A bst obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BST(const BST<Data>&);

  // Move constructor
  BST(BST<Data>&&);

  /* ************************************************************************ */

  // Destructor
  ~BST() = default;

  /* ************************************************************************ */

  // Copy assignment
  void operator=(const BST<Data>&);

  // Move assignment
  void  operator=(BST<Data>&&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BST<Data>&) const; //con gli iteratori inorder
  bool operator!=(const BST<Data>&) const;

  /* ************************************************************************ */

  // Specific member functions

  const Data& Min(); // (concrete function must throw std::length_error when empty)
  Data MinNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMin(); // (concrete function must throw std::length_error when empty)

  const Data& Max(); // (concrete function must throw std::length_error when empty)
  Data MaxNRemove();// (concrete function must throw std::length_error when empty)
  void RemoveMax(); // (concrete function must throw std::length_error when empty)

  const Data& Predecessor(const Data&); // (concrete function must throw std::length_error when not found), riferimento costante
  Data PredecessorNRemove(const Data&); // (concrete function must throw std::length_error when not found), copia del valore
  void RemovePredecessor(const Data&); // (concrete function must throw std::length_error when not found), non restituisce nulla

  

  const Data& Successor(const Data&); // (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(const Data&); // (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data&); // (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data&) override; // Override DictionaryContainer member (Copy of the value)
  bool Insert(Data&&) override; // Override DictionaryContainer member (Move of the value)
  bool Remove(const Data&) override ; // Override DictionaryContainer member

  using DictionaryContainer<Data>::Insert;
  using DictionaryContainer<Data>::Remove;

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data&)const noexcept override; // Override TestableContainer member

protected:

  // Auxiliary member functions

  Data DataNDelete(typename BinaryTreeLnk<Data>::NodeLnk**);

  typename BinaryTreeLnk<Data>::NodeLnk* Detach(typename BinaryTreeLnk<Data>::NodeLnk**);//v

  typename BinaryTreeLnk<Data>::NodeLnk& DetachMin(typename BinaryTreeLnk<Data>::NodeLnk**);//v
  typename BinaryTreeLnk<Data>::NodeLnk& DetachMax(typename BinaryTreeLnk<Data>::NodeLnk**);//v

  typename BinaryTreeLnk<Data>::NodeLnk& Skip2Left(typename BinaryTreeLnk<Data>::NodeLnk**);//v
  typename BinaryTreeLnk<Data>::NodeLnk& Skip2Right(typename BinaryTreeLnk<Data>::NodeLnk**);//v

  typename BinaryTreeLnk<Data>::NodeLnk*& FindPointerToMin(typename BinaryTreeLnk<Data>::NodeLnk**);//v // Both mutable & unmutable versions
  typename BinaryTreeLnk<Data>::NodeLnk*& FindPointerToMax(typename BinaryTreeLnk<Data>::NodeLnk**); //v// Both mutable & unmutable versions
  const typename BinaryTreeLnk<Data>::NodeLnk*& FindPointerToMin(typename BinaryTreeLnk<Data>::NodeLnk**)const;//v // Both mutable & unmutable versions
  const typename BinaryTreeLnk<Data>::NodeLnk*& FindPointerToMax(typename BinaryTreeLnk<Data>::NodeLnk**)const; //v// Both mutable & unmutable versions

  typename BinaryTreeLnk<Data>::NodeLnk*& FindPointerTo(const Data&,typename BinaryTreeLnk<Data>::NodeLnk**); // Both mutable & unmutable versions
  typename BinaryTreeLnk<Data>::NodeLnk*const& FindPointerTo(const Data&,typename BinaryTreeLnk<Data>::NodeLnk* const*)const;

  typename BinaryTreeLnk<Data>::NodeLnk*& FindPointerToPredecessor(const Data&,typename BinaryTreeLnk<Data>::NodeLnk**); // Both mutable & unmutable versions
  typename BinaryTreeLnk<Data>::NodeLnk*& FindPointerToSuccessor( const Data&,typename BinaryTreeLnk<Data>::NodeLnk**); // Both mutable & unmutable versions
  const typename BinaryTreeLnk<Data>::NodeLnk*& FindPointerToPredecessor(const Data&,typename BinaryTreeLnk<Data>::NodeLnk* const *) const;
  const typename BinaryTreeLnk<Data>::NodeLnk*& FindPointerToSuccessor(const Data&,typename BinaryTreeLnk<Data>::NodeLnk* const *) const; 

};


/* ************************************************************************** */

}

#include "bst.cpp"

#endif
