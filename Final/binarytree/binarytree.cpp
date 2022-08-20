namespace lasd {

template<typename Data>
bool BinaryTree<Data>::Node::operator==(const Node& n) const
{
    if(n.HasLeftChild() && HasLeftChild())
    {
        if(n.HasRightChild() && HasRightChild())
        {
            if(Element() == n.Element()) return (LeftChild() == n.LeftChild() && RightChild() == n.RightChild());
            else return false;
        }
        else if(!n.HasRightChild() && !HasRightChild())
        {
            if(Element() == n.Element()) return (LeftChild() == n.LeftChild());
            else return false;
        }
        else
        {
            return false;
        }
    }
    else if(!n.HasLeftChild() && !HasLeftChild())
    {
        if(n.HasRightChild() && HasRightChild())
        {
            if(Element() == n.Element()) return (RightChild() == n.RightChild());
            else return false;
        }
        else if(!n.HasRightChild() && !HasRightChild())
        {
            if(Element() == n.Element()) return true;
            else return false;
        }
        else
        {
            return false;
        }
    }
    else return false;
};


template<typename Data>
bool BinaryTree<Data>::Node::operator!=(const Node& n) const
{
    return !(*this == n);
};

template<typename Data>
Data& BinaryTree<Data>::Node::Element()
{
    return value;
};

template<typename Data>
const Data& BinaryTree<Data>::Node::Element() const
{
    return value;
};

template<typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree<Data>& bt) const
{
    if(size == bt.size) 
    {
        if (size == 0) return true;
        return (Root() == bt.Root()); 
    }
    else return false;
};

template<typename Data>
bool BinaryTree<Data>::operator!=(const BinaryTree<Data>& bt) const
{
    return !(*this == bt);
};

template<typename Data>
void BinaryTree<Data>::Node::AuxFoldPreOrder(FoldFunctor fun, const void* cv, void* v)
{
    fun(this->Element(),cv,v);
    if(HasLeftChild())
    {
        LeftChild().AuxFoldPreOrder(fun,cv,v);
        if(HasRightChild()) RightChild().AuxFoldPreOrder(fun,cv,v);
    }
    else
    {
        if(HasRightChild()) RightChild().AuxFoldPreOrder(fun,cv,v);
    }
};


template<typename Data>
void BinaryTree<Data>::Node::AuxFoldPostOrder(FoldFunctor fun, const void* cv, void* v)
{
    if(HasLeftChild())
    {
        LeftChild().AuxFoldPostOrder(fun,cv,v);
        if(HasRightChild()) RightChild().AuxFoldPostOrder(fun,cv,v);
    }
    else
    {
        if(HasRightChild()) RightChild().AuxFoldPostOrder(fun,cv,v);
    }
    fun(this->Element(),cv,v);
};

template<typename Data>
void BinaryTree<Data>::Node::AuxFoldInOrder(FoldFunctor fun, const void* cv, void* v)
{
    if(HasLeftChild())
    {
        LeftChild().AuxFoldInOrder(fun,cv,v);
        fun(this->Element(),cv,v);
        if(HasRightChild()) RightChild().AuxFoldInOrder(fun,cv,v);
    }
    else
    {
        fun(this->Element(),cv,v);
        if(HasRightChild()) RightChild().AuxFoldInOrder(fun,cv,v);
    }
};

template<typename Data>
void BinaryTree<Data>::Node::AuxFoldBreadth(FoldFunctor fun,const void* cv, void* v)
{
    Node* currnode;
    QueueLst<Node*> Queue;
    
    Queue.Enqueue(this);

    while(Queue.Size()!= 0)
    {
        currnode = Queue.Head();

        if(currnode->HasLeftChild()) Queue.Enqueue(&(currnode->LeftChild()));
        if(currnode->HasRightChild()) Queue.Enqueue(&(currnode->RightChild()));

        fun(currnode->Element(),cv,v);

        Queue.Dequeue();
    }
}

template<typename Data>
void BinaryTree<Data>::Node::AuxMapPreOrder(MapFunctor fun, void * v)
{
    fun(this->Element(),v);
    if(HasLeftChild())
    {
        LeftChild().AuxMapPreOrder(fun,v);
        if(HasRightChild()) RightChild().AuxMapPreOrder(fun,v);
    }
    else
    {
        if(HasRightChild()) RightChild().AuxMapPreOrder(fun,v);
    }
}

template<typename Data>
void BinaryTree<Data>::Node::AuxMapPostOrder(MapFunctor fun, void* v)
{
    if(HasLeftChild())
    {
        LeftChild().AuxMapPostOrder(fun,v);
        if(HasRightChild()) RightChild().AuxMapPostOrder(fun,v);
    }
    else
    {
        if(HasRightChild()) RightChild().AuxMapPostOrder(fun,v);
    }
    fun(Element(),v);
};

template<typename Data>
void BinaryTree<Data>::Node::AuxMapInOrder(MapFunctor fun, void* v)
{
    if(HasLeftChild())
    {
        LeftChild().AuxMapInOrder(fun,v);
        fun(Element(),v);
        if(HasRightChild()) RightChild().AuxMapInOrder(fun,v);
    }
    else
    {
        fun(Element(),v);
        if(HasRightChild()) RightChild().AuxMapInOrder(fun,v);
    }
};

template<typename Data>
void BinaryTree<Data>::Node::AuxMapBreadth(MapFunctor fun, void* v)
{
    QueueLst<Node*> Queue;
    
    Queue.Enqueue(this);

    Node* currnode;

    while(Queue.Size()!= 0)
    {
        currnode = Queue.Head();

        if(currnode->HasLeftChild()) Queue.Enqueue(&(currnode->LeftChild()));
        if(currnode->HasRightChild()) Queue.Enqueue(&(currnode->RightChild()));

        fun(currnode->Element(),v);

        Queue.Dequeue();
    }
};


template<typename Data>
void BinaryTree<Data>::FoldPreOrder(FoldFunctor fun , const void* cv, void * v) const
{
    if(size!= 0)
        Root().AuxFoldPreOrder(fun,cv,v);
};

template<typename Data>
void BinaryTree<Data>::FoldPostOrder(FoldFunctor fun , const void* cv, void * v) const
{
    if(size!= 0)
        Root().AuxFoldPostOrder(fun,cv,v);
};

template<typename Data>
void BinaryTree<Data>::FoldInOrder(FoldFunctor fun , const void* cv, void * v) const
{
    if(size!= 0)
        Root().AuxFoldInOrder(fun,cv,v);
};

template<typename Data>
void BinaryTree<Data>::FoldBreadth(FoldFunctor fun,const void* cv, void* v) const
{
    if(size!= 0)
        Root().AuxFoldBreadth(fun ,cv , v);
};

template<typename Data>
void BinaryTree<Data>::Fold(FoldFunctor fun,const void* cv, void* v) const
{
    FoldBreadth(fun,cv,v);
};

template<typename Data>
void BinaryTree<Data>::MapPreOrder(MapFunctor fun, void* v)
{
    if(size!= 0)
        Root().AuxMapPreOrder(fun,v);
};

template<typename Data>
void BinaryTree<Data>::MapPostOrder(MapFunctor fun, void* v)
{
    if(size!= 0)
        Root().AuxMapPostOrder(fun,v);
};

template<typename Data>
void BinaryTree<Data>::MapInOrder(MapFunctor fun, void* v)
{
    if(size!= 0)
        Root().AuxMapInOrder(fun,v);
};

template<typename Data>
void BinaryTree<Data>::MapBreadth(MapFunctor fun, void* v)
{
    if(size!= 0)
        Root().AuxMapBreadth(fun, v);
};

template<typename Data>
void BinaryTree<Data>::Map(MapFunctor fun, void* v)
{
    MapBreadth(fun,v);
};


template<typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& t)
{
    try 
    {
        currElement = &(t.Root()); 
    }
    catch(std::length_error)
    {
        currElement = nullptr;
    }
    root = currElement;
    toVisit = new StackLst<typename BinaryTree<Data>::Node*>();
};

template<typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data>& pi)
{
    currElement = pi.currElement;
    root = pi.root;
    toVisit = new StackLst<typename BinaryTree<Data>::Node*>(*pi.toVisit);
};

template<typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data>&& pi)
{
    toVisit = new StackLst<typename BinaryTree<Data>::Node*>();
    root = currElement = nullptr;
    swap<typename BinaryTree<Data>::Node*>(currElement,pi.currElement);
    swap<typename BinaryTree<Data>::Node*>(root,pi.root);
    swap<StackLst<typename BinaryTree<Data>::Node*>*>(toVisit,pi.toVisit);
};

template<typename Data>
BTPreOrderIterator<Data>::~BTPreOrderIterator()
{
    delete toVisit;
};

template<typename Data>
void BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data>& pi)
{
    *toVisit = *pi.toVisit;
    currElement = pi.currElement;
    root = pi.root;
};

template<typename Data>
void BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data>&& pi)
{
    swap<StackLst<typename BinaryTree<Data>::Node*>*>(toVisit,pi.toVisit);
    swap<typename BinaryTree<Data>::Node*>(currElement,pi.currElement);
    swap<typename BinaryTree<Data>::Node*>(root,pi.root);
};

template<typename Data>
bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data>& pi) const
{
    return (currElement==pi.currElement && *toVisit == *pi.toVisit && *root = *pi.root);
};

template<typename Data>
bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data>& pi) const
{
   return !(*this == pi);
};

template<typename Data>
Data& BTPreOrderIterator<Data>::operator*() const 
{
    if(Terminated()) throw std::out_of_range("Fine esplorazione albero");
    return currElement->Element();
};

template<typename Data>
bool BTPreOrderIterator<Data>::Terminated() const noexcept
{
    return (currElement==nullptr);
};

template<typename Data>
void BTPreOrderIterator<Data>::operator++()
{   
    if (Terminated()) throw std::out_of_range("Fine esplorazione albero");
    if(currElement->HasLeftChild())
    {
        if(currElement->HasRightChild())
            toVisit->Push(&(currElement->RightChild()));
        
        currElement = &(currElement->LeftChild());
    }
    else if(currElement->HasRightChild())
        currElement = &(currElement->RightChild());
    else 
        if(toVisit->Empty()) currElement = nullptr;
        else{ currElement = toVisit->Top(); toVisit->Pop();}
};

template<typename Data>
void BTPreOrderIterator<Data>::Reset() noexcept
{
    currElement = root;
    toVisit->Clear();
};

template<typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& bt) 
{
    toVisit = new StackLst<typename BinaryTree<Data>::Node*>();
    try {root = &bt.Root();}
    catch(std::length_error) { root = nullptr;}
    currElement = root;

    if(currElement!= nullptr) GoToMin();
};

template<typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data>& bt) 
{
    toVisit = new StackLst<typename BinaryTree<Data>::Node*>(*bt.toVisit);
    root = bt.root;
    currElement = bt.currElement;
};

template<typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data>&& bt) 
{
    toVisit = new StackLst<typename BinaryTree<Data>::Node*>();
    currElement = root = nullptr;
    swap<typename BinaryTree<Data>::Node*>(currElement,bt.currElement);
    swap<typename BinaryTree<Data>::Node*>(root,bt.root);
    swap<StackLst<typename BinaryTree<Data>::Node*>*>(toVisit,bt.toVisit);
};

template<typename Data>
BTInOrderIterator<Data>::~BTInOrderIterator()
{
    delete toVisit;
};

template<typename Data>
void BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data>& bt)
{
    *toVisit = *bt.toVisit;
    currElement = bt.currElement;
    root = bt.root;

};

template<typename Data>
void BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data>&& bt)
{
    swap<StackLst<typename BinaryTree<Data>::Node*>*>(toVisit,bt.toVisit);
    swap<typename BinaryTree<Data>::Node*>(currElement,bt.currElement);
    swap<typename BinaryTree<Data>::Node*>(root,bt.root);
};  

template<typename Data>
bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data>& bt)const
{
    return (*toVisit == *bt.toVisit && currElement == bt.currElement && root == bt.root);
};

template<typename Data>
bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data>& bt)const
{
    return !(*this == bt);
};

template<typename Data>
Data& BTInOrderIterator<Data>::operator*() const 
{
    if(Terminated()) throw std::out_of_range("Fine esplorazione albero");
    return currElement->Element();
};

template<typename Data>
bool BTInOrderIterator<Data>::Terminated() const noexcept
{
    return (toVisit->Empty() && currElement == nullptr);
};

template<typename Data>
void BTInOrderIterator<Data>::GoToMin()
{
    while(currElement->HasLeftChild())
    {
        toVisit->Push(currElement);
        currElement = &(currElement->LeftChild());
    }
};

template<typename Data>
void BTInOrderIterator<Data>::operator++()
{
    if(Terminated()) throw std::out_of_range("Fine esplorazione albero");
    if (currElement->HasRightChild())
    {
        currElement = &(currElement->RightChild());
        GoToMin();
    }
    else
    {
        if(!toVisit->Empty()) {currElement = toVisit->Top(); toVisit->Pop();}
        else currElement = nullptr;
    }
};

template<typename Data>
void BTInOrderIterator<Data>::Reset()noexcept
{
    toVisit->Clear();
    currElement = root;

    if(currElement != nullptr) GoToMin();
}

template<typename Data>
void BTBreadthIterator<Data>::AheadAndGetChildren()
{
    currElement = toVisit->Head();
    toVisit->Dequeue();
    if(currElement->HasLeftChild()) toVisit->Enqueue(&(currElement->LeftChild()));
    if(currElement->HasRightChild()) toVisit->Enqueue(&(currElement->RightChild()));
};

template<typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& bt)
{
    toVisit = new QueueLst<typename BinaryTree<Data>::Node*>();
    try {root = &bt.Root();} catch(std::length_error) { root = currElement = nullptr; }

    if(root != nullptr)
    {
        toVisit->Enqueue(root);
        AheadAndGetChildren();
    }
};

template<typename Data>
void BTBreadthIterator<Data>::operator++()
{
    if(Terminated()) throw std::out_of_range("Fine esplorazione albero");
    if(!toVisit->Empty()) AheadAndGetChildren();
    else currElement = nullptr;
};

template<typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data>& bt) 
{
    toVisit = new QueueLst<typename BinaryTree<Data>::Node*>(*bt.toVisit);
    root = bt.root;
    currElement = bt.currElement;
};

template<typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data>&& bt) 
{
    toVisit = new QueueLst<typename BinaryTree<Data>::Node*>();
    currElement = root = nullptr;
    swap<typename BinaryTree<Data>::Node*>(currElement,bt.currElement);
    swap<typename BinaryTree<Data>::Node*>(root,bt.root);
    swap<QueueLst<typename BinaryTree<Data>::Node*>*>(toVisit,bt.toVisit);
};

template<typename Data>
BTBreadthIterator<Data>::~BTBreadthIterator()
{
    delete toVisit;
};

template<typename Data>
void BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data>& bt)
{

    *toVisit = *bt.toVisit;
    currElement = bt.currElement;
    root = bt.root;

};

template<typename Data>
void BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data>&& bt)
{
    swap<QueueLst<typename BinaryTree<Data>::Node*>*>(toVisit,bt.toVisit);
    swap<typename BinaryTree<Data>::Node*>(currElement,bt.currElement);
    swap<typename BinaryTree<Data>::Node*>(root,bt.root);
};  

template<typename Data>
bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data>& bt)const
{
    return (*toVisit == *bt.toVisit && currElement == bt.currElement && root == bt.root);
};

template<typename Data>
bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data>& bt)const
{
    return !(*this == bt);
};

template<typename Data>
Data& BTBreadthIterator<Data>::operator*() const 
{
    if(Terminated()) throw std::out_of_range("Fine esplorazione albero");
    return currElement->Element();
};

template<typename Data>
bool BTBreadthIterator<Data>::Terminated() const noexcept
{
    return (toVisit->Empty() && currElement == nullptr);
};

template<typename Data>
void BTBreadthIterator<Data>::Reset()noexcept
{
    toVisit->Clear();
    
    if(root != nullptr) 
    {
        toVisit->Enqueue(root);
        AheadAndGetChildren();
    }
};

template<typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data>& bt) 
{
    toVisit = new StackLst<typename BinaryTree<Data>::Node*>(*bt.toVisit);
    root = bt.root;
    currElement = bt.currElement;
};

template<typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data>&& bt) 
{
    toVisit = new StackLst<typename BinaryTree<Data>::Node*>();
    currElement = root = nullptr;
    swap<typename BinaryTree<Data>::Node*>(currElement,bt.currElement);
    swap<typename BinaryTree<Data>::Node*>(root,bt.root);
    swap<StackLst<typename BinaryTree<Data>::Node*>*>(toVisit,bt.toVisit);
};

template<typename Data>
BTPostOrderIterator<Data>::~BTPostOrderIterator()
{
    delete toVisit;
};

template<typename Data>
void BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data>& bt)
{

    *toVisit = *bt.toVisit;
    currElement = bt.currElement;
    root = bt.root;

};

template<typename Data>
void BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data>&& bt)
{
    swap<StackLst<typename BinaryTree<Data>::Node*>*>(toVisit,bt.toVisit);
    swap<typename BinaryTree<Data>::Node*>(currElement,bt.currElement);
    swap<typename BinaryTree<Data>::Node*>(root,bt.root);
};  

template<typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data>& bt)const
{
    return (*toVisit == *bt.toVisit && currElement == bt.currElement && root == bt.root);
};

template<typename Data>
bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data>& bt)const
{
    return !(*this == bt);
};

template<typename Data>
Data& BTPostOrderIterator<Data>::operator*() const 
{
    if(Terminated()) throw std::out_of_range("Fine esplorazione albero");
    return currElement->Element();
};

template<typename Data>
bool BTPostOrderIterator<Data>::Terminated() const noexcept
{
    return (toVisit->Empty() && currElement == nullptr);
};

template<typename Data>
void BTPostOrderIterator<Data>::MinLeaf()
{
    while(!currElement->IsLeaf())
    {
        toVisit->Push(currElement);
        if(currElement->HasLeftChild()) currElement = &(currElement->LeftChild());
        else currElement = &(currElement->RightChild());
    }
};

template<typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& bt)
{
    toVisit = new StackLst<typename BinaryTree<Data>::Node*>();
    try {root = currElement = &bt.Root();} catch(std::length_error){root = currElement = nullptr;}

    if(currElement != nullptr)
    {
        MinLeaf();
    }

};

template<typename Data>
void BTPostOrderIterator<Data>::operator++()
{
    if(Terminated()) throw std::out_of_range("Fine esplorazione albero");
    if(!toVisit->Empty())
    {    
        if (toVisit->Top()->HasLeftChild() && currElement == &(toVisit->Top()->LeftChild())) 
        {
            if(toVisit->Top()->HasRightChild()) 
            {
                currElement = &(toVisit->Top()->RightChild());
                MinLeaf();
            }
            else
            {
                currElement = toVisit->Top();
                toVisit->Pop();
            }
        }
        else
        {
            currElement = toVisit->Top();
            toVisit->Pop();
        }
    }
    else
    {
        currElement = nullptr;
    }
};

template<typename Data>
void BTPostOrderIterator<Data>::Reset() noexcept
{
    toVisit->Clear();
    currElement = root;

    if(currElement != nullptr) 
    {
        MinLeaf();
    }
};

}