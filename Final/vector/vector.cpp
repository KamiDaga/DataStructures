namespace lasd 
{

template<typename Data>
Vector<Data>::Vector()
{
    this->size=0;
    elements = nullptr;
}

template<typename Data>
Vector<Data>::Vector(const ulong& nsize)
{
    size = nsize;
    if(size != 0)
    {
        elements = new Data[size]{};
    }
    else
    {
        elements = nullptr;
    }
};
    



template<typename Data>
Vector<Data>::Vector(LinearContainer<Data>& lc)
{
    size = lc.Size();
    elements = new Data[size]{};
    for (ulong i = 0; i<size; i++)
    {
        elements[i] = lc[i];
    }
};

template<typename Data>
Vector<Data>::Vector(const Vector<Data>& v)
{
    size = v.size;
    elements = new Data[size]{};

    for (ulong i = 0; i<size; i++)
    {
        elements[i] = v[i];
    }
};

template<typename Data>
Vector<Data>::Vector(Vector<Data>&& v)
{
    size = v.size;
    elements = v.elements;
    v.elements = nullptr;
    v.size = 0;
};

template<typename Data>
Vector<Data>::~Vector()
{
    if(size != 0) delete[] elements;
};

template<typename Data>
void Vector<Data>::operator=(const Vector<Data>& v)
{
    
    size = v.size;
    delete[] elements;
    if(size != 0)
    {
        elements = new Data[size]{};
        for (ulong i = 0; i<size; i++)
        {
            elements[i] = v[i];
        }
    }
    else elements = nullptr;
};

template<typename Data>
void Vector<Data>::operator=(Vector<Data>&& v)
{
    ulong tmp = size; 
    Data* tmpA = elements; 
    size = v.size; 
    v.size = tmp;
    elements = v.elements;
    v.elements = tmpA;
};

template<typename Data>
bool Vector<Data>::operator==(const Vector<Data>& v1) const
{
    if(size == v1.Size())
    {
        bool res = true;
        ulong i = 0;
        while(res && (i < size))
        {
            if(elements[i]!=v1[i]) res = false;
            i++;
        }
        return res;
    }
    else return false;
};

template<typename Data>
bool Vector<Data>::operator!=(const Vector<Data>& v1) const
{
    return !(*this == v1);
};

template<typename Data>
void Vector<Data>::Resize(const ulong nsize)
{
    if(size!=0)    
    {
        if(size != nsize)  
        {
            Data* tmp = new Data[nsize]{};
            if(nsize>size)
            {

                for (ulong i = 0; i < size ;i++)
                {
                    tmp[i] = elements[i];
                }
            }
            else
            {

                for (ulong i = 0; i < nsize ;i++)
                {
                    tmp[i] = elements[i];
                }
            }

            delete[] elements;
            elements = tmp;
        }
    }
    else
    {
        if(nsize != 0) elements = new Data[nsize]{};
    }
    size = nsize;
};

template<typename Data>
void Vector<Data>::Clear() noexcept
{
    delete[] elements;
    elements = nullptr;
    size = 0;
};

template <typename Data>
Data& Vector<Data>::operator[](const ulong i) const
{

    if(i<size)
        return elements[i];
    else throw std::out_of_range("Indice superiore alla dimensione dell'array");
};

template<typename Data>
void Vector<Data>::Map(MapFunctor fun, void* p)
{
    MapPreOrder(fun,p);
};

template<typename Data>
void Vector<Data>::MapPreOrder(MapFunctor fun, void* p)
{   
    if(size!=0)
    {
        for(ulong i = 0; i<size; i++)
        {
            fun(elements[i],p);
        }
    }
};

template<typename Data>
void Vector<Data>::MapPostOrder(MapFunctor fun, void* p)
{
    if(size!=0)
    {
        ulong i = size -1;
        bool frst = false;
        while(!frst)
        {
            fun(elements[i],p);
            if(i == 0) frst = true;
            i--;
        }
    }
};

template<typename Data>
void Vector<Data>::Fold(FoldFunctor fun,const void* cp, void* p) const
{
    FoldPreOrder(fun,cp,p);
};




template<typename Data>
void Vector<Data>::FoldPreOrder(FoldFunctor fun,const void* cp, void* p) const
{
    if(size!=0)
    {
        for(ulong i = 0; i<size; i++)
        {
            fun(elements[i],cp,p);
        }
    }
};



template<typename Data>
void Vector<Data>::FoldPostOrder(FoldFunctor fun,const void* cp, void* p) const
{
    if(size!=0)
    {
        ulong i = size -1;
        bool frst = false;
        while(!frst)
        {
            fun(elements[i],cp, p);
            if(i == 0) frst = true;
            i--;
        }
    }
};

}

