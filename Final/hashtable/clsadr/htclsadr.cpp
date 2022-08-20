
namespace lasd 
{

    template<typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr()
    {
        tavola = new Vector<BST<Data>>(hashsize);
    }

    template<typename Data>
    HashTableClsAdr<Data>::~HashTableClsAdr()
    {
        delete tavola;
    }

    template<typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const ulong sz)
    {
        tavola = new Vector<BST<Data>>(hashsize);
        if (sz !=0)
            hashsize = sz;
        tavola->Resize(hashsize);
    };

    template<typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const LinearContainer<Data>& lc)
    {
        tavola = new Vector<BST<Data>>(hashsize);
        if(!lc.Empty())
        {
            for(ulong i = 0; i < lc.Size(); i++)
                Insert(lc[i]);
        }
    };

    template<typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const ulong sz, const LinearContainer<Data>& lc)
    {
        tavola = new Vector<BST<Data>>(hashsize);
        if (sz !=0)
            hashsize = sz;
        tavola->Resize(hashsize);
        DictionaryContainer<Data>::Insert(lc);
        // if(!lc.Empty())
        // {
        //     for(ulong i = 0; i < lc.Size(); i++)
        //         Insert(lc[i]);
        // }
    }; 

    template<typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data>& ht)
    {
        tavola = new Vector<BST<Data>>(hashsize);
        hashsize = ht.hashsize;
        size = ht.size;
        HashTable<Data>::a = ht.a;
        HashTable<Data>::b = ht.b;
        *tavola = *ht.tavola; 
        // tavola->Resize(hashsize);
        // if(!ht.Empty())
        //     for(ulong i = 0; i<hashsize; i++)
        //         if(!ht.tavola->operator[](i).Empty())
        //         {
        //             BTBreadthIterator<Data> itr(ht.tavola->operator[](i));
        //             while(!itr.Terminated())
        //             {
        //                 Insert(*itr);
        //                 ++itr;
        //             }
        //         }
    };

    template<typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr<Data>&& ht)
    {
        tavola = new Vector<BST<Data>>(hashsize);
        swap<Vector<BST<Data>>*>(tavola, ht.tavola);
        swap<ulong>(HashTable<Data>::a, ht.a);
        swap<ulong>(HashTable<Data>::b, ht.b);
        swap<ulong>(size, ht.size);
        swap<ulong>(hashsize,ht.hashsize);
    };


    template<typename Data>
    void HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data>& ht)
    {
        HashTable<Data>::operator=(ht);
        *tavola = *ht.tavola;

        // if(!ht.Empty())
        //     for(ulong i = 0; i<hashsize; i++)
        //         if(!ht.tavola->operator[](i).Empty())
        //         {
        //             BTBreadthIterator<Data> itr(ht.tavola->operator[](i));
        //             while(!itr.Terminated())
        //             {
        //                 Insert(*itr);
        //                 ++itr;
        //             }
        //         }
    };

    template<typename Data>
    void HashTableClsAdr<Data>::operator=(HashTableClsAdr<Data>&& ht)
    {
        HashTable<Data>::operator=(std::move(ht));
        swap<Vector<BST<Data>>*>(tavola, ht.tavola);
    };

    template<typename Data>
    bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr<Data>& ht) const
    {
        bool res;
        ulong i = 0;
        if(size == ht.size)
        {
            res = true;
            while(i < hashsize && res)
            {
                if(!tavola->operator[](i).Empty())
                {
                    BTBreadthIterator<Data> itr(tavola->operator[](i));
                    while(!itr.Terminated() && res == true) {if(!ht.Exists(*itr)) res = false; ++itr;}
                }
                i++;
            }
            return res;
        }
        else return false;
    };

    template<typename Data>
    bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr<Data>& ht) const
    {
        return !(*this == ht);
    };

    template<typename Data>
    void HashTableClsAdr<Data>::Resize(const ulong& sz)
    {
        HashTableClsAdr<Data> newtab(sz);

        for (ulong i = 0; i<hashsize; i++)
        {
            if(!tavola->operator[](i).Empty())
            {
                BTBreadthIterator<Data> itr(tavola->operator[](i));
                while(!itr.Terminated()) {newtab.Insert(*itr); ++itr;}
            }
        }

        *this = std::move(newtab);
    };

    template<typename Data>
    bool HashTableClsAdr<Data>::Insert(const Data& dat)
    {
        if(tavola->operator[](HashKey(dat)).Insert(dat)) {size++; return true;}
        else return false;
    };

    template<typename Data>
    bool HashTableClsAdr<Data>::Insert(Data&& dat)
    {
       if(tavola->operator[](HashKey(dat)).Insert(std::move(dat))){size++; return true;}
       else return false;
    };

    template<typename Data>
    bool HashTableClsAdr<Data>::Remove(const Data& dat)
    {
       if(tavola->operator[](HashKey(dat)).Remove(dat)){size--; return true;}
       else return false;
    };

    template<typename Data>
    bool HashTableClsAdr<Data>::Exists(const Data& dat) const noexcept
    {
        return tavola->operator[](HashKey(dat)).Exists(dat);
    };

    template<typename Data>
    void HashTableClsAdr<Data>::Clear() noexcept
    {
        tavola->Clear();
        tavola->Resize(256);
        hashsize = 256;
        size = 0;
    };

    template<typename Data>
    void HashTableClsAdr<Data>::Map(MapFunctor fun, void * vp)
    {
        for(ulong i = 0; i < hashsize; i++)
        {
            tavola->operator[](i).Map(fun,vp);
        }
    };

    template<typename Data>
    void HashTableClsAdr<Data>::Fold(FoldFunctor fun, const void * cv,void * vp) const
    {
        for(ulong i = 0; i < hashsize; i++)
        {
            tavola->operator[](i).Fold(fun,cv,vp);
        }
    };

}

