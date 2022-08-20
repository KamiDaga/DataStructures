
namespace lasd {


template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr()
{
    infotab = new Vector<char>(hashsize); 
    elementi = new Vector<Data>(hashsize);
};

template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong& sz)
{
    infotab = new Vector<char>(hashsize); 
    elementi = new Vector<Data>(hashsize);
    ulong newsize = 2;
    while(newsize < sz) newsize = newsize* 2;
    hashsize = newsize;
    infotab->Resize(newsize);
    elementi->Resize(newsize);
};


template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const LinearContainer<Data>& lc)
{
    infotab = new Vector<char>(hashsize); 
    elementi = new Vector<Data>(hashsize);
    ulong newsize = 2;
    while(newsize < lc.Size()) newsize = newsize* 2;
    hashsize = newsize;

    infotab->Resize(hashsize);
    elementi->Resize(hashsize);

    if(!lc.Empty())
        for (ulong i = 0; i< lc.Size(); i++)
           Insert(lc[i]);
};



template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong& sz,const LinearContainer<Data>& lc )
{
    infotab = new Vector<char>(hashsize); 
    elementi = new Vector<Data>(hashsize);
    ulong newsize = 2;
    while(newsize < std::max(lc.Size(), sz)) newsize = newsize* 2;
    hashsize = newsize;

    infotab->Resize(hashsize);
    elementi->Resize(hashsize);

    Insert(lc);
};


template<typename Data>
HashTableOpnAdr<Data>:: HashTableOpnAdr(const HashTableOpnAdr<Data>& ht)
{
    infotab = new Vector<char>(hashsize); 
    elementi = new Vector<Data>(hashsize);
    hashsize = ht.hashsize;

    infotab->Resize(hashsize);
    elementi->Resize(hashsize);

    for(ulong i = 0; i<hashsize; i++)
        if(((int)ht.infotab->operator[](i)) == 1) Insert(ht.elementi->operator[](i));  
};




template<typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr<Data>&& ht)
{
    infotab = new Vector<char>(hashsize); 
    elementi = new Vector<Data>(hashsize);
    swap<ulong>(size, ht.size);
    swap<ulong>(hashsize, ht.hashsize);
    swap<ulong>(HashTable<Data>::b, ht.b);
    swap<ulong>(HashTable<Data>::a, ht.a);
    swap<Vector<char>*>(infotab,ht.infotab);
    swap<Vector<Data>*>(elementi, ht.elementi);
};


template<typename Data>
HashTableOpnAdr<Data>::~HashTableOpnAdr()
{
    delete infotab;
    delete elementi;
};


template<typename Data>
void HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr<Data>& ht)
{
    Clear();
    Resize(ht.hashsize);    

    for(ulong i = 0; i<ht.hashsize; i++)
        if(((int)ht.infotab->operator[](i)) == 1) Insert(ht.elementi->operator[](i));  

};

template<typename Data>
void HashTableOpnAdr<Data>::operator=(HashTableOpnAdr<Data>&& ht)
{
    HashTable<Data>::operator=(std::move(ht));
    swap<Vector<Data>*>(elementi, ht.elementi);
    swap<Vector<char>*>(infotab, ht.infotab);
};

template<typename Data>
bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr<Data>& ht)const
{
    bool res = true;
    ulong i = 0;
    if(size == ht.size)
    {
        if(size == 0) return true;
        while(i<hashsize && res)
        {
            if(((int)infotab->operator[](i)) == 1) if(!ht.Exists(elementi->operator[](i))) res = false;  
            i++;
        }
        return res;
    }
    else return false;
};

template<typename Data>
bool HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr<Data>& ht)const
{
    return !(*this == ht);
};


template<typename Data>
bool HashTableOpnAdr<Data>::Insert(const Data& dat)
{
    ulong location = FindEmpty(dat);
    if(location != hashsize + 1)
    {
        infotab->operator[](location) = (char)1;  
        elementi->operator[](location) = dat;
        size++;
        return true;
    }
    else
    {
        return false;
    }
};

template<typename Data>
bool HashTableOpnAdr<Data>::Insert(Data&& dat)
{
    ulong location = FindEmpty(dat);
    if(location != hashsize + 1)
    {
        infotab->operator[](location) = (char)1;  
        elementi->operator[](location) = std::move(dat);
        size++;
        return true;
    }
    else
    {
        return false;
    }
};

template<typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data& dat)
{
    ulong loc;
    Remove2(dat, loc);
    if(loc != hashsize+1)
    {
        size--;
        if(nonusable+size >= hashsize/2) Resize(hashsize);
        return true;
    }
    else return false;
};

template<typename Data>
bool HashTableOpnAdr<Data>::Exists(const Data& dat)const noexcept
{
    ulong location = Find(dat);
    if(location != hashsize + 1)
    {
        return true;
    }
    else
    {
        return false;
    }
};

template<typename Data>
void HashTableOpnAdr<Data>::Resize(const ulong& sz)
{
    HashTableOpnAdr<Data> temp(sz);
    for(ulong i = 0; i< hashsize; i++)
        if((int)infotab->operator[](i) == 1) temp.Insert(elementi->operator[](i));  

    *this = std::move(temp);
};

template<typename Data>
void HashTableOpnAdr<Data>::Map(MapFunctor fun, void * ptr)
{
    for(ulong i = 0; i< hashsize; i++)
        if(((int)infotab->operator[](i)) == 1) fun(elementi->operator[](i), ptr);  
};


template<typename Data>
void HashTableOpnAdr<Data>::Fold(FoldFunctor fun, const void* cptr , void* ptr)const
{
    for(ulong i = 0; i< hashsize; i++)
        if(((int)infotab->operator[](i)) == 1) fun(elementi->operator[](i), cptr, ptr);  
};

template<typename Data>
void HashTableOpnAdr<Data>::Clear()noexcept
{
    infotab->Clear();
    infotab->Resize(256);
    elementi->Clear();
    elementi->Resize(256);
    hashsize = 256;
    size = 0;
};

template<typename Data>
ulong HashTableOpnAdr<Data>::Find(const Data& dat) const
{
    bool res = false;
    ulong base;
    ulong triedplace = base = HashKey(dat);


    res = ((int)infotab->operator[](triedplace) == 1 && elementi->operator[](triedplace) == dat);
    for(ulong i = 1; !res && (int)infotab->operator[](triedplace) != 0; i++)
    {
        triedplace = (probe(i) + base) % hashsize;
        res = ((int)infotab->operator[](triedplace) == 1 && elementi->operator[](triedplace) == dat);
    }

    if(res) return triedplace;
    else
        return hashsize+1;
};

template<typename Data>
ulong HashTableOpnAdr<Data>::FindEmpty(const Data& dat)
{
    bool res;
    ulong i = 1;
    ulong base;
    ulong triedplace;

    if(size>= hashsize/2) Resize(hashsize*2);
    base = HashKey(dat);
    triedplace = base;
    res = (((int)infotab->operator[](triedplace))== 1 && elementi->operator[](triedplace) == dat);  
    for(ulong i = 1; !res && ((int)infotab->operator[](triedplace)) != 0; i++)  
    {
        triedplace = (probe(i) + base) % hashsize;
        res = (((int)infotab->operator[](triedplace)) == 1 && elementi->operator[](triedplace) == dat);  
    }
    if(res) return hashsize+1;
    else return triedplace;

};


template<typename Data>
void HashTableOpnAdr<Data>::Remove2(const Data& dat, ulong& location)
{
    location = Find(dat);
    if(location != hashsize+1)
        {infotab->operator[](location) = (char)2; nonusable++;}
};


}

