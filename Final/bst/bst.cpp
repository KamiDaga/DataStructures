
namespace lasd {

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::Detach(typename BinaryTreeLnk<Data>::NodeLnk** ref)
{
    typename BinaryTreeLnk<Data>::NodeLnk* tmp = nullptr;

    if(*ref != nullptr)
    {
        if((*ref)->HasLeftChild() && (*ref)->HasRightChild())
        {
            tmp = &DetachMin(&(*ref)->dx);
            Data swp = (*ref)->Element();
            (*ref)->Element() = tmp->Element();
            tmp->Element() = swp;
        }
        else
        {
            if((*ref)->IsLeaf())
            {
                tmp = *ref;
                *ref = nullptr;
                size --;
            }
            else if(!(*ref)->HasLeftChild())
                tmp = &Skip2Right(ref);
            else   
                tmp = &Skip2Left(ref);
        }
        return tmp;
    }
    else
        return *ref;
};

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BST<Data>::Skip2Left(typename BinaryTreeLnk<Data>::NodeLnk** ref)
{   
    typename BinaryTreeLnk<Data>::NodeLnk* tmp = *ref;
    (*ref) = (*ref)->sx;
    tmp->sx = nullptr;
    size --;
    return *tmp;
};

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BST<Data>::Skip2Right(typename BinaryTreeLnk<Data>::NodeLnk** ref)
{   
    typename BinaryTreeLnk<Data>::NodeLnk* tmp = *ref;
    (*ref) = (*ref)->dx;
    tmp->dx = nullptr;
    size --;
    return *tmp;
};

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BST<Data>::DetachMin(typename BinaryTreeLnk<Data>::NodeLnk** ref)
{
    typename BinaryTreeLnk<Data>::NodeLnk* tmp = nullptr;
    while ((*ref)->sx != nullptr)
    {
        ref = &((*ref)->sx);
    }
    tmp = *ref;
    *ref = (*ref)->dx;
    tmp->dx = nullptr;
    size --;
    return *tmp;
};

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BST<Data>::DetachMax(typename BinaryTreeLnk<Data>::NodeLnk** ref)
{
    typename BinaryTreeLnk<Data>::NodeLnk* tmp = nullptr;
    while ((*ref)->dx != nullptr)
    {
        ref = &((*ref)->dx);
    }
    tmp = *ref;
    *ref = (*ref)->sx;
    tmp->sx = nullptr;
    size --;
    return *tmp;
};

template<typename Data>
Data BST<Data>::DataNDelete(typename BinaryTreeLnk<Data>::NodeLnk** ref)
{
    typename BinaryTreeLnk<Data>::NodeLnk* tmp = Detach(ref);
    Data tmpVal = tmp->Element();
    delete tmp;
    return tmpVal;
};

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk*& BST<Data>::FindPointerToMin(typename BinaryTreeLnk<Data>::NodeLnk** ref)
{
    if(!(*ref)->HasLeftChild()) 
    {
        return *ref;
    }
    else
    {
        if((*ref)->sx != nullptr)
        {
            return FindPointerToMin(&((*ref)->sx));
        }
    }
    return *ref;
};

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk*& BST<Data>::FindPointerToMax(typename BinaryTreeLnk<Data>::NodeLnk** ref)
{
    if(!(*ref)->HasRightChild()) 
    {
        return *ref;
    }
    else
    {
        if((*ref)->dx != nullptr)
        {
            return FindPointerToMax(&((*ref)->dx));
        }
    }
    return *ref;
};

template<typename Data>
const typename BinaryTreeLnk<Data>::NodeLnk*& BST<Data>::FindPointerToMax(typename BinaryTreeLnk<Data>::NodeLnk** ref) const
{
    if(!(*ref)->HasRightChild()) 
    {
        return *ref;
    }
    else
    {
        if((*ref)->dx != nullptr)
        {
            return FindPointerToMax(&((*ref)->dx));
        }
    }
    return *ref;
};

template<typename Data>
const typename BinaryTreeLnk<Data>::NodeLnk*& BST<Data>::FindPointerToMin(typename BinaryTreeLnk<Data>::NodeLnk** ref) const
{
    if(!(*ref)->HasLeftChild()) 
    {
        return *ref;
    }
    else
    {
        while ((*ref)->sx != nullptr)
        {
            return FindPointerToMin(&((*ref)->sx));
        }

    }
    return *ref;
};

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk*& BST<Data>::FindPointerToPredecessor(const Data& d,typename BinaryTreeLnk<Data>::NodeLnk** sc)
{    
    typename BinaryTreeLnk<Data>::NodeLnk** tmp = nullptr;
    if((*sc) != nullptr)
    {
        if(d<(*sc)->Element()) 
        {    
            return FindPointerToPredecessor(d,&((*sc)->sx));
        }  
        else if((*sc)->Element()<d)
        {   
            tmp = &FindPointerToPredecessor(d,&((*sc)->dx));
            if(*tmp == nullptr)
                return *sc;
            else
                return *tmp;
        }    
        else
        {
            if((*sc)->sx != nullptr) return FindPointerToMax(&(*sc)->sx);
            else return (*sc)->sx;
        }
    }
    else return *sc;
};

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk*& BST<Data>::FindPointerToSuccessor(const Data& d,typename BinaryTreeLnk<Data>::NodeLnk** sc)
{
    typename BinaryTreeLnk<Data>::NodeLnk** tmp= nullptr;
    if((*sc) != nullptr)
    {
        if(d<(*sc)->Element()) 
        {    
            tmp = &FindPointerToSuccessor(d,&((*sc)->sx));
            if(*tmp == nullptr)
                return *sc;
            else
                return *tmp;
        }  
        else if((*sc)->Element()<d)
        {   
            return FindPointerToSuccessor(d,&((*sc)->dx));
        }    
        else
        {
            if((*sc)->dx != nullptr) return FindPointerToMin(&(*sc)->dx);
            else return (*sc)->dx;
        }
    }
    else return *sc;

};

template<typename Data>
const typename BinaryTreeLnk<Data>::NodeLnk*& BST<Data>::FindPointerToPredecessor(const Data& d,typename BinaryTreeLnk<Data>::NodeLnk* const* sc) const
{
    typename BinaryTreeLnk<Data>::NodeLnk** tmp = nullptr;
    if((*sc) != nullptr)
    {
        if(d<(*sc)->Element()) 
        {    
            return FindPointerToPredecessor(d,&((*sc)->sx));
        }  
        else if((*sc)->Element()<d)
        {   
            tmp = &FindPointerToPredecessor(d,&((*sc)->dx));
            if(*tmp == nullptr)
                return *sc;
            else
                return *tmp;
        }    
        else
        {
            if((*sc)->sx != nullptr) return FindPointerToMax(&(*sc)->sx);
            else return (*sc)->sx;
        }
    }
    else return *sc;
};

template<typename Data>
const typename BinaryTreeLnk<Data>::NodeLnk*& BST<Data>::FindPointerToSuccessor(const Data& d,typename BinaryTreeLnk<Data>::NodeLnk* const* sc) const
{
    typename BinaryTreeLnk<Data>::NodeLnk** tmp= nullptr;
    if((*sc) != nullptr)
    {
        if(d<(*sc)->Element()) 
        {    
            tmp = &FindPointerToSuccessor(d,&((*sc)->sx));
            if(*tmp == nullptr)
                return *sc;
            else
                return *tmp;
        }  
        else if((*sc)->Element()<d)
        {   
            return FindPointerToSuccessor(d,&((*sc)->dx));
        }    
        else
        {
            if((*sc)->dx != nullptr) return FindPointerToMin(&(*sc)->dx);
            else return (*sc)->dx;
        }
    }
    else return *sc;
};

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk*& BST<Data>::FindPointerTo(const Data& d,typename BinaryTreeLnk<Data>::NodeLnk** sc)
{
    if(*sc != nullptr)
    {
        if(d<(*sc)->Element()) 
            return FindPointerTo(d,&((*sc)->sx));
        else if((*sc)->Element()<d)
            return FindPointerTo(d,&((*sc)->dx));  
        else
            return *sc;
    }
    return *sc;
};

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* const& BST<Data>::FindPointerTo(const Data& d,typename BinaryTreeLnk<Data>::NodeLnk* const* sc) const
{
    if(*sc != nullptr)
    {
        if(d<(* sc)->Element()) 
            return FindPointerTo(d,&((*sc)->sx));
        else if((*sc)->Element()<d)
            return FindPointerTo(d,&((*sc)->dx));  
        else
            return *sc;
    }
    return *sc;
};

template<typename Data>
const Data& BST<Data>::Min()
{
    if(size == 0) throw std::length_error("ABR vuoto!");
    else
    {
        return FindPointerToMin(&root)->Element();
    }
};

template<typename Data>
Data BST<Data>::MinNRemove()
{
    if(size == 0) throw std::length_error("ABR vuoto!");
    else
    {
        return DataNDelete(&FindPointerToMin(&root));
    }
};

template<typename Data>
void BST<Data>::RemoveMin()
{
    if(size == 0) throw std::length_error("ABR vuoto!");
    else
    {
        delete &DetachMin(&root);
    }  
};

template<typename Data>
const Data& BST<Data>::Max()
{
    if(size == 0) throw std::length_error("ABR vuoto!");
    else
    {
        return FindPointerToMax(&root)->Element();
    }
};

template<typename Data>
Data BST<Data>::MaxNRemove()
{
    if(size == 0) throw std::length_error("ABR vuoto!");
    else
    {
        return DataNDelete(&FindPointerToMax(&root));
    }
};

template<typename Data>
void BST<Data>::RemoveMax()
{
    if(size == 0) throw std::length_error("ABR vuoto!");
    else
    {
        delete &DetachMax(&root);
    }  
};

template<typename Data>
const Data& BST<Data>::Successor(const Data& d)
{
    typename BinaryTreeLnk<Data>::NodeLnk** stima;
    if(size == 0) throw std::length_error("ABR vuoto!");
    else
    {
        stima = &FindPointerToSuccessor(d,&root);
        if((*stima) == nullptr) {throw std::length_error("Successore non trovato");}
        return (*stima)->Element();
    }
};

template<typename Data>
Data BST<Data>::SuccessorNRemove(const Data& d)
{
    typename BinaryTreeLnk<Data>::NodeLnk** stima;
    if(size == 0) throw std::length_error("ABR vuoto!");
    else
    {
        stima = &FindPointerToSuccessor(d,&root);
        if((*stima) == nullptr) throw std::length_error("Successore non trovato");
        return DataNDelete(stima);
    }
};

template<typename Data>
void BST<Data>::RemoveSuccessor(const Data& d)
{
    typename BinaryTreeLnk<Data>::NodeLnk** stima;
    if(size == 0) throw std::length_error("ABR vuoto!");
    else
    {
        stima = &FindPointerToSuccessor(d,&root);
        if((*stima) == nullptr) throw std::length_error("Successore non trovato");
        delete Detach(stima);
    }  
};

template<typename Data>
const Data& BST<Data>::Predecessor(const Data& d)
{
    typename BinaryTreeLnk<Data>::NodeLnk** stima;
    if(size == 0) throw std::length_error("ABR vuoto!");
    else
    {
        stima = &FindPointerToPredecessor(d,&root);
        if((*stima) == nullptr) throw std::length_error("Predecessore non trovato");
        return (*stima)->Element();
    }
};

template<typename Data>
Data BST<Data>::PredecessorNRemove(const Data& d)
{
    typename BinaryTreeLnk<Data>::NodeLnk** stima;
    if(size == 0) throw std::length_error("ABR vuoto!");
    else
    {

        stima = &FindPointerToPredecessor(d,&root);
        if((*stima) == nullptr) throw std::length_error("Predecessore non trovato");
        return DataNDelete(stima);

    }
};

template<typename Data>
void BST<Data>::RemovePredecessor(const Data& d)
{
    typename BinaryTreeLnk<Data>::NodeLnk** stima;
    if(size == 0) throw std::length_error("ABR vuoto!");
    else
    {
        stima = &FindPointerToPredecessor(d,&root);
        if((*stima) == nullptr) throw std::length_error("Predecessore non trovato");
        delete Detach(stima);
    }  
};

template<typename Data>
bool BST<Data>::Insert(const Data& d)
{
    typename BinaryTreeLnk<Data>::NodeLnk** tmp = &FindPointerTo(d,&root);
    if(*tmp == nullptr)
    {
        *tmp = new typename BinaryTreeLnk<Data>::NodeLnk();
        (*tmp)->Element() = d;
        size++;
        return true;
    }
    return false;
};

template<typename Data>
bool BST<Data>::Insert(Data&& d)
{
    typename BinaryTreeLnk<Data>::NodeLnk** tmp = &FindPointerTo(d,&root);
    if(*tmp == nullptr)
    {
        *tmp = new typename BinaryTreeLnk<Data>::NodeLnk();
        (*tmp)->Element() = std::move(d);
        size++;
        return true;
    }
    return false;
};

template<typename Data>
bool BST<Data>::Remove(const Data& d)
{
    if(size == 0) return false;
    typename BinaryTreeLnk<Data>::NodeLnk* tmp = Detach(&FindPointerTo(d,&root)); 
    if(tmp != nullptr)
    {   
        delete tmp;
        return true;
    }
    return false;
};


template<typename Data>
BST<Data>::BST(const LinearContainer<Data>& lc)
{
    //BST();
    if(!lc.Empty())
    {
        for(ulong i = 0; i<lc.Size(); i++)
            Insert(lc[i]);
    }
};

template<typename Data>
BST<Data>::BST(const BST<Data>& bs)
{
    //BST();
    BTBreadthIterator<Data> it (bs);
    while(!it.Terminated())
    {
        Insert(*it);
        ++it;
    }
};

template<typename Data>
BST<Data>::BST(BST<Data>&& bs )
{
    root = bs.root;
    size = bs.size;
    
    bs.root = nullptr;
    bs.size = 0;
};

template<typename Data>
void BST<Data>::operator=(const BST<Data>& bs)
{
    BinaryTreeLnk<Data>::Clear();

    BTBreadthIterator<Data> it (bs);
    while(!it.Terminated())
    {
        Insert(*it);
        ++it;
    }
};

template<typename Data>
void  BST<Data>::operator=(BST<Data>&& bs)
{
    swap<typename BinaryTreeLnk<Data>::NodeLnk*>(root, bs.root);
    swap<ulong>(size, bs.size);
};

template<typename Data>
bool BST<Data>::operator==(const BST<Data>& bs) const
{
    if(size == bs.size)
    {
        if(size==0) return true;
        BTInOrderIterator<Data> it1 (bs);
        BTInOrderIterator<Data> it2 (*this);
        while(!it1.Terminated()) 
        {
            if(*it1 != *it2) return false;
            ++it1;
            ++it2;
        }
        return true;
    }
    else return false;
};


template<typename Data>
bool BST<Data>::operator!=(const BST<Data>& bs) const
{
    return !(*this == bs);
};

template<typename Data>
bool BST<Data>::Exists(const Data& d) const noexcept
{
    return (!(FindPointerTo(d,&root) == nullptr));
};


}

