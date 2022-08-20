
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>

#include "../container/container.hpp"
using namespace std;
/* ************************************************************************** */


namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Hash {

public:
  ulong operator()(const Data&) const noexcept; // (concrete function should not throw exceptions)
};

/* ************************************************************************** */

template <typename Data>
class HashTable: public virtual DictionaryContainer<Data>,
                 public virtual MappableContainer<Data>,
                 public virtual FoldableContainer<Data> 
                 { 

private:


protected:

  using DictionaryContainer<Data>::size;
  
  const ulong p = 9223372040000000087;
  ulong a;
  ulong b;
  ulong hashsize;
    
  // Copy assignment
  inline void operator=(const HashTable<Data>& h) {a = h.a; b = h.b; hashsize = h.hashsize; size = h.size;}; // Copy assignment of abstract types should not be possible.

  // Move assignment
  inline void operator=(HashTable<Data>&& h) {swap<ulong>(hashsize, h.hashsize); swap<ulong>(b,h.b); swap<ulong>(a,h.a); swap<ulong>(size,h.size); }; // Move assignment of abstract types should not be possible.
  
  //sarebbe inoltre inutile istanziare la tabella, siccome noi non siamo sicuri di come funzioni, una ha dizionari, l'altra no
  // ...

public:
  
  //Meglio non usare il costruttore di default, ma farne uno che gia ci costruisca le variabili per la funzione universale e una dimensione prefisata
  HashTable();
  // Destructor
  virtual ~HashTable() = default;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTable<Data>&)const = delete; // Comparison of abstract binary tree is possible.
  bool operator!=(const HashTable<Data>&)const = delete; // Comparison of abstract binary tree is possible.


  /* ************************************************************************ */

  // Specific member function

  virtual void Resize(const ulong&) = 0; // Resize the hashtable to a given size

  //ovviamente anche questa e' virutale, e ridimensiona la tabella. Il resize deve anche fare il rehashing ovviamente
  //Uno dei modi piu efficenti e' creare un altra hash, inserire tutti i valori che gia ho, fare uno swap ed e' fatta

protected:

  // Auxiliary member functions
  inline ulong HashKey(const Data dat) const noexcept { return (((a* (hasher(dat)) + b) % p) % hashsize); };
  Hash<Data> hasher;

 
};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
