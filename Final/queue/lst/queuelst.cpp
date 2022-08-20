
namespace lasd {

template<typename Data>
QueueLst<Data>::QueueLst()
{
    elements = nullptr;
    size = 0;
};



template<typename Data>
QueueLst<Data>::QueueLst(const LinearContainer<Data>& lc)
{
    elements = nullptr;
    size = 0;

    if(lc.Size()!= 0)
    {
        for(ulong i = 0; i<lc.Size(); i++)
        Enqueue(lc[i]);
    }

};

template<typename Data>
QueueLst<Data>::QueueLst(const QueueLst<Data>& ql)
{
    elements = nullptr;
    size = 0;

    if(ql.size!=0)
    {
        for(ulong i = 0; i<ql.size; i++)
        {
            Enqueue(ql[i]);
        }
    }

};

template<typename Data>
QueueLst<Data>::QueueLst(QueueLst<Data>&& ql)
{
    elements = ql.elements;
    size = ql.size;

    ql.elements = nullptr;
    ql.size = 0;
};

template<typename Data>
void QueueLst<Data>::operator=(const QueueLst<Data>& ql)
{
    Clear();
    if(ql.size!=0)
    {
        for(ulong i = 0; i<ql.size; i++)
        {
            Enqueue(ql[i]);
        }
    }
};

template<typename Data>
void QueueLst<Data>::operator=(QueueLst<Data>&& ql)
{  
    swap(elements,ql.elements);
    swap(size,ql.size);
};

template<typename Data>
bool QueueLst<Data>::operator==(const QueueLst<Data>& ql) const
{
    if(size == ql.size & size != 0)
    {
        return (*(ql.elements) == *elements);
    }
    else if (size == ql.size & size == 0 ) return true;
    else return false;
};


template<typename Data>
bool QueueLst<Data>::operator!=(const QueueLst<Data>& ql) const
{
    return !(*this == ql);
};

template<typename Data>
Data& QueueLst<Data>::Head()
{
    return List<Data>::Front();
};


template<typename Data>
const Data& QueueLst<Data>::Head() const
{   
    return List<Data>::Front();
};

template<typename Data>
void QueueLst<Data>::Dequeue()
{
    List<Data>::RemoveFromFront();
};

template<typename Data>
Data QueueLst<Data>::HeadNDequeue()
{
    return List<Data>::FrontNRemove();
};

template<typename Data>
void QueueLst<Data>::Enqueue(const Data& d)
{
    List<Data>::InsertAtBack(d);
};

template<typename Data>
void QueueLst<Data>::Enqueue(Data&& d)
{
    List<Data>::InsertAtBack(d);
};


template<typename Data>
void QueueLst<Data>::Clear() noexcept
{
    delete elements;
    elements = nullptr;
    size = 0;
};

}
