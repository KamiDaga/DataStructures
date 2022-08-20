
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec: virtual public BinaryTree<Data> {


                      
private:


protected:

  using BinaryTree<Data>::size;

  struct NodeVec: virtual public BinaryTree<Data>::Node 
  { 

  private:

  protected:

  ulong index;
  Vector<NodeVec*>* arr;
  inline ulong sx()const {return (2*index)+1;}
  inline ulong dx()const {return 2*(index+1);}

  public:
  
  friend class BinaryTreeVec<Data>;

  NodeVec(const BinaryTreeVec<Data>&, const ulong index, Data&);

  inline bool IsLeaf() const noexcept override{return (!HasLeftChild() && !HasRightChild());}; // (concrete function should not throw exceptions)
  inline bool HasLeftChild() const noexcept override{if (sx() < arr->Size()) return !(arr->operator[](sx())==nullptr); else return false; }; // (concrete function should not throw exceptions)
  inline bool HasRightChild() const noexcept override {if (dx() < arr->Size()) return !(arr->operator[](dx())==nullptr); else return false; }; // (concrete function should not throw exceptions)
  inline NodeVec& LeftChild() override {if (sx()> arr->Size()) throw std::out_of_range("Accesso a figlio sx inesistente"); else return *(arr->operator[](sx()));}; // (concrete function must throw std::out_of_range when not existent)
  inline NodeVec& RightChild() override{ if (dx() > arr->Size()) throw std::out_of_range("Accesso a figlio sx inesistente"); else return *(arr->operator[](dx()));} ; // (concrete function must throw std::out_of_range when not existent)
  inline const NodeVec& LeftChild() const override {if (sx()> arr->Size()) throw std::out_of_range("Accesso a figlio sx inesistente"); else return *(arr->operator[](sx()));}; // (concrete function must throw std::out_of_range when not existent)
  inline const NodeVec& RightChild() const override { if (dx() > arr->Size()) throw std::out_of_range("Accesso a figlio sx inesistente"); else return *(arr->operator[](dx()));} ; // (concrete function must throw std::out_of_range when not existent)
  inline void operator=(const NodeVec& n ) = delete;
  inline void operator=(NodeVec&& n) = delete;



  ~NodeVec();
  
  };


public:

  BinaryTreeVec();

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const LinearContainer<Data>&); // A binary tree obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec<Data>&);

  // Move constructor
  BinaryTreeVec(BinaryTreeVec<Data>&&);

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeVec();

  /* ************************************************************************ */

  // Copy assignment
  void operator=(const BinaryTreeVec<Data>&);

  // Move assignment
  void operator=(BinaryTreeVec<Data>&&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeVec<Data>&) const;
  bool operator!=(const BinaryTreeVec<Data>&) const;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  NodeVec& Root()const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear()noexcept override; // Override Container member

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthMappableContainer)
  using typename BinaryTree<Data>::MapFunctor;

  void MapBreadth(MapFunctor,void*) override; // Override BreadthMappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthFoldableContainer)
  using typename BinaryTree<Data>::FoldFunctor;

  void FoldBreadth(FoldFunctor, const void*, void *) const override; // Override BreadthFoldableContainer member

  private:
  
  Vector<NodeVec*>* arr;

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
