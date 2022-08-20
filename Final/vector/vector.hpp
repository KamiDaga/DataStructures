
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector: 
              virtual public LinearContainer<Data>,
              virtual public PreOrderMappableContainer<Data>,
              virtual public PostOrderMappableContainer<Data>,
              virtual public PreOrderFoldableContainer<Data>,
              virtual public PostOrderFoldableContainer<Data>
{
private:


protected:

  using LinearContainer<Data>::size;

  Data* elements = nullptr;

public:

  Vector();


  // Specific constructors
  Vector(const ulong&); // A vector with a given initial dimension
  Vector(LinearContainer<Data>&); // A vector obtained from a LinearContainer

  // Copy constructor
  Vector(const Vector<Data>&);

  // Move constructor
  Vector(Vector<Data>&&);

  // Destructor
  ~Vector();

  // Copy assignment
  void operator=(const Vector<Data>&);

  // Move assignment
  void operator=(Vector<Data>&&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Vector<Data>&) const;
  bool operator!=(const Vector<Data>&) const;

  // Specific member functions

  void Resize(const ulong); // Resize the vector to a given size

  void Clear() noexcept override; // Override Container member

  // Specific member functions (inherited from LinearContainer)

  Data& operator[](const ulong)const override;  // Override LinearContainer member (must throw std::out_of_range when out of range)

  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  void Map(MapFunctor, void*) override; // Override MappableContainer member

  // Specific member functions (inherited from PreOrderMappableContainer)

  void MapPreOrder(MapFunctor, void*) override; // Override PreOrderMappableContainer member

  // Specific member functions (inherited from PostOrderMappableContainer)

  void MapPostOrder(MapFunctor, void*) override; // Override PostOrderMappableContainer member

  // Specific member functions (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  void Fold(FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

  // Specific member functions (inherited from PreOrderFoldableContainer)

  void FoldPreOrder(FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

  // Specific member functions (inherited from PostOrderFoldableContainer)

  void FoldPostOrder(FoldFunctor, const void*, void*) const override; // Override FoldableContainer member


};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
