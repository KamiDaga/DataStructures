
#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../bst/bst.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableClsAdr: virtual public HashTable<Data> { 

private:


protected:

  using HashTable<Data>::size;
  using HashTable<Data>::hashsize;
  using HashTable<Data>::HashKey;
  Vector<BST<Data>>* tavola; //testing, prima questo era inizializzato gia nel membro

public:

  // Default constructor
  

  /* ************************************************************************ */

  // Specific constructors
  HashTableClsAdr(const ulong); // A hash table of a given size
  HashTableClsAdr(const LinearContainer<Data>&); // A hash table obtained from a LinearContainer
  HashTableClsAdr(const ulong, const LinearContainer<Data>&); // A hash table of a given size obtained from a LinearContainer
  HashTableClsAdr(); //testing, questo prima era di default
  /* ************************************************************************ */

  // Copy constructor
  HashTableClsAdr(const HashTableClsAdr<Data>&);

  // Move constructor
  HashTableClsAdr(HashTableClsAdr<Data>&&);

  /* ************************************************************************ */

  // Destructor
  ~HashTableClsAdr();

  /* ************************************************************************ */

  // Copy assignment
  void operator=(const HashTableClsAdr<Data>&);

  // Move assignment
  void operator=(HashTableClsAdr<Data>&&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableClsAdr<Data>&)const;
  bool operator!=(const HashTableClsAdr<Data>&)const;

  //Scorriamo un vettore e prendiamo tutti i valori che ci sono e facciamo l'exist nell'altro

  /* ************************************************************************ */

  // Specific member functions (inherited from HashTable)

  void Resize(const ulong&) override; // Resize the hashtable to a given size
  //Resize e confronti si possono fare tutti tramite le map, siccome comunque sono praticamente uguali gli algoritmi (strutturalmente)
  //cambia SOLAMENTE la funzione che si usa

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data&) override; // Override DictionaryContainer member (Copy of the value)
  bool Insert(Data&&) override; // Override DictionaryContainer member (Move of the value)
  bool Remove(const Data&) override; // Override DictionaryContainer member

  using DictionaryContainer<Data>::Insert;
  using DictionaryContainer<Data>::Remove;


  //Semplicemente chiamiamo la funzione di hashkey sul dato richiesto (che da sola trasforma chiamando Hash e trova l'indirizzo giusto)
  //e al dizionario corrispondente inserisco il valore.

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member
  
  //Uguale, facciamo semplicemente hashkey e chiamiamo l'exist sul dizionario corrispondente
  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  void Map(MapFunctor, void *)override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;
  void Fold(FoldFunctor, const void*, void*)const override; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear()noexcept override; // Override Container member
  // Riporta lo stato alla tabella originale, con la dimensione prefissata all'inizio (dal costruttore senza nulla insomma)

};

/* ************************************************************************** */

}

#include "htclsadr.cpp"

#endif

