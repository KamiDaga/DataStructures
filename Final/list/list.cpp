using namespace std;


namespace lasd 
{

template<typename Data>
List<Data>::Node::Node(const Data& v)
{
    value = v;
    next = nullptr;
};

template<typename Data>
List<Data>::Node::Node(const Node& c)
{
    value = c.value;
    next = nullptr;
};

template<typename Data>
List<Data>::Node::Node(Node&& n)
{
    value = n.value;
    next = n.next;
    n.next = nullptr;
};

template<typename Data>
List<Data>::Node::~Node() noexcept
{
    if(this->next != nullptr) delete this->next;
};

template<typename Data>
bool List<Data>::Node::operator == (const Node& c) const
{
    if(c.next!= nullptr && next != nullptr)
        return (value == c.value && *(c.next) == *next); 
    else if (c.next == nullptr && next == nullptr)
        return (value == c.value);
    else   
        return false;
};

template<typename Data>
bool List<Data>::Node::operator != (const Node& c) const
{
    return !(*this == c);
};

template<typename Data>
void List<Data>::Node::AuxFoldPostOrder(FoldFunctor fu, const void* cv, void* v) const
{
    if(next!=nullptr)
    {
        next->AuxFoldPostOrder(fu,cv,v);
        fu(value,cv,v);
    }
    else
        fu(value,cv,v);
};

template<typename Data>
void List<Data>::Node::AuxMapPostOrder(MapFunctor fun, void* v)
{

    if(next!=nullptr)
    {
        next->AuxMapPostOrder(fun,v);
        fun(value,v);
    }
    else fun(value,v);
};

template<typename Data>
Data& List<Data>::Node::Access(ulong i) 
{
    if(i==0) return value;
    else 
    {
        if (next != nullptr) try {return next->Access(i-1);}
                            catch(out_of_range exc) { throw exc; }
        else throw out_of_range("Accesso a indice invalido");
    }
};

template<typename Data>
List<Data>::List()
{
    size = 0;
    elements = nullptr;
};

template<typename Data>
List<Data>::List(LinearContainer<Data>& lc)
{
    size = 0;
    elements = nullptr;
    if(lc.Size() != 0)
    {
        for (ulong i = 0; i< lc.Size(); i++)
        {
            InsertAtBack(lc[i]);
        }
    }
};

template<typename Data>
List<Data>::List(const List<Data>& lc)
{
    size = 0;
    elements = nullptr;
    if(lc.Size() != 0)
    {
        for (ulong i = 0; i< lc.Size(); i++)
        {
            InsertAtBack(lc[i]);
        }
    }
};

template<typename Data>
List<Data>::List(List<Data>&& lc)
{
    size = lc.size;
    elements = lc.elements;
    lc.size = 0; 
    lc.elements = nullptr;
};

template<typename Data>
List<Data>::~List()
{
    if(size!=0) delete elements;
};

template<typename Data>
void List<Data>::operator=(const List<Data>& l)
{
    Clear();
    for (ulong i = 0; i< l.size; i++)
    {
        InsertAtBack(l[i]);
    }
};

template<typename Data> 
void List<Data>::operator=(List<Data>&& lc)
{
    Node* tmpA = elements;
    ulong tmp = size;
    size = lc.size;
    elements = lc.elements;
    lc.elements = tmpA;
    lc.size = tmp;
};


template<typename Data>
bool List<Data>::operator==(const List<Data>& l) const
{
    if (size == l.size)
    {
        if(size == 0 )return true;
        return (*elements == *l.elements);
    }   
    else return false;
};

template<typename Data>
bool List<Data>::operator!=(const List<Data>& l) const
{
    return !(*this == l);
};

template<typename Data>
void List<Data>::InsertAtFront(const Data& d)
{
    if(size != 0 )
    {    
        Node* temp= new Node(d);
        temp->next = elements;
        elements = temp;
    }
    else elements = new Node(d);

    size++;
};

template<typename Data>
void List<Data>::InsertAtFront(Data&& d)
{
    Node* temp = new Node();
    temp->value = move(d);
    temp->next = this->elements;
    this->elements = temp;
    size++;
};

template<typename Data>
void List<Data>::RemoveFromFront()
{
    if(size!= 0)
    {
        Node* tmp = elements;
        elements = elements->next;
        tmp->next = nullptr;
        delete tmp;
        size--;
    }
    else throw std::length_error("La lista è vuota!");
};

template<typename Data>
Data List<Data>::FrontNRemove()
{
    if(size!= 0)
    {
        Node* tmp = elements;
        Data val;
        elements = elements->next;
        val = tmp->value;
        tmp->next = nullptr;
        size--;
        delete tmp;
        return val;
    }
    else throw std::length_error("La lista è vuota!");
};

template<typename Data>
void List<Data>::InsertAtBack(const Data& d)
{
    if(size != 0)
    {    
        Node* tmp = elements;
        while(tmp->next != nullptr)
        {
            tmp = tmp->next;
        }
        tmp->next = new Node(d);
    }
    else
    {
        elements = new Node(d);
    }
    size++;
};

template<typename Data>
void List<Data>::InsertAtBack(Data&& d)
{
    if(elements != nullptr)
    {
        Node* tmp = elements;
        while(tmp->next != nullptr)
        {
            tmp = tmp->next;
        }
        Node* a = new Node();
        tmp->next = a;
        a->value = move(d);
    }
    else
    {
        Node* a = new Node();
        a->value = move(d);
        elements = a;
    }
    size++;
};

template<typename Data>
void List<Data>::Clear() noexcept
{
    if(size!=0)
    {
        size = 0;
        delete elements;
        elements = nullptr;
    }
};



template<typename Data>
Data& List<Data>::operator[](const ulong i)const
{
    if(i<size && size != 0)
    {
        try{ return elements->Access(i); }
        catch(out_of_range exc) { throw exc; }
    }
    else
    {
        throw std::out_of_range("Accesso ad indice invalido");
    }
};

template<typename Data> 
void List<Data>::MapPreOrder(MapFunctor fun, void* v)
{
    for(ulong i = 0; i<size; i++)
        fun(operator[](i), v);
};

template<typename Data>
void List<Data>::MapPostOrder(MapFunctor fun, void* v)
{
    if(size>0)
        elements->AuxMapPostOrder(fun, v);
};



template<typename Data>
void List<Data>::Map(MapFunctor fun, void* v)
{
    MapPreOrder(fun,v);
};

template<typename Data>
void List<Data>::FoldPreOrder(FoldFunctor fu, const void* cv, void* v)const
{
    for (ulong i = 0; i<size; i++)
    {
        fu(operator[](i),cv,v);
    }
};



template<typename Data> 
void List<Data>::FoldPostOrder(FoldFunctor fu, const void* cv, void* v)const
{ 
    if(size>0)
        elements->AuxFoldPostOrder(fu, cv, v);
};

template<typename Data>
void List<Data>::Fold(FoldFunctor fun, const void* cv, void* v)const
{
    FoldPreOrder(fun, cv, v);
};

template<typename Data>
void List<Data>::MapPreOrder(MapFunctor fun, void* v, ulong n)
{
    if(n<size && size != 0)
    {
        Node* tmp = elements;
        ulong i = 0;
        for( ; i<n; i++)
            tmp = tmp->next;
        
        for( ; i<size; i++)
            fun(operator[](i), v);
    }    
};

template<typename Data>
void List<Data>::MapPostOrder(MapFunctor fun, void* v, ulong n)
{
    if(n<size && size != 0)
    {
        Node* tmp = elements;
        for (ulong i = 0; i<n; i++)
            tmp = tmp->next;

        tmp->AuxMapPostOrder(fun, v);
    }
};

template<typename Data>
void List<Data>::FoldPreOrder(FoldFunctor fun, const void* cv, void* v, ulong n) const
{
    if(n<size && size != 0)
    {
        Node* tmp = elements;
        ulong i = 0;
        for( ; i<n; i++)
            tmp = tmp->next;
        
        for( ; i<size; i++)
            fun(operator[](i),cv, v);
    }
};

template<typename Data>
void List<Data>::FoldPostOrder(FoldFunctor fun, const void* cv, void* v, ulong n) const
{
    if(n<size && size != 0) 
    {
        Node* tmp = elements;
        for (ulong i = 0; i<n; i++) 
            tmp = tmp->next;
 
        tmp->AuxFoldPostOrder(fun, cv, v);
    }
};

}

