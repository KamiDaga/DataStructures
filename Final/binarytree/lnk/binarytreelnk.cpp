#include "../../vector/vector.hpp"
#include <iostream>
using namespace std;
namespace lasd {

template<typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk()
{
    delete sx;
    delete dx;
};



template<typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const LinearContainer<Data>& lc) 
{
    root = nullptr;
    size = 0;
    if(lc.Size()!= 0)
    {
        QueueLst<NodeLnk*> Queue;
        root = new NodeLnk();
        root->Element()=lc[0];
        size++;
        Queue.Enqueue(root);
        for(ulong i = 1; i<lc.Size(); i++)
        {
            if(!((Queue.Head())->HasLeftChild()))
            {
                Queue.Head()->sx = new NodeLnk();
                Queue.Head()->sx->Element() = lc[i];
                Queue.Enqueue((Queue.Head()->sx));             
            }
            else if(!Queue.Head()->HasRightChild())
            {
                Queue.Head()->dx = new NodeLnk();
                Queue.Head()->dx->Element() = lc[i];
                Queue.Enqueue(Queue.Head()->dx);
                Queue.Dequeue();
            }
            size++;
        }
    }
};

template<typename Data>
void BinaryTreeLnk<Data>::NodeLnk::operator=(const NodeLnk& n)
{   
    this->Element() = n.Element();
    if(n.HasLeftChild())
    {
        sx = new NodeLnk();
        *sx= n.LeftChild();
        if(n.HasRightChild())
        {
            dx = new NodeLnk();
            *dx = n.RightChild();
        }
    }
    else
    {
        if(n.HasRightChild())
        {    
            dx = new NodeLnk();
            *dx = n.RightChild();
        }
    }
};

template<typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data>& bt) 
{
    size = bt.size;
    root = nullptr;
    
    if(bt.Size()!=0)
    {
        root = new NodeLnk();
        *root = bt.Root();
    }
};

template<typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data>&& bt) 
{
    root = &bt.Root();
    size = bt.Size();

    bt.root = nullptr;
    bt.size = 0;
};

template<typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk() 
{
    if (size != 0)delete root;
};

template<typename Data>
void BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& bt) 
{
    Clear();
    size = bt.Size();
    if(bt.Size()!=0)
    {
        root = new NodeLnk();
        *root=bt.Root();
    }
};

template<typename Data>
void BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data>&& bt) 
{
    swap<NodeLnk*>(root,bt.root);
    swap<ulong>(size,bt.size);
};

template<typename Data>
bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk<Data>& bt)const
{
    if(size == bt.size)
        if (size == 0) return true;
        else return (Root() == bt.Root());
    else return false;
};

template<typename Data>
bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk<Data>& bt)const
{
    return !(*this == bt);
};

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const
{
    if (size>0)return *root;
    else throw std::length_error("Accesso ad albero vuoto");
};

template<typename Data>
void BinaryTreeLnk<Data>::Clear() noexcept
{
    delete root;
    root = nullptr;
    size = 0;
};

}
