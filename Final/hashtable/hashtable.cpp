#include <typeinfo>


namespace lasd {


    template<typename Data>
    ulong Hash<Data>::operator()(const Data& d)const noexcept
    {
        int a;
        double b;
        string c;
        if(typeid(d).name() == typeid(a).name())
            {
                // cout<<"Sono un intero!-"<<endl; 
                return ((int&)d)*((int&)d); 
            }
        else if(typeid(d).name() == typeid(b).name())
        {   
            int base = floor(((double&)d));
            // cout<<"Sono un double!-";
            return base*base;
        }
        else if(typeid(d).name() == typeid(c).name())
        {

            // cout<<"Sono una stringa!-";
            ulong sum = 0;
            string& drf = ((string&) d);
            for(ulong i = 0; i<drf.length(); i++)
                sum+= 200 * (int)(drf[i]);
            return sum;
        }
    };


    template<typename Data>
    HashTable<Data>::HashTable()
    {
        mt19937 genh(random_device{}());
        uniform_int_distribution<ulong> disth(1,p-1);
        a = disth(genh);
        if(a%2 == 0) if(a == p-1) a--; else a++;
        b = disth(genh); 
        hashsize = 256;
    };


}
