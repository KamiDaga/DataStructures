
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List: 
          virtual public  LinearContainer<Data>,
          virtual public  PreOrderMappableContainer<Data>,
          virtual public  PostOrderMappableContainer<Data>,
          virtual public  PreOrderFoldableContainer<Data>,
          virtual public  PostOrderFoldableContainer<Data>{

private:


public:

  List();

  // Specific constructor
  List(LinearContainer<Data>&); // A list obtained from a LinearContainer

  // Copy constructor
  List(const List<Data>&);

  // Move constructor
  List(List<Data>&&);

  // Destructor
  virtual ~List();

  // Copy assignment
  void operator=(const List<Data>&);

  // Move assignment
  void operator=(List<Data>&&);

  // Comparison operators
  bool operator==(const List<Data>&) const;
  bool operator!=(const List<Data>&) const;

  // Specific member functions

  void InsertAtFront(const Data&); // Copy of the value
  void InsertAtFront(Data&&); // Move of the value
  void RemoveFromFront(); // (must throw std::length_error when empty)
  Data FrontNRemove(); // (must throw std::length_error when empty)

  void InsertAtBack(const Data&); // Copy of the value
  void InsertAtBack(Data&&); // Move of the value

  // Specific member functions (inherited from Container)

  void Clear()noexcept override; // Override Container member

  // Specific member functions (inherited from LinearContainer)

  Data& operator[](const ulong i) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)
  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  void Map(MapFunctor, void*) override; // Override MappableContainer member
  void MapPreOrder(MapFunctor, void*) override; // Override PreOrderMappableContainer member
  void MapPostOrder(MapFunctor, void*) override; // Override PostOrderMappableContainer member
  // Specific member functions (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  void Fold(FoldFunctor, const void*, void*)const override; // Override FoldableContainer member
  void FoldPreOrder(FoldFunctor, const void*, void*)const override; // Override FoldableContainer member
  void FoldPostOrder(FoldFunctor, const void*, void*)const override; // Override FoldableContainer member
  

  private: 
  
  void MapPreOrder(MapFunctor, void*,ulong); // Accessory function executing from one point of the list onwards
  void MapPostOrder(MapFunctor, void*,ulong); // Accessory function executing from one point of the list onwards

  // Auxiliary member functions (for PreOrderFoldableContainer & PostOrderFoldableContainer)

  void FoldPreOrder(FoldFunctor, const void*, void*, ulong) const; // Accessory function executing from one point of the list onwards
  void FoldPostOrder(FoldFunctor, const void*, void*, ulong) const; // Accessory function executing from one point of the list onwards

  

protected:

  using LinearContainer<Data>::size;


  struct Node {

    Data value;
    Node* next = nullptr;

    // Specific constructors
    Node(const Data& v);
    Node() = default;
    
    // Copy constructor
    Node(const Node&);

    // Move constructor
    Node(Node&&);

    // Destructor
    ~Node() noexcept;

    // Comparison operators
    bool operator == (const Node&)const;
    bool operator != (const Node&)const;


    // Specific member functions
    Data& Access(ulong);
    void AuxMapPostOrder(MapFunctor,void*);
    void AuxFoldPostOrder(FoldFunctor,const void*, void*)const;

  };
  
  Node* elements = nullptr;


};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
