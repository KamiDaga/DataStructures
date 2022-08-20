
namespace lasd {

template<typename Data>
StackLst<Data>::StackLst()
{
    size = 0;
    elements = nullptr;
};


template<typename Data>
StackLst<Data>::StackLst(LinearContainer<Data>& lc)
{
    size = 0;
    elements = nullptr;
    for (ulong i = 0; i < lc.Size(); i++)
        List<Data>::InsertAtBack(lc[i]); 
};

template<typename Data>
void CopyFoldFunctor(const Data& r,const void* v, void* aa)
{
    (static_cast<StackLst<Data>*>(aa))->Push(r);
} 

template<typename Data>
StackLst<Data>::StackLst(const StackLst<Data>& sc)
{
    if(sc.size != 0)
    {
        size = 0;
        sc.List<Data>::FoldPostOrder(CopyFoldFunctor<Data>, nullptr, this);
    }
    else
    {
        elements = nullptr;
        size = 0;
    }
    
};


template<typename Data>
StackLst<Data>::StackLst(StackLst<Data>&& sc)
{
    elements = sc.elements;
    size = sc.size;

    sc.size = 0;
    sc.elements = nullptr;
};


template<typename Data>
void StackLst<Data>::operator=(const StackLst<Data>& sc)
{
    Clear();
    if(sc.size != 0)
    {
        sc.List<Data>::FoldPostOrder(CopyFoldFunctor<Data>, nullptr, this);
    }
};


template<typename Data>
void StackLst<Data>::operator=(StackLst<Data>&& sc)
{
    typename List<Data>::Node* tmpN = elements;
    ulong tmp = size;

    size = sc.size;
    elements = sc.elements;

    sc.size = tmp;
    sc.elements = tmpN;
};


template<typename Data>
bool StackLst<Data>::operator==(const StackLst<Data>& sc)const
{
    if(size == sc.size && size!= 0)
    {
        return (*elements == *sc.elements);
    }
    else if (size == sc.size && size == 0) return true;
    else return false;
};

template<typename Data>
bool StackLst<Data>::operator!=(const StackLst<Data>& sc) const 
{
    return !(*this==sc);
};

template<typename Data>
const Data& StackLst<Data>::Top() const
{
    if(size != 0) return List<Data>::Front();
    else throw std::length_error("Lo stack e vuoto!");
};

template<typename Data>
Data& StackLst<Data>::Top()
{
    if(size != 0) return List<Data>::Front();
    else throw std::length_error("Lo stack e vuoto!");
};

template<typename Data>
void StackLst<Data>::Pop()
{
    List<Data>::RemoveFromFront();
};

template<typename Data>
Data StackLst<Data>::TopNPop()
{
    return List<Data>::FrontNRemove();
};

template<typename Data>
void StackLst<Data>::Push(const Data& v)
{
    List<Data>::InsertAtFront(v);
};

template<typename Data>
void StackLst<Data>::Push(Data&& v)
{
    List<Data>::InsertAtFront(v);
};

template<typename Data>
void StackLst<Data>::Clear() noexcept
{
    delete elements;
    elements = nullptr;
    size = 0;
};

}
