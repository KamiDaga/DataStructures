
namespace lasd {


template<typename Data>
QueueVec<Data>::QueueVec()
{
    trueSize = 0;
    elements = new Data[2]; 
    size = 2;
    tail = 0;
    head = 0;
};

template<typename Data>
QueueVec<Data>::QueueVec(const LinearContainer<Data>& lc)
{
    trueSize = 0;
    elements = new Data[2];
    size = 2;
    tail = 0;
    head = 0;

    if(lc.Size()!= 0)
    {
        for (ulong i = 0; i<lc.Size(); i++)
        {
            Enqueue(lc[i]);
        }
    }

};

template<typename Data>
QueueVec<Data>::QueueVec(const QueueVec<Data>& qv)
{
    trueSize = 0;
    elements = new Data[2];
    size = 2;
    tail = 0;
    head = 0;

    if(qv.size != 0)
    {
        ulong i = qv.head;
        while(i != qv.tail)
        {
            Enqueue(qv[i]);
            i++;
            if(i == qv.size) i = 0;
        }
    }
};

template<typename Data>
QueueVec<Data>::QueueVec(QueueVec<Data>&& qv)
{
    trueSize = qv.trueSize;
    elements = qv.elements;
    size = qv.size;
    tail = qv.tail;
    head = qv.head;

    qv.elements = nullptr;
    qv.Clear();
};

template<typename Data>
void QueueVec<Data>::operator=(const QueueVec<Data>& qv)
{
    Clear();

    if(qv.trueSize != 0)
    {
        ulong i = qv.head;
        while(i != qv.tail)
        {
            Enqueue(qv[i]);
            i++;
            if(i == qv.size) i = 0;
        }
    }
};



template<typename Data>
void QueueVec<Data>::operator=(QueueVec<Data>&& qv)
{

    std::swap<ulong>(trueSize,qv.trueSize);
    std::swap<ulong>(size,qv.size);
    std::swap<Data*>(elements,qv.elements);
    std::swap<ulong>(tail,qv.tail);
    std::swap<ulong>(head,qv.head);

};


template<typename Data>
bool QueueVec<Data>::operator==(const QueueVec<Data>& qv) const
{

    if(trueSize == qv.trueSize)
    {
        ulong icurr = head;
        ulong iother = qv.head;

        while(icurr != tail)
        {
            if (elements[icurr]!= qv.elements[iother]) return false;
            icurr++;
            iother++;
            if(icurr == size) icurr = 0;
            if(iother == qv.size) iother = 0;
        }
        return true;
    }
    else return false;
};


template<typename Data>
bool QueueVec<Data>::operator!=(const QueueVec<Data>& qv) const
{
    return !(*this == qv);
};


template<typename Data>
Data& QueueVec<Data>::Head()
{
    if(trueSize!=0)
    {
        return elements[head];
    }
    else throw std::length_error("La queue e vuota!");
};

template<typename Data>
const Data& QueueVec<Data>::Head() const
{   
    if(trueSize!=0)
    {
        return elements[head];
    }
    else throw std::length_error("La queue e vuota!");
};


template<typename Data>
void QueueVec<Data>::Dequeue()
{

    if(trueSize!= 0)
    {
        head = head+1;
        if (head == size) head = 0;
        trueSize--;
        if(trueSize==size/4 && size>2) Reduce();
    }
    else throw std::length_error("La queue e vuota!");

};

template<typename Data>
Data QueueVec<Data>::HeadNDequeue()
{

    if(trueSize != 0)
    {
        Data ret = elements[head];
        head++;
        if(head==size)head = 0;
        trueSize--;
        if(trueSize==size/4 && size>2) Reduce();
        return ret;
    }
    else throw std::length_error("La queue e vuota!");

};


template<typename Data>
void QueueVec<Data>::Enqueue(const Data& d)
{

    elements[tail] = d;
    tail++;
    ulong tmp = tail;
    trueSize++;
    if(tail == size) tail = 0;
    if(trueSize == size) 
    {
        Expand();
    }
};


template<typename Data>
void QueueVec<Data>::Enqueue(Data&& d)
{

    elements[tail] = std::move(d);
    tail++;
    trueSize++;
    ulong tmp = size;
    if(tail == size) tail = 0;
    if(trueSize == size) 
    {
       Expand();
    }

};


template<typename Data>
void QueueVec<Data>::Clear() noexcept
{

    delete[] elements;
    elements = new Data[2];
    tail = 0;
    head = 0;
    size = 2;
    trueSize = 0;

};

template<typename Data>
void QueueVec<Data>::Expand()
{

    Data* tmp = new Data[2*size];
    ulong i = head;
    ulong j = 0;
    do
        {
            tmp[j] = elements[i];
            i++;
            if (i == size) i = 0;
            j++;
        }while(i != tail);
    head = 0;
    tail = j;
    size = 2*size;
    delete[] elements;
    elements = tmp;

};

template<typename Data>
void QueueVec<Data>::Reduce()
{
    Data* tmp = new Data[size/2];
    ulong i = head;
    ulong j = 0;
    if(trueSize != 0)
    {
        do
            {
                tmp[j] = elements[i];
                i++;
                if (i == size) i = 0;
                j++;
            }while(i != tail);
    }
    head = 0;
    tail = j;
    size = size/2;
    delete[] elements;
    elements = tmp;
};

}