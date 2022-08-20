
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

#include "../iterator/iterator.hpp"

#include "../queue/lst/queuelst.hpp"

#include "../stack/lst/stacklst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTree: virtual public PreOrderMappableContainer<Data>,
                  virtual public PostOrderMappableContainer<Data>,
                  virtual public InOrderMappableContainer<Data>,
                  virtual public BreadthMappableContainer<Data>,
                  virtual public PreOrderFoldableContainer<Data>,
                  virtual public PostOrderFoldableContainer<Data>,
                  virtual public InOrderFoldableContainer<Data>,
                  virtual public BreadthFoldableContainer<Data>
                               {
                   

private:

protected:

  using BreadthMappableContainer<Data>::size;


public:

 

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  virtual void operator=(const BinaryTree<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  virtual void operator=(BinaryTree<Data>&&) = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTree<Data>&) const; // Comparison of abstract binary tree is possible 
  bool operator!=(const BinaryTree<Data>&) const; // Comparison of abstract binary tree is possible.

  /* ************************************************************************ */



  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  void Map(MapFunctor,void*) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  void Fold(FoldFunctor,const void *, void*)const override; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from PreOrderMappableContainer)

  void MapPreOrder(MapFunctor,void*) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from PreOrderFoldableContainer)

  void FoldPreOrder(FoldFunctor,const void *, void*)const override; // Override PreOrderFoldableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from PostOrderMappableContainer)

  void MapPostOrder(MapFunctor,void*) override; // Override PostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from PostOrderFoldableContainer)

  void FoldPostOrder(FoldFunctor,const void *, void*)const override; // Override PostOrderFoldableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from InOrderMappableContainer)

  void MapInOrder(MapFunctor,void*) override; // Override InOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from InOrderFoldableContainer)

  void FoldInOrder(FoldFunctor,const void *, void*)const override; // Override InOrderFoldableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthMappableContainer)

  void MapBreadth(MapFunctor,void*) override; // Override BreadthMappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthFoldableContainer)

  void FoldBreadth(FoldFunctor,const void *, void*)const override; // Override BreadthFoldableContainer member

 struct Node {

  private:

  protected:

  // Comparison operators
  bool operator==(const Node&)const; // Comparison of abstract types is possible, but should not be visible.
  bool operator!=(const Node&)const; // Comparison of abstract types is possible, but should not be visible.
  void AuxFoldPreOrder(FoldFunctor fun, const void* cv, void* v);
  void AuxFoldPostOrder(FoldFunctor fun, const void * cv, void* v);
  void AuxFoldInOrder(FoldFunctor fun, const void * cv, void* v);
  void AuxFoldBreadth(FoldFunctor,const void*, void*);
  void AuxMapPreOrder(MapFunctor, void *);
  void AuxMapPostOrder(MapFunctor, void *);
  void AuxMapInOrder(MapFunctor, void *);
  void AuxMapBreadth(MapFunctor,void *);
  Data value;

  public:

    friend class BinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Copy assignment
    virtual void operator=(const Node&) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    virtual void operator=(Node&&) = delete; // Move assignment of abstract types should not be possible.

    /* ********************************************************************** */

    // Specific member functions

    Data& Element(); // Mutable access to the element (concrete function should not throw exceptions)
    const Data& Element() const; // Immutable access to the element (concrete function should not throw exceptions)

    virtual bool IsLeaf() const noexcept = 0; // (concrete function should not throw exceptions)
    virtual bool HasLeftChild() const noexcept = 0; // (concrete function should not throw exceptions)
    virtual bool HasRightChild() const noexcept = 0; // (concrete function should not throw exceptions)

    virtual Node& LeftChild()= 0; // (concrete function must throw std::out_of_range when not existent)
    virtual Node& RightChild()= 0; // (concrete function must throw std::out_of_range when not existent)
    virtual const Node& LeftChild() const = 0;
    virtual const Node& RightChild() const = 0;
  };


  virtual Node& Root() const = 0; // (concrete function must throw std::length_error when empty)
};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderIterator: virtual public ForwardIterator<Data>,virtual public ResettableIterator<Data> {
                      

private:


protected:
StackLst<typename BinaryTree<Data>::Node*>* toVisit;
typename BinaryTree<Data>::Node* currElement;
typename BinaryTree<Data>::Node* root;


public:

  // Specific constructors
  BTPreOrderIterator(const BinaryTree<Data>&); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderIterator(const BTPreOrderIterator<Data>&);

  // Move constructor
  BTPreOrderIterator(BTPreOrderIterator<Data>&& );
//Move constructor da problemi sulla sorgente del move
  /* ************************************************************************ */

  // Destructor
  ~BTPreOrderIterator();

  /* ************************************************************************ */

  // Copy assignment
  void operator=(const BTPreOrderIterator<Data>&) ;

  // Move assignment
  void operator=(BTPreOrderIterator<Data>&&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPreOrderIterator<Data>&) const;
  bool operator!=(const BTPreOrderIterator<Data>&) const;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  Data& operator*() const override ; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  void operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderIterator: virtual public ForwardIterator<Data>,
                           virtual public ResettableIterator<Data> 
                          {
                          
private:

protected:
  
  StackLst<typename BinaryTree<Data>::Node*>* toVisit; //Messo in public per ragioni di testing

  typename BinaryTree<Data>::Node* currElement;
  typename BinaryTree<Data>::Node* root;
  void MinLeaf();

public:

  // Specific constructors
  BTPostOrderIterator(const BinaryTree<Data>&); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderIterator(const BTPostOrderIterator<Data>&);

  // Move constructor
  BTPostOrderIterator(BTPostOrderIterator<Data>&&);

  /* ************************************************************************ */

  // Destructor
  ~BTPostOrderIterator();

  /* ************************************************************************ */

  // Copy assignment
  void operator=(const BTPostOrderIterator<Data>&);

  // Move assignment
  void operator=(BTPostOrderIterator<Data>&&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPostOrderIterator<Data>&) const;
  bool operator!=(const BTPostOrderIterator<Data>&) const;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  void operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderIterator: virtual public ForwardIterator<Data>,
                        virtual public ResettableIterator<Data> {

private:


protected:

  StackLst<typename BinaryTree<Data>::Node*>* toVisit;
  typename BinaryTree<Data>::Node* currElement;
  typename BinaryTree<Data>::Node* root;
  void GoToMin();


public:

  // Specific constructors
  BTInOrderIterator(const BinaryTree<Data>&); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderIterator(const BTInOrderIterator<Data>&);

  // Move constructor
  BTInOrderIterator(BTInOrderIterator<Data>&&);

  /* ************************************************************************ */

  // Destructor
  ~BTInOrderIterator();

  /* ************************************************************************ */

  // Copy assignment
  void operator=(const BTInOrderIterator<Data>&);

  // Move assignment
  void operator=(BTInOrderIterator<Data>&&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTInOrderIterator<Data>&)const;
  bool operator!=(const BTInOrderIterator<Data>&)const;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  void operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset()noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthIterator: virtual public ForwardIterator<Data>,
                         virtual public ResettableIterator<Data> {

private:


protected:
  QueueLst<typename BinaryTree<Data>::Node*>* toVisit;
  typename BinaryTree<Data>::Node* currElement;
  typename BinaryTree<Data>::Node* root;

  void AheadAndGetChildren();
public:

  // Specific constructors
  BTBreadthIterator(const BinaryTree<Data>&); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthIterator(const BTBreadthIterator<Data>&);

  // Move constructor
  BTBreadthIterator(BTBreadthIterator<Data>&&);

  /* ************************************************************************ */

  // Destructor
  ~BTBreadthIterator();

  /* ************************************************************************ */

  // Copy assignment
  void operator=(const BTBreadthIterator<Data>&);

  // Move assignment
  void operator=(BTBreadthIterator<Data>&&);

  /* ************************************************************************ */

  // Comparison operators 
  /* ************************************************************************ */
  
  bool operator==(const BTBreadthIterator<Data>&) const;
  
  bool operator!=(const BTBreadthIterator<Data>&) const;

  // Specific member functions (inherited from Iterator)

  Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  void operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
