
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Iterator {

private:

protected:

public:

  // Destructor
  virtual ~Iterator()= default;  /* ************************************************************************ */

  // Copy assignment
  void operator=(const Iterator<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  void operator=(Iterator<Data>&) = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Iterator<Data>&)const = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const Iterator<Data>&)const = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual Data& operator*() const = 0; // (concrete function must throw std::out_of_range when terminated)
  
  virtual bool Terminated() const noexcept = 0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class ForwardIterator: virtual public Iterator<Data> {

private:


protected:

public:

  // Destructor
  virtual ~ForwardIterator()= default;

  /* ************************************************************************ */

  // Copy assignment
  void operator=(const ForwardIterator<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  void operator=(ForwardIterator<Data>&&); // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ForwardIterator<Data>&)const = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const ForwardIterator<Data>&)const = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual void operator++()  = 0 ; // (concrete function must throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BackwardIterator: virtual public Iterator<Data>{

private:

protected:

public:

  // Destructor
  virtual ~BackwardIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  void operator=(const BackwardIterator<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  void operator=(BackwardIterator<Data>&&) = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BackwardIterator<Data>&) const = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const BackwardIterator<Data>&) const = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual void operator--() =0; // (concrete function must throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BidirectionalIterator:virtual public ForwardIterator<Data>, virtual public BackwardIterator<Data> {


private:

protected:

public:

  // Destructor
  virtual ~BidirectionalIterator()= default;

  /* ************************************************************************ */

  // Copy assignment
  void operator=(const BidirectionalIterator<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  void operator=(BidirectionalIterator<Data>&&) = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BidirectionalIterator<Data>&)const =delete; // Comparison of abstract types might not be possible.
  bool operator!=(const BidirectionalIterator<Data>&)const =delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  inline bool Terminated() const noexcept override {return (ForwardTerminated() || BackwardTerminated());}; // Override Iterator member

  virtual bool ForwardTerminated() const noexcept  = 0; // (concrete function should not throw exceptions)

  virtual bool BackwardTerminated() const noexcept  = 0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class ResettableIterator { // Must extend Iterator<Data>

private:

protected:

public:

  // Destructor
  virtual ~ResettableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  void operator=(const ResettableIterator<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  void operator=(ResettableIterator<Data>&&) = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ResettableIterator<Data>&) const = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const ResettableIterator<Data>&) const = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual void Reset()noexcept = 0 ; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

}

#endif
