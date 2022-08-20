
namespace lasd {

template<typename Data>
StackVec<Data>::StackVec()
{
    size = 2;
    head = 0;
    elements = new Data[2];
};

template<typename Data>
StackVec<Data>::StackVec(LinearContainer<Data>& lc)
{
    size = 2;
    elements = new Data[2];
    head = 0;
    for (ulong i = 0; i<lc.Size(); i++)
        Push(lc[i]);
};

template<typename Data>
StackVec<Data>::StackVec(const StackVec<Data>& sv)
{
    size = sv.size;
    elements = new Data[size];

    for(ulong i = 0; i<size; i++)
        elements[i] = sv.elements[i];

    head = sv.head;

};

template<typename Data>
StackVec<Data>::StackVec(StackVec<Data>&& sv)
{
    size = sv.size;
    head = sv.head;
    elements = sv.elements;

    sv.elements = new Data[2];
    sv.head = 0;
    sv.size = 2;
};

template<typename Data>
StackVec<Data>::~StackVec()
{
   
};

template<typename Data>
void StackVec<Data>::operator=(const StackVec<Data>& sv)
{
    size = sv.size;
    if (elements != nullptr) delete[] elements;
    elements = new Data[size];
    head = sv.head;

    if (head != 0)
    {
        for(ulong i = 0; i<head; i++)
            elements[i] = sv.elements[i];
    }

};

template<typename Data>
void StackVec<Data>::operator=(StackVec<Data>&& sv)
{
    ulong tmp = size;
    Data* tmpP = elements;
    size = sv.size;
    sv.size = tmp;
    elements = sv.elements;
    sv.elements = tmpP;
    tmp = head;
    head = sv.head;
    sv.head = tmp;

};

template<typename Data>
bool StackVec<Data>::operator==(const StackVec<Data>& sv)const
{
    if(Size() == sv.Size())
    {
        for(ulong i = 0; i < Size(); i++)
            if(elements[i]!=sv.elements[i]) return false;
        return true;
    }
    {
        return false;
    }
};


template<typename Data>
bool StackVec<Data>::operator!=(const StackVec<Data>& sv)const
{
    return !(*this == sv);
};

template<typename Data>
const Data& StackVec<Data>::Top() const
{
    if (head!=0) return elements[head-1];
    else throw std::length_error("Lo stack e vuoto!");
};

template<typename Data>
Data& StackVec<Data>::Top()
{
    if (head!=0) return elements[head-1];
    else throw std::length_error("Lo stack e vuoto!");
};


template<typename Data>
void StackVec<Data>::Pop()
{
    if (head!=0) 
    {
        head = head-1;
        if(head <= size/4 && size > 2) Reduce();
    }
    else throw std::length_error("Lo stack e vuoto!");
};

template<typename Data>
Data StackVec<Data>::TopNPop()
{

    if (head!=0) 
    {   
        head = head-1;
        Data ret = elements[head];
        if(head <= size/4 && size > 2) Reduce();
        return ret;
    }
    else throw std::length_error("Lo stack e vuoto!");
};

template<typename Data>
void StackVec<Data>::Push(const Data& val)
{   
    if (head == size) Expand();

    elements[head] = val;
    head = head + 1;
};

template<typename Data>
void StackVec<Data>::Push(Data&& val)
{
    if (head == size) Expand();
    
    elements[head] = std::move(val);
    head = head + 1;
};


template<typename Data>
void StackVec<Data>::Clear() noexcept
{
    delete[] elements;
    head = 0;
    size = 2;
    elements = new Data[2];
};

template<typename Data>
void StackVec<Data>::Expand()
{
    Resize(2*size);
}

template<typename Data>
void StackVec<Data>::Reduce()
{
    Resize(size/2);
};


}
