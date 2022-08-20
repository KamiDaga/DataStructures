#include <iostream>
namespace lasd 
{

    template<typename Data>
    BinaryTreeVec<Data>::NodeVec::NodeVec(const BinaryTreeVec<Data>& bt, const ulong index, Data& val)
    {
        arr = bt.arr;
        this->index = index;
        this->Element() = val;
    };
    
    template<typename Data>
    BinaryTreeVec<Data>::NodeVec::~NodeVec()
    {
        arr->operator[](index) = nullptr;
        if(HasLeftChild()) delete arr->operator[](sx()) ;
        if(HasRightChild()) delete arr->operator[](dx()) ;
    };

    template<typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec()
    {
        size = 0;
        arr = new Vector<NodeVec*>(0);
    };


    template<typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data>& lc)
    {
        arr = new Vector<NodeVec*>(lc.Size());
        size = lc.Size();

        for(ulong i = 0; i<lc.Size(); i++)
        {
            arr->operator[](i) = new NodeVec(*this,i,lc[i]);
        }

    };

    template<typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& bt)
    {
        arr = new Vector<NodeVec*>(bt.size);
        size = bt.size;

        for(ulong i = 0; i<bt.size; i++)
        {
            arr->operator[](i) = new NodeVec(*this,i,((bt.arr)->operator[](i))->Element());
        }
    };

    template<typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& bt)
    {
        arr = new Vector<NodeVec*>(0);
        size = 0;
        swap<ulong>(size,bt.size);
        swap<Vector<NodeVec*>*>(arr,bt.arr);
    };

    template<typename Data>
    BinaryTreeVec<Data>::~BinaryTreeVec()
    {
        if(size>0)  delete arr->operator[](0);
        delete arr; 
    };

    template<typename Data>
    void BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& bt)
    {
        if(size!=0) delete arr->operator[](0); 
        arr->Resize(bt.size);
        // delete arr;
        // arr = new Vector<NodeVec*>(bt.size);
        size = bt.size;

        for(ulong i = 0; i<bt.size; i++)
        {
            arr->operator[](i) = new NodeVec(*this,i,((bt.arr)->operator[](i))->Element());
        }
    };

    template<typename Data>
    void BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& bt)
    {
        swap<ulong>(size,bt.size);
        swap<Vector<NodeVec*>*>(arr,bt.arr);
    };

    template<typename Data>
    bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data>& bt) const
    {
        if(size == bt.size)
        {
            if(size == 0) return true; 
            else
            {
                for (ulong i = 0; i <size;i++)
                {
                    if(arr->operator[](i)->Element()!=bt.arr->operator[](i)->Element()) return false;
                }
                return true;
            }
        }
        return false;
    };

    template<typename Data>
    bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data>& bt) const
    {
        return !(*this == bt);
    };


    template<typename Data>
    typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const
    {
        if (size>0) return *(arr->operator[](0));
        else throw std::length_error("Accesso ad albero vuoto");
    };


    template<typename Data>
    void BinaryTreeVec<Data>::Clear() noexcept
    {
 
        if (size>0) delete arr->operator[](0);
        arr->Clear();
        size= 0;
    };


    template<typename Data>
    void BinaryTreeVec<Data>::MapBreadth(MapFunctor fun, void* v)
    {  
        for(ulong i = 0; i< size; i++) fun(arr->operator[](i)->Element(),v);
    };  

    template<typename Data>
    void BinaryTreeVec<Data>::FoldBreadth(FoldFunctor fun,const void* cv, void* v) const
    {  
        for(ulong i = 0; i< size; i++) fun(arr->operator[](i)->Element(),cv, v);
    };


}
