
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <stdexcept>
#include <functional>

namespace lasd {



class Container {

private:

protected:

ulong size = 0;

public:


  virtual ~Container() = default;

  // Copy assignment
  virtual void operator=(const Container&) = delete;// Copy assignment of abstract types should not be possible.

  // Move assignment
  virtual void operator=(Container&&) = delete; // Move assignment of abstract types should not be possible.

  // Comparison operators
  virtual bool operator==(const Container&) const= delete; // Comparison of abstract types might not be possible.
  virtual bool operator!=(const Container&) const = delete; // Comparison of abstract types might not be possible.

  // Specific member functions

  virtual bool Empty() const noexcept {return (size == 0);};
  virtual ulong Size() const noexcept {return size;};

  virtual void Clear() noexcept = 0;

};


template <typename Data>
class LinearContainer: virtual public Container { // Must extend Container

private:

protected:

public:

  
  virtual ~LinearContainer() = default;


  // Copy assignment
  void operator=(const LinearContainer<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  void operator=(LinearContainer<Data>&&) = delete; // Move assignment of abstract types should not be possible.

  // Comparison operators
  bool operator==(const LinearContainer<Data>& lc)const; // Comparison of abstract types is possible.
  bool operator!=(const LinearContainer<Data>& lc)const; // Comparison of abstract types is possible.

  // Specific member functions

  Data& Front() const; // (concrete function must throw std::length_error when empty)
  Data& Back() const; // (concrete function must throw std::length_error when empty)

  virtual Data& operator[](const ulong) const = 0 ; // (concrete function must throw std::out_of_range when out of range)

};


template <typename Data>
class TestableContainer: virtual public Container { // Must extend Container, possiamo chiedere la presenza di un determinato elemento

private:

protected:

public:

  virtual ~TestableContainer() = default;

  // Copy assignment
  void operator=(const LinearContainer<Data>&) = delete; 
  // Move assignment
  void operator=(LinearContainer<Data>&&) = delete; 
  
  // Comparison operators
  bool operator==(const LinearContainer<Data>&)const = delete; 
  bool operator!=(const LinearContainer<Data>&)const = delete;

  // Specific member functions

  virtual bool Exists(const Data&)const noexcept = 0;

};

template <typename Data>
class DictionaryContainer: virtual public TestableContainer<Data> {

private:

protected:

public:

  // Destructor
  ~DictionaryContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  void operator=(const DictionaryContainer<Data>&) = delete ; // Copy assignment of abstract types should not be possible.

  // Move assignment
  void operator=(DictionaryContainer<Data>&&) = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const DictionaryContainer<Data>& )const = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const DictionaryContainer<Data>& )const = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual bool Insert(const Data&) = 0; // Copy of the value
  virtual bool Insert(Data&&) = 0; // Move of the value
  virtual bool Remove(const Data&) = 0;

  inline bool Insert(const LinearContainer<Data>& lc) {ulong os = TestableContainer<Data>::size; for (ulong i = 0; i<lc.Size(); i++) Insert(lc[i]); if(os<TestableContainer<Data>::size) return true; else return false;};
  inline bool Insert(LinearContainer<Data>&& lc) {ulong os = TestableContainer<Data>::size; for (ulong i = 0; i<lc.Size(); i++) Insert(std::move(lc[i])); if(os<TestableContainer<Data>::size) return true; else return false;};
  inline bool Remove(const LinearContainer<Data>& lc) {ulong os = TestableContainer<Data>::size; for (ulong i = 0; i<lc.Size(); i++) Remove(lc[i]); if(os>TestableContainer<Data>::size) return true; else return false;};

};


template <typename Data>
class MappableContainer: virtual public Container { // Must extend Container, sta ad indicare la possibilita di modificare dati tramite funzioni passate come argomento

private:

protected:

public:

  ~MappableContainer() = default;

  // Copy assignment
  void operator=(const MappableContainer<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  void operator=(MappableContainer<Data>&&) = delete; // Move assignment of abstract types should not be possible.

  // Comparison operators
  bool operator==(const MappableContainer<Data>&)const = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const MappableContainer<Data>&)const = delete; // Comparison of abstract types might not be possible.

  // Specific member functions

  typedef std::function<void(Data&, void*)> MapFunctor;

  virtual void Map(MapFunctor, void*) = 0;

};


template <typename Data>
class FoldableContainer: virtual public TestableContainer<Data> { // Must extend TestableContainer<Data>, accumula l-informazione

private:

protected:

public:

  
  virtual ~FoldableContainer() = default;

  // Copy assignment
  void operator=(const FoldableContainer<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  void operator=(FoldableContainer<Data>&&) = delete; // Move assignment of abstract types should not be possible.

  // Comparison operators
  bool operator==(const FoldableContainer<Data>&)const = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const FoldableContainer<Data>&) const = delete; // Comparison of abstract types might not be possible.

  // Specific member functions

  typedef std::function<void(const Data&, const void*, void*)> FoldFunctor;

  virtual void Fold(FoldFunctor,const void*, void*) const = 0;

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

};


template <typename Data>
class PreOrderMappableContainer: virtual public MappableContainer<Data> { // Must extend MappableContainer<Data>

private:

protected:

public:

  virtual ~PreOrderMappableContainer() = default;

  // Copy assignment<Data>
  void operator=(const PreOrderMappableContainer<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  void operator=(PreOrderMappableContainer<Data>&&) = delete; // Move assignment of abstract types should not be possible.

  // Comparison operators
  bool operator==(const PreOrderMappableContainer<Data>&)const  = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const PreOrderMappableContainer<Data>&) const = delete; // Comparison of abstract types might not be possible.

  using typename MappableContainer<Data>::MapFunctor;

  virtual void MapPreOrder(MapFunctor,void*) = 0;

  void Map(MapFunctor,void*); 
};


template <typename Data>
class PreOrderFoldableContainer: virtual public FoldableContainer<Data> { // Must extend FoldableContainer<Data>

private:

protected:

public:

  virtual ~PreOrderFoldableContainer() = default;

  // Copy assignment
  void operator=(const PreOrderFoldableContainer<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  void operator=(PreOrderFoldableContainer<Data>&&) = delete; // Move assignment of abstract types should not be possible.

  // Comparison operators
  bool operator==(const PreOrderFoldableContainer<Data>&)const  = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const PreOrderFoldableContainer<Data>&)const  = delete; // Comparison of abstract types might not be possible.

  using typename FoldableContainer<Data>::FoldFunctor;

  virtual void FoldPreOrder(FoldFunctor,const void*, void*) const = 0;

  void Fold(FoldFunctor,const void*, void*)const override; // Override FoldableContainer member

};


template <typename Data>
class PostOrderMappableContainer: virtual public MappableContainer<Data> { // Must extend MappableContainer<Data>

private:

protected:

public:

  virtual ~PostOrderMappableContainer() = default; 

  // Copy assignment
  void operator=(const PostOrderMappableContainer<Data>&) const = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  void operator=( PostOrderMappableContainer<Data>&&)const  = delete; // Move assignment of abstract types should not be possible.

  // Comparison operators
  bool operator==(const PostOrderMappableContainer<Data>&)const  = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const PostOrderMappableContainer<Data>&) const = delete; // Comparison of abstract types might not be possible.

  // Specific member functions

  using typename MappableContainer<Data>::MapFunctor;

  virtual void MapPostOrder(MapFunctor, void*) = 0;

  // Specific member functions (inherited from MappableContainer)

  void Map(MapFunctor, void*) override; // Override MappableContainer member

};

template <typename Data>
class PostOrderFoldableContainer: virtual public FoldableContainer<Data> { // Must extend FoldableContainer<Data>

private:

protected:

public:
  virtual ~PostOrderFoldableContainer() = default;
  
  //Copy assignment
  void operator=(PostOrderFoldableContainer<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  void operator=(PostOrderFoldableContainer<Data>&&) = delete; // Move assignment of abstract types should not be possible.

  // Comparison operators
  bool operator==(PostOrderFoldableContainer<Data>&) = delete; // Comparison of abstract types might not be possible.
  bool operator!=(PostOrderFoldableContainer<Data>&) = delete; // Comparison of abstract types might not be possible.

  using typename FoldableContainer<Data>::FoldFunctor;

  virtual void FoldPostOrder(FoldFunctor, const void*, void*) const = 0;

  // Specific member functions (inherited from FoldableContainer)

  void Fold(FoldFunctor,const void*,void*)const override; // Override FoldableContainer member

};

template <typename Data>
class InOrderMappableContainer: virtual public MappableContainer<Data>{ // Must extend MappableContainer<Data>

private:

protected:

public:

  virtual ~InOrderMappableContainer() = default;

  // Copy assignment
  void operator=(InOrderMappableContainer<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  void operator=(InOrderMappableContainer<Data>&&) = delete; // Move assignment of abstract types should not be possible.

  // Comparison operators
  bool operator==(InOrderMappableContainer<Data>&)= delete; // Comparison of abstract types might not be possible.
  bool operator!=(InOrderMappableContainer<Data>&)= delete; // Comparison of abstract types might not be possible.

  // Specific member functions

  using typename MappableContainer<Data>::MapFunctor;

  virtual void MapInOrder(MapFunctor,void*) = 0;

  // Specific member functions (inherited from MappableContainer)

  void Map(MapFunctor,void*) override; // Override MappableContainer member

};

/* ************************************************************************** */

template <typename Data>
class InOrderFoldableContainer: virtual public FoldableContainer<Data> { // Must extend FoldableContainer<Data>

private:

protected:


public:

  virtual ~InOrderFoldableContainer() = default;


  // Copy assignment
  void operator=(InOrderFoldableContainer<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  void operator=(InOrderFoldableContainer<Data>&&) = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(InOrderFoldableContainer<Data>&) = delete; // Comparison of abstract types might not be possible.
  bool operator!=(InOrderFoldableContainer<Data>&) = delete; // Comparison of abstract types might not be possible.

  // Specific member functions

  using typename FoldableContainer<Data>::FoldFunctor;

  virtual void FoldInOrder(FoldFunctor, const void*, void*)const = 0 ;

  // Specific member functions (inherited from FoldableContainer)

  void Fold(FoldFunctor, const void*, void*)const  override; // Override FoldableContainer member

};

/* ************************************************************************** */

template <typename Data>
class BreadthMappableContainer: virtual public MappableContainer<Data> { // Must extend MappableContainer<Data>

private:


protected:

public:

  // Destructor
  virtual ~BreadthMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  void operator=(BreadthMappableContainer<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  void operator=(BreadthMappableContainer<Data>&&) = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BreadthMappableContainer<Data>&) const = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const BreadthMappableContainer<Data>&) const = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  using typename MappableContainer<Data>::MapFunctor;

  virtual void MapBreadth(MapFunctor, void*) = 0;

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  void Map(MapFunctor, void*) override; // Override MappableContainer member

};

/* ************************************************************************** */

template <typename Data>
class BreadthFoldableContainer: virtual public FoldableContainer<Data>{ // Must extend FoldableContainer<Data>

private:

protected:

public:

  // Destructor
  virtual ~BreadthFoldableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  void operator=(const BreadthFoldableContainer<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  void operator=(BreadthFoldableContainer<Data>&&) = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BreadthFoldableContainer<Data>&)const = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const BreadthFoldableContainer<Data>&)const = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  using typename FoldableContainer<Data>::FoldFunctor;

  virtual void FoldBreadth(FoldFunctor, const void *, void *)const = 0;

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  void Fold(FoldFunctor,const void*, void*) const; // Override FoldableContainer member

};

/* ************************************************************************** */

}

#include "container.cpp"

#endif