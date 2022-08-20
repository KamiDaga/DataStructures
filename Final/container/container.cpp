

namespace lasd {

//Container member functions

/*bool Container::Empty() const noexcept{
    if (size == 0) return true; else return false;
};

ulong Container::Size() const noexcept{
    return size;
};*/

//LinearContainer equality operators

template<typename Data>
bool LinearContainer<Data>::operator==(const LinearContainer<Data>& lc) const
{
    if(size == lc.size)
    {
        for(ulong i = 0; i<size ; i++)
        {
            if(operator[](i)!= lc[i]) return false;
        }
        return true;
    }
    return false;
};

template<typename Data>
bool LinearContainer<Data>::operator!=(const LinearContainer<Data>& lc)const
{
    return !(operator==(lc));
};

//LinearContainer proprietary functions

template<typename Data>
Data& LinearContainer<Data>::Front() const
{  
    if (size!=0)    return (operator[](0));
    else throw std::length_error("Accesso ad un container vuoto");

};

template<typename Data>
Data& LinearContainer<Data>::Back() const
{
    if (size!=0) return (operator[](size-1));
    else throw std::length_error("Accesso ad un container vuoto");
};

//FoldableContainer proprietary functions

template<typename Data>
void FoldExists(const Data& d, const void* val, void* res)  noexcept
{
    if(*((Data*)val) == d) *((bool*)res) = true;
};

template<typename Data>
bool FoldableContainer<Data>::Exists(const Data& d)const noexcept
{
    bool exist = false;
    Fold(FoldExists<Data>, &d, &exist);
    return exist; 
};

//PreOrderMappableContainer Map

template<typename Data>
void PreOrderMappableContainer<Data>::Map(MapFunctor fun, void* v)
{
    MapPreOrder(fun,v);
};

//....FoldableContainer Map

template<typename Data>
void PreOrderFoldableContainer<Data>::Fold(FoldFunctor fun, const void* cv, void* v) const
{
    FoldPreOrder(fun, cv, v);
};
 
//PostOrderMappableContainer Map

template<typename Data>
void PostOrderMappableContainer<Data>::Map(MapFunctor fun, void* v)
{
    MapPostOrder(fun,v);
};

//PostOrderFoldable

template<typename Data>
void PostOrderFoldableContainer<Data>::Fold(FoldFunctor fun,const void* cv, void* v) const
{
    FoldPostOrder(fun, cv, v);
};

//InOrderMappable

template<typename Data>
void InOrderMappableContainer<Data>::Map(MapFunctor fun, void* v)
{
    MapInOrder(fun,v);
};

//InOrderFoldable

template<typename Data>
void InOrderFoldableContainer<Data>::Fold(FoldFunctor fun, const void* cv, void* v) const
{
    FoldInOrder(fun,cv,v);
};


//BreadthFoldable
template<typename Data>
void BreadthFoldableContainer<Data>::Fold(FoldFunctor fun, const void* cv, void* v) const
{
    FoldBreadth(fun,cv,v);
};

//BreadthMappable

template<typename Data>
void BreadthMappableContainer<Data>::Map(MapFunctor fun, void* v)
{
    MapBreadth(fun,v);
};


}
