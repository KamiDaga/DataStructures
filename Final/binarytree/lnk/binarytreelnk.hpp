
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk: virtual public BinaryTree<Data> 
                  {

private:

protected:

  using BinaryTree<Data>::size;
  struct NodeLnk: virtual public BinaryTree<Data>::Node {

    private:

    protected:

    public:
    friend class BinaryTreeLnk<Data>;
    NodeLnk() = default;

    NodeLnk* sx = nullptr;
    NodeLnk* dx = nullptr;

    inline bool IsLeaf() const noexcept override {return (sx==nullptr && dx == nullptr);}; // (concrete function should not throw exceptions)
    inline bool HasLeftChild() const noexcept override {return !(sx == nullptr);}; // (concrete function should not throw exceptions)
    inline bool HasRightChild() const noexcept override {return !(dx == nullptr);}; // (concrete function should not throw exceptions)

    inline NodeLnk& LeftChild() override {if(sx == nullptr)throw std::out_of_range("Accesso a figlio sx inesistente"); return *sx;}; // (concrete function must throw std::out_of_range when not existent)
    inline NodeLnk& RightChild() override {if(dx == nullptr)throw std::out_of_range("Accesso a figlio dx inesistente"); return *dx;}; // (concrete function must throw std::out_of_range when not existent)
    inline const NodeLnk& LeftChild() const override{if(sx == nullptr)throw std::out_of_range("Accesso a figlio sx inesistente"); return *sx;}; // (concrete function must throw std::out_of_range when not existent)
    inline const NodeLnk& RightChild() const override{if(dx == nullptr)throw std::out_of_range("Accesso a figlio dx inesistente"); return *dx;}; // (concrete function must throw std::out_of_range when not existent)

    void operator=(const NodeLnk&);


    ~NodeLnk();

    };

public:

  BinaryTreeLnk() = default; 

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const LinearContainer<Data>&); // A binary tree obtained from a LinearContainer, in ampiezza 

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk<Data>&);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk<Data>&&);

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  void operator=(const BinaryTreeLnk<Data>&);

  // Move assignment
  void operator=(BinaryTreeLnk<Data>&&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeLnk<Data>&)const;
  bool operator!=(const BinaryTreeLnk<Data>&)const;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  NodeLnk& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear()noexcept override; // Override Container member

  protected: 
  
  NodeLnk* root = nullptr;
};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
