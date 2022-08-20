#include <iostream>
#include <random>
#include "../vector/vector.hpp"
#include "../list/list.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../stack/vec/stackvec.hpp"
#include "../queue/lst/queuelst.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../binarytree/vec/binarytreevec.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../bst/bst.hpp"
#include "../hashtable/hashtable.hpp"
#include "../hashtable/opnadr/htopnadr.hpp"
#include "../hashtable/clsadr/htclsadr.hpp"

using namespace std;

const string CHARACTERS = "0123456789abcdefghilmnopqrstuvzABCDEFGHILMNOPQRSTUVZ!@#$%&():<>";
const string init = "";

mt19937 gen(random_device{}());
uniform_int_distribution<int> dist(1,450);
uniform_int_distribution<int> distAndNeg(-450,450);
uniform_int_distribution<int> distUnder(1,90);
uniform_int_distribution<int> randomstop(0,10);
uniform_int_distribution<int> distC(0,CHARACTERS.size() -1);

enum class Struttura {Vettore, Lista, Stack, Queue, BT, BST, Hashtable, Exit, Invalid};
enum class Tipo {Int, Double, String, Invalid, Exit};
enum class Operazione {Front, Back, FullContainer, CheckExist, ProprietaryFoldFun, ProprietaryMapFun, LibFunct, Top, TopNPop, EmptinessCheck, CheckDim, Clear, Push, End, Invalid};

template<typename Data>
void VisualizeContainer(Data& d, void* v)        
{
    cout<<d<<" ";
}

void TripleThemUp(int& d, void*v)
{
    d = 3*d;
}

void MultiplyByItself2Times(double& d, void* v)
{
    d = trunc(pow(d,3) *100)/100;
}

void AppendV(string& d, void* v)
{
    d = *(static_cast<string*>(v)) + d;
}

void MulIfLessThanN(const int& d, const void* n, void* res)
{
    if (d < *(static_cast<const int*>(n)))  *(static_cast<int*>(res)) = *(static_cast<int*>(res)) * d;
}

void SumIfHigherThanN(const double& d, const void* n, void* res)
{
    if(d>*(static_cast<const double*>(n))) *(static_cast<double*>(res)) = *(static_cast<double*>(res)) + d;
}

void DoubleThemUp(int& d, void* v)
{
    d = 2*d;
}

void SumIfLessThanN(const int& d, const void* n, void* res)
{
    if (d < *(static_cast<const int*>(n)))  *(static_cast<int*>(res)) = *(static_cast<int*>(res)) + d;
}

void MultiplyByItself(double& d, void* v)
{
    d = trunc(pow(d,2) *100)/100;
}

void MultiplyIfHigherThanN(const double& d, const void* n, void* res)
{
    if(d>*(static_cast<const double*>(n))) *(static_cast<double*>(res)) = *(static_cast<double*>(res)) * d;
}

void AppendIfLessThanN(const string& s, const void* n, void* res)
{
    if(s.size()<= *((int*)n)) (static_cast<string*>(res))->operator+=(s);
}

void Uppercase(string& s, void* n)
{
    for (ulong i = 0; i<s.length();i++)
    {
        if (int(s[i]) >= 97 && int(s[i])<=122) s[i] = (char)(int(s[i]) - 32);
    }
}


void TestHTC(Tipo tp, ulong dim)
{
    int choice = 1;
    if(tp == Tipo::Int)
    {
        lasd::HashTableClsAdr<int> playedHT(dim);
        for(ulong i = 0; i<dim; i++)
        {
            playedHT.Insert(distAndNeg(gen));
        }
        int inserimento;
        int res = 0;
        int choice=1;
        while(choice != 0)
        {
            cout<<"1. Inserisci un elemento"<<endl;
            cout<<"2. Rimuovi un elemento"<<endl;
            cout<<"3. Controlla l'esistenza di un valore"<<endl;
            cout<<"4. Somma tutti i valori minori di uno arbitrario"<<endl;
            cout<<"5. Visualizza tutti gli elementi della tavola"<<endl;
            cout<<"0. Esci dal test"<<endl;
            cin>>choice;

            switch (choice)
            {
            case 1:
                cout<<"Quale elemento va inserito?"<<endl;
                cin>>inserimento;
                playedHT.Insert(inserimento);
                break;
            case 2:
                cout<<"Quale elemento si desidera rimuovere?"<<endl;
                cin>>inserimento;
                playedHT.Remove(inserimento);
                break;
            case 3:
                cout<<"Di quale elemento si controlla l'esistenza?"<<endl;
                cin>>inserimento;
                cout<<"L'elemento "<<inserimento<<" "<<(playedHT.Exists(inserimento)? "" : "non ")<<"esiste!"<<endl;
                break;
            case 4:
                cout<<"Qual'e' il valore in input? ";
                cin>>inserimento;
                res = 0;
                playedHT.Fold(SumIfLessThanN, &inserimento, &res);
                cout<<"Il risulato e' "<<res<<endl;
                break;
            case 5:
                cout<<"Stampo tutti gli elementi:\n";
                playedHT.Map(VisualizeContainer<int>,nullptr);
                cout<<endl<<endl;
                break;
            default:
                break;
            }
        }
    }

    else if(tp == Tipo::Double)
    {
        lasd::HashTableOpnAdr<double> playedHT(dim);
        for(ulong i = 0; i<dim; i++)
        {
            playedHT.Insert(trunc(((double) distAndNeg(gen)/distUnder(gen)) * 100) / 100);
        }
        double inserimento;
        double res = 1;
        int choice=1;
        while(choice != 0)
        {
            cout<<"1. Inserisci un elemento"<<endl;
            cout<<"2. Rimuovi un elemento"<<endl;
            cout<<"3. Controlla l'esistenza di un valore"<<endl;
            cout<<"4. Prodotto di tutti i valori maggiori di uno arbitrario"<<endl;
            cout<<"5. Visualizza tutti gli elementi della tavola"<<endl;
            cout<<"0. Esci dal test"<<endl;
            cin>>choice;

            switch (choice)
            {
            case 1:
                cout<<"Quale elemento va inserito?"<<endl;
                cin>>inserimento;
                playedHT.Insert(inserimento);
                break;
            case 2:
                cout<<"Quale elemento si desidera rimuovere?"<<endl;
                cin>>inserimento;
                playedHT.Remove(inserimento);
                break;
            case 3:
                cout<<"Di quale elemento si controlla l'esistenza?"<<endl;
                cin>>inserimento;
                cout<<"L'elemento "<<inserimento<<" "<<(playedHT.Exists(inserimento)? "" : "non ")<<"esiste!"<<endl;
                break;
            case 4:
                cout<<"Qual'e' il valore in input? ";
                cin>>inserimento;
                res = 0;
                playedHT.Fold(MultiplyIfHigherThanN, &inserimento, &res);
                cout<<"Il risulato e' "<<res<<endl;
                break;
            case 5:
                cout<<"Stampo tutti gli elementi:\n";
                playedHT.Map(VisualizeContainer<double>,nullptr);
                cout<<endl<<endl;
                break;
            default:
                break;
            }
        }
    }

    else if(tp == Tipo::String)
    {
        lasd::HashTableOpnAdr<string> playedHT;
        string inserimento;
        int ins;
        int lunghezzamax;
        for(ulong i = 0; i<dim; i++)
        {
            inserimento = init;
            lunghezzamax = 1;
            inserimento += CHARACTERS[distC(gen)];
            while(randomstop(gen) != 0 && lunghezzamax<10)
                {inserimento += CHARACTERS[distC(gen)]; lunghezzamax++;}
            playedHT.Insert(inserimento);
        }
        string res = init;
        int choice=1;
        while(choice != 0)
        {
            cout<<"1. Inserisci un elemento"<<endl;
            cout<<"2. Rimuovi un elemento"<<endl;
            cout<<"3. Controlla l'esistenza di un valore"<<endl;
            cout<<"4. Concatena tutti i valori con lunghezza minore di un numero arbitrario"<<endl;
            cout<<"5. Visualizza tutti gli elementi della tavola"<<endl;
            cout<<"0. Esci dal test"<<endl;
            cin>>choice;

            switch (choice)
            {
            case 1:
                cout<<"Quale elemento va inserito?"<<endl;
                cin>>inserimento;
                playedHT.Insert(inserimento);
                break;
            case 2:
                cout<<"Quale elemento si desidera rimuovere?"<<endl;
                cin>>inserimento;
                playedHT.Remove(inserimento);
                break;
            case 3:
                cout<<"Di quale elemento si controlla l'esistenza?"<<endl;
                cin>>inserimento;
                cout<<"L'elemento "<<inserimento<<" "<<(playedHT.Exists(inserimento)? "" : "non ")<<"esiste!"<<endl;
                break;
            case 4:
                cout<<"Qual'e' il valore in input? ";
                cin>>ins;
                res = init;
                playedHT.Fold(AppendIfLessThanN, &ins, &res);
                cout<<"Il risulato e' "<<res<<endl;
                break;
            case 5:
                cout<<"Stampo tutti gli elementi:\n";
                playedHT.Map(VisualizeContainer<string>,nullptr);
                cout<<endl<<endl;
                break;
            default:
                break;
            }
        }
    }
}

void TestHTO(Tipo tp, ulong dim)
{
    int choice = 1;
    if(tp == Tipo::Int)
    {
        lasd::HashTableOpnAdr<int> playedHT(dim);
        for(ulong i = 0; i<dim; i++)
        {
            playedHT.Insert(distAndNeg(gen));
        }
        int inserimento;
        int res = 0;
        int choice=1;
        while(choice != 0)
        {
            cout<<"1. Inserisci un elemento"<<endl;
            cout<<"2. Rimuovi un elemento"<<endl;
            cout<<"3. Controlla l'esistenza di un valore"<<endl;
            cout<<"4. Somma tutti i valori minori di uno arbitrario"<<endl;
            cout<<"5. Visualizza tutti gli elementi della tavola"<<endl;
            cout<<"0. Esci dal test"<<endl;
            cin>>choice;

            switch (choice)
            {
            case 1:
                cout<<"Quale elemento va inserito?"<<endl;
                cin>>inserimento;
                playedHT.Insert(inserimento);
                break;
            case 2:
                cout<<"Quale elemento si desidera rimuovere?"<<endl;
                cin>>inserimento;
                playedHT.Remove(inserimento);
                break;
            case 3:
                cout<<"Di quale elemento si controlla l'esistenza?"<<endl;
                cin>>inserimento;
                cout<<"L'elemento "<<inserimento<<" "<<(playedHT.Exists(inserimento)? "" : "non ")<<"esiste!"<<endl;
                break;
            case 4:
                cout<<"Qual'e' il valore in input? ";
                cin>>inserimento;
                res = 0;
                playedHT.Fold(SumIfLessThanN, &inserimento, &res);
                cout<<"Il risulato e' "<<res<<endl;
                break;
            case 5:
                cout<<"Stampo tutti gli elementi:\n";
                playedHT.Map(VisualizeContainer<int>,nullptr);
                cout<<endl<<endl;
                break;
            default:
                break;
            }
        }
    }

    else if(tp == Tipo::Double)
    {
        lasd::HashTableOpnAdr<double> playedHT(dim);
        for(ulong i = 0; i<dim; i++)
        {
            playedHT.Insert(trunc(((double) distAndNeg(gen)/distUnder(gen)) * 100) / 100);
        }
        double inserimento;
        double res = 1;
        int choice=1;
        while(choice != 0)
        {
            cout<<"1. Inserisci un elemento"<<endl;
            cout<<"2. Rimuovi un elemento"<<endl;
            cout<<"3. Controlla l'esistenza di un valore"<<endl;
            cout<<"4. Prodotto di tutti i valori maggiori di uno arbitrario"<<endl;
            cout<<"5. Visualizza tutti gli elementi della tavola"<<endl;
            cout<<"0. Esci dal test"<<endl;
            cin>>choice;

            switch (choice)
            {
            case 1:
                cout<<"Quale elemento va inserito?"<<endl;
                cin>>inserimento;
                playedHT.Insert(inserimento);
                break;
            case 2:
                cout<<"Quale elemento si desidera rimuovere?"<<endl;
                cin>>inserimento;
                playedHT.Remove(inserimento);
                break;
            case 3:
                cout<<"Di quale elemento si controlla l'esistenza?"<<endl;
                cin>>inserimento;
                cout<<"L'elemento "<<inserimento<<" "<<(playedHT.Exists(inserimento)? "" : "non ")<<"esiste!"<<endl;
                break;
            case 4:
                cout<<"Qual'e' il valore in input? ";
                cin>>inserimento;
                res = 0;
                playedHT.Fold(MultiplyIfHigherThanN, &inserimento, &res);
                cout<<"Il risulato e' "<<res<<endl;
                break;
            case 5:
                cout<<"Stampo tutti gli elementi:\n";
                playedHT.Map(VisualizeContainer<double>,nullptr);
                cout<<endl<<endl;
                break;
            default:
                break;
            }
        }
    }

    else if(tp == Tipo::String)
    {
        lasd::HashTableOpnAdr<string> playedHT;
        string inserimento;
        int ins;
        int lunghezzamax;
        for(ulong i = 0; i<dim; i++)
        {
            inserimento = init;
            lunghezzamax = 1;
            inserimento += CHARACTERS[distC(gen)];
            while(randomstop(gen) != 0 && lunghezzamax<10)
                {inserimento += CHARACTERS[distC(gen)]; lunghezzamax++;}
            playedHT.Insert(inserimento);
        }
        string res = init;
        int choice=1;
        while(choice != 0)
        {
            cout<<"1. Inserisci un elemento"<<endl;
            cout<<"2. Rimuovi un elemento"<<endl;
            cout<<"3. Controlla l'esistenza di un valore"<<endl;
            cout<<"4. Concatena tutti i valori con lunghezza minore di un numero arbitrario"<<endl;
            cout<<"5. Visualizza tutti gli elementi della tavola"<<endl;
            cout<<"0. Esci dal test"<<endl;
            cin>>choice;

            switch (choice)
            {
            case 1:
                cout<<"Quale elemento va inserito?"<<endl;
                cin>>inserimento;
                playedHT.Insert(inserimento);
                break;
            case 2:
                cout<<"Quale elemento si desidera rimuovere?"<<endl;
                cin>>inserimento;
                playedHT.Remove(inserimento);
                break;
            case 3:
                cout<<"Di quale elemento si controlla l'esistenza?"<<endl;
                cin>>inserimento;
                cout<<"L'elemento "<<inserimento<<" "<<(playedHT.Exists(inserimento)? "" : "non ")<<"esiste!"<<endl;
                break;
            case 4:
                cout<<"Qual'e' il valore in input? ";
                cin>>ins;
                res = init;
                playedHT.Fold(AppendIfLessThanN, &ins, &res);
                cout<<"Il risulato e' "<<res<<endl;
                break;
            case 5:
                cout<<"Stampo tutti gli elementi:\n";
                playedHT.Map(VisualizeContainer<string>,nullptr);
                cout<<endl<<endl;
                break;
            default:
                break;
            }
        }
    }
}

void TestBST(Tipo tp, ulong dim)
{
    int choice = 1;

    if(tp == Tipo::Int)
    {   
        lasd::BST<int> playedBst;
        for(ulong i = 0; i<dim; i++)
        {
            playedBst.Insert(distAndNeg(gen));
        }

        int inserimento;
        int risultato;
        while(choice != 0)
        {    
            cout<<"1. Inserisci un elemento"<<endl;
            cout<<"2. Rimuovi un elemento"<<endl;
            cout<<"3. Controlla l'esistenza di un dato valore"<<endl;
            cout<<"4. Trova il minimo dell'albero"<<endl;
            cout<<"5. Trova il massimo dell'albero"<<endl;
            cout<<"6. Trova il successore di un dato valore"<<endl;
            cout<<"7. Trova il predecessore di un dato valore"<<endl;
            cout<<"8. Trova ed elimina il minimo dell'albero"<<endl;
            cout<<"9. Trova ed elimina il massimo dell'albero"<<endl;
            cout<<"10. Trova ed elimina il successore di un dato valore"<<endl;
            cout<<"11. Trova ed elimina il predecessore di un dato valore"<<endl;
            cout<<"12. Elimina il minimo dell'albero"<<endl;
            cout<<"13. Elimina il massimo dell'albero"<<endl;
            cout<<"14. Elimina il predecessore di un dato valore"<<endl;
            cout<<"15. Elimina il successore di un dato valore"<<endl;
            cout<<"16. Prodotto di tutti gli interi minori di un certo valore arbitrario"<<endl;
            cout<<"17. Visualizza tutti gli elementi (inorder) dell'albero"<<endl;
            cout<<"0. Esci dal test"<<endl;
            cin>>choice;

            switch (choice)
            {
            case 1:
                cout<<"Quale elemento va inserito?"<<endl;
                cin>>inserimento;
                playedBst.Insert(inserimento);
                break;
            case 2:
                cout<<"Quale elemento si desidera rimuovere?"<<endl;
                cin>>inserimento;
                try
                {
                    playedBst.Remove(inserimento);
                }
                catch(length_error err)
                {
                    cout<<"L'albero e' vuoto!"<<endl;
                }
                break;
            case 3:
                cout<<"Di quale valore si desidera testare l'esistenza?"<<endl;
                cin>>inserimento;
                cout<<"L'elemento inserito "<<(playedBst.Exists(inserimento)? "esiste" : "non esiste")<<endl;
                break;
            case 4:
                cout<<"Il minimo dell'albero e': "<<playedBst.Min()<<endl;
                break;
            case 5:
                cout<<"Il massimo dell'albero e': "<<playedBst.Max()<<endl;
                break;
            case 6:
                cout<<"Di quale valore si desidera ottenere il successore?"<<endl;
                cin>>inserimento;
                try
                {
                    cout<<"Il successore di "<<inserimento<<" nell'albero e: "<<playedBst.Successor(inserimento)<<endl;
                }
                catch(length_error err)
                {
                    cout<<"L'elemento indicato non ha successore nell'albero"<<endl;
                }
                break;
            case 7:
                cout<<"Di quale valore si desidera ottenere il predecessore?"<<endl;
                cin>>inserimento;
                try
                {
                    cout<<"Il predecessore di "<<inserimento<<" nell'albero e: "<<playedBst.Predecessor(inserimento)<<endl;
                }
                catch(length_error err)
                {
                    cout<<"L'elemento indicato non ha predecessore nell'albero"<<endl;
                }
                break;
            case 8:
                try
                {
                    cout<<"Il minimo di valore "<<playedBst.MinNRemove()<<" e stato cancellato dall'albero!"<<endl;
                }
                catch(length_error err)
                {
                    cerr<<err.what()<<endl;
                }
                break;
            case 9:
                try
                {
                    cout<<"Il massimo di valore "<<playedBst.MaxNRemove()<<" e stato cancellato dall'albero!"<<endl;
                }
                catch(length_error err)
                {
                    cerr<<err.what()<<endl;
                }
                break;
            case 10:
                cout<<"Di quale valore si desidera eliminarne il successore?"<<endl;
                cin>>inserimento;
                try
                {
                    cout<<"Il successore di valore "<<playedBst.SuccessorNRemove(inserimento)<<" e stato cancellato dall'albero!"<<endl;
                }
                catch(length_error err)
                {
                    cerr<<err.what()<<endl;
                }
                break;
            case 11:
                cout<<"Di quale valore si desidera eliminarne il predecessore?"<<endl;
                cin>>inserimento;
                try
                {
                    cout<<"Il predecessore di valore "<<playedBst.PredecessorNRemove(inserimento)<<" e stato cancellato dall'albero!"<<endl;
                }
                catch(length_error err)
                {
                    cerr<<err.what()<<endl;
                }
                break;
            case 12:
                try
                {
                    playedBst.RemoveMin();
                    cout<<"Il minimo e' stato cancellato!"<<endl;
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }        
                break;
            case 13:
                try
                {
                    playedBst.RemoveMax();
                    cout<<"Il massimo e' stato cancellato!"<<endl;
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                break;
            case 14:
                cout<<"Di quale valore si desidera eliminarne il predecessore?"<<endl;
                cin>>inserimento;
                try
                {
                    playedBst.RemovePredecessor(inserimento);
                    cout<<"Il predecessore e stato cancellato dall'albero!"<<endl;
                }
                catch(length_error err)
                {
                    cerr<<err.what()<<endl;
                }
                break;
            case 15:
                cout<<"Di quale valore si desidera eliminarne il successore?"<<endl;
                cin>>inserimento;
                try
                {
                    playedBst.RemoveSuccessor(inserimento);
                    cout<<"Il predecessore e stato cancellato dall'albero!"<<endl;
                }
                catch(length_error err)
                {
                    cerr<<err.what()<<endl;
                }
                break;

            case 16:
                cout<<"Qual'e il valore in input?"<<endl;
                cin>>inserimento;
                risultato = 1;
                playedBst.Fold(MulIfLessThanN, &inserimento, &risultato);
                cout<<"Risultato: "<<risultato<<endl;
                break;
            case 17:
                cout<<"Albero: ";
                playedBst.MapInOrder(VisualizeContainer<int>,nullptr);
                cout<<endl<<endl;
                break;
            case 0: 

                break;
            default:
                cout<<"Opzione non esistente, riprovare!"<<endl<<endl;
                break;
            }
        }
    }


    if(tp == Tipo::Double)
    {   
        lasd::BST<double> playedBst;
        for(ulong i = 0; i<dim; i++)
        {
            playedBst.Insert(trunc(((double) distAndNeg(gen)/distUnder(gen)) * 100) / 100);
        }

        double inserimento;
        double risultato;
        while(choice != 0)
        {    
            cout<<"1. Inserisci un elemento"<<endl;
            cout<<"2. Rimuovi un elemento"<<endl;
            cout<<"3. Controlla l'esistenza di un dato valore"<<endl;
            cout<<"4. Trova il minimo dell'albero"<<endl;
            cout<<"5. Trova il massimo dell'albero"<<endl;
            cout<<"6. Trova il successore di un dato valore"<<endl;
            cout<<"7. Trova il predecessore di un dato valore"<<endl;
            cout<<"8. Trova ed elimina il minimo dell'albero"<<endl;
            cout<<"9. Trova ed elimina il massimo dell'albero"<<endl;
            cout<<"10. Trova ed elimina il successore di un dato valore"<<endl;
            cout<<"11. Trova ed elimina il predecessore di un dato valore"<<endl;
            cout<<"12. Elimina il minimo dell'albero"<<endl;
            cout<<"13. Elimina il massimo dell'albero"<<endl;
            cout<<"14. Elimina il predecessore di un dato valore"<<endl;
            cout<<"15. Elimina il successore di un dato valore"<<endl;
            cout<<"16. Controlla la dimensione dell'albero"<<endl;
            cout<<"17. Visualizza tutti gli elementi (inorder) dell'albero"<<endl;
            cout<<"0. Esci dal test"<<endl;
            cin>>choice;

            switch (choice)
            {
            case 1:
                cout<<"Quale elemento va inserito?"<<endl;
                cin>>inserimento;
                playedBst.Insert(inserimento);
                break;
            case 2:
                cout<<"Quale elemento si desidera rimuovere?"<<endl;
                cin>>inserimento;
                try
                {
                    playedBst.Remove(inserimento);
                }
                catch(length_error err)
                {
                    cout<<"L'albero e' vuoto!"<<endl;
                }
                break;
            case 3:
                cout<<"Di quale valore si desidera testare l'esistenza?"<<endl;
                cin>>inserimento;
                cout<<"L'elemento inserito "<<(playedBst.Exists(inserimento)? "esiste" : "non esiste")<<endl;
                break;
            case 4:
                cout<<"Il minimo dell'albero e': "<<playedBst.Min()<<endl;
                break;
            case 5:
                cout<<"Il massimo dell'albero e': "<<playedBst.Max()<<endl;
                break;
            case 6:
                cout<<"Di quale valore si desidera ottenere il successore?"<<endl;
                cin>>inserimento;
                try
                {
                    cout<<"Il successore di "<<inserimento<<" nell'albero e: "<<playedBst.Successor(inserimento)<<endl;
                }
                catch(length_error err)
                {
                    cout<<"L'elemento indicato non ha successore nell'albero"<<endl;
                }
                break;
            case 7:
                cout<<"Di quale valore si desidera ottenere il predecessore?"<<endl;
                cin>>inserimento;
                try
                {
                    cout<<"Il predecessore di "<<inserimento<<" nell'albero e: "<<playedBst.Predecessor(inserimento)<<endl;
                }
                catch(length_error err)
                {
                    cout<<"L'elemento indicato non ha predecessore nell'albero"<<endl;
                }
                break;
            case 8:
                try
                {
                    cout<<"Il minimo di valore "<<playedBst.MinNRemove()<<" e stato cancellato dall'albero!"<<endl;
                }
                catch(length_error err)
                {
                    cerr<<err.what()<<endl;
                }
                break;
            case 9:
                try
                {
                    cout<<"Il massimo di valore "<<playedBst.MaxNRemove()<<" e stato cancellato dall'albero!"<<endl;
                }
                catch(length_error err)
                {
                    cerr<<err.what()<<endl;
                }
                break;
            case 10:
                cout<<"Di quale valore si desidera eliminarne il successore?"<<endl;
                cin>>inserimento;
                try
                {
                    cout<<"Il massimo di valore "<<playedBst.SuccessorNRemove(inserimento)<<" e stato cancellato dall'albero!"<<endl;
                }
                catch(length_error err)
                {
                    cerr<<err.what()<<endl;
                }
                break;
            case 11:
                cout<<"Di quale valore si desidera eliminarne il predecessore?"<<endl;
                cin>>inserimento;
                try
                {
                    cout<<"Il predecessore di valore "<<playedBst.PredecessorNRemove(inserimento)<<" e stato cancellato dall'albero!"<<endl;
                }
                catch(length_error err)
                {
                    cerr<<err.what()<<endl;
                }
                break;
            case 12:
                try
                {
                    playedBst.RemoveMin();
                    cout<<"Il minimo e' stato cancellato!"<<endl;
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }        
                break;
            case 13:
                try
                {
                    playedBst.RemoveMax();
                    cout<<"Il massimo e' stato cancellato!"<<endl;
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                break;
            case 14:
                cout<<"Di quale valore si desidera eliminarne il predecessore?"<<endl;
                cin>>inserimento;
                try
                {
                    playedBst.RemovePredecessor(inserimento);
                    cout<<"Il predecessore e stato cancellato dall'albero!"<<endl;
                }
                catch(length_error err)
                {
                    cerr<<err.what()<<endl;
                }
                break;
            case 15:
                cout<<"Di quale valore si desidera eliminarne il successore?"<<endl;
                cin>>inserimento;
                try
                {
                    playedBst.RemoveSuccessor(inserimento);
                    cout<<"Il predecessore e stato cancellato dall'albero!"<<endl;
                }
                catch(length_error err)
                {
                    cerr<<err.what()<<endl;
                }
                break;            
            case 16:
                cout<<"Qual'e il valore in input?"<<endl;
                cin>>inserimento;
                risultato = 0;
                playedBst.Fold(SumIfHigherThanN, &inserimento, &risultato);
                cout<<"Risultato: "<<risultato<<endl;;
                break;
            case 17:
                cout<<"Albero: ";
                playedBst.MapInOrder(VisualizeContainer<double>,nullptr);
                cout<<endl<<endl;
                break; 
            case 0: 

                break;
            default:
                cout<<"Opzione non esistente, riprovare!"<<endl<<endl;
                break;
            }
        }
    }

    else if(tp == Tipo::String)
    {   
        lasd::BST<string> playedBst;
        string value = init;
        int lunghezzamax;
        for(ulong i = 0; i<dim; i++)
        {
            value = init;
            lunghezzamax = 1;
            value += CHARACTERS[distC(gen)];
            while(randomstop(gen) != 0 && lunghezzamax<10)
                {value += CHARACTERS[distC(gen)]; lunghezzamax++;}
            playedBst.Insert(value);
        }

        string inserimento;
        string risultato;
        int lunghmax;
        while(choice != 0)
        {    
            cout<<"1. Inserisci un elemento"<<endl;
            cout<<"2. Rimuovi un elemento"<<endl;
            cout<<"3. Controlla l'esistenza di un dato valore"<<endl;
            cout<<"4. Trova il minimo dell'albero"<<endl;
            cout<<"5. Trova il massimo dell'albero"<<endl;
            cout<<"6. Trova il successore di un dato valore"<<endl;
            cout<<"7. Trova il predecessore di un dato valore"<<endl;
            cout<<"8. Trova ed elimina il minimo dell'albero"<<endl;
            cout<<"9. Trova ed elimina il massimo dell'albero"<<endl;
            cout<<"10. Trova ed elimina il successore di un dato valore"<<endl;
            cout<<"11. Trova ed elimina il predecessore di un dato valore"<<endl;
            cout<<"12. Elimina il minimo dell'albero"<<endl;
            cout<<"13. Elimina il massimo dell'albero"<<endl;
            cout<<"14. Elimina il predecessore di un dato valore"<<endl;
            cout<<"15. Elimina il successore di un dato valore"<<endl;
            cout<<"16. Concatena tutti i valori di lunghezza minore di un intero"<<endl;
            cout<<"17. Visualizza tutti gli elementi (inorder) dell'albero"<<endl;
            cout<<"0. Esci dal test"<<endl;
            cin>>choice;

            switch (choice)
            {
            case 1:
                cout<<"Quale elemento va inserito?"<<endl;
                cin>>inserimento;
                playedBst.Insert(inserimento);
                break;
            case 2:
                cout<<"Quale elemento si desidera rimuovere?"<<endl;
                cin>>inserimento;
                try
                {
                    playedBst.Remove(inserimento);
                }
                catch(length_error err)
                {
                    cout<<"L'albero e' vuoto!"<<endl;
                }
                break;
            case 3:
                cout<<"Di quale valore si desidera testare l'esistenza?"<<endl;
                cin>>inserimento;
                cout<<"L'elemento inserito "<<(playedBst.Exists(inserimento)? "esiste" : "non esiste")<<endl;
                break;
            case 4:
                cout<<"Il minimo dell'albero e': "<<playedBst.Min()<<endl;
                break;
            case 5:
                cout<<"Il massimo dell'albero e': "<<playedBst.Max()<<endl;
                break;
            case 6:
                cout<<"Di quale valore si desidera ottenere il successore?"<<endl;
                cin>>inserimento;
                try
                {
                    cout<<"Il successore di "<<inserimento<<" nell'albero e: "<<playedBst.Successor(inserimento)<<endl;
                }
                catch(length_error err)
                {
                    cout<<"L'elemento indicato non ha successore nell'albero"<<endl;
                }
                break;
            case 7:
                cout<<"Di quale valore si desidera ottenere il predecessore?"<<endl;
                cin>>inserimento;
                try
                {
                    cout<<"Il predecessore di "<<inserimento<<" nell'albero e: "<<playedBst.Predecessor(inserimento)<<endl;
                }
                catch(length_error err)
                {
                    cout<<"L'elemento indicato non ha predecessore nell'albero"<<endl;
                }
                break;
            case 8:
                try
                {
                    cout<<"Il minimo di valore "<<playedBst.MinNRemove()<<" e stato cancellato dall'albero!"<<endl;
                }
                catch(length_error err)
                {
                    cerr<<err.what()<<endl;
                }
                break;
            case 9:
                try
                {
                    cout<<"Il massimo di valore "<<playedBst.MaxNRemove()<<" e stato cancellato dall'albero!"<<endl;
                }
                catch(length_error err)
                {
                    cerr<<err.what()<<endl;
                }
                break;
            case 10:
                cout<<"Di quale valore si desidera eliminarne il successore?"<<endl;
                cin>>inserimento;
                try
                {
                    cout<<"Il massimo di valore "<<playedBst.SuccessorNRemove(inserimento)<<" e stato cancellato dall'albero!"<<endl;
                }
                catch(length_error err)
                {
                    cerr<<err.what()<<endl;
                }
                break;
            case 11:
                cout<<"Di quale valore si desidera eliminarne il predecessore?"<<endl;
                cin>>inserimento;
                try
                {
                    cout<<"Il predecessore di valore "<<playedBst.PredecessorNRemove(inserimento)<<" e stato cancellato dall'albero!"<<endl;
                }
                catch(length_error err)
                {
                    cerr<<err.what()<<endl;
                }
                break;
            case 12:
                try
                {
                    playedBst.RemoveMin();
                    cout<<"Il minimo e' stato cancellato!"<<endl;
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }        
                break;
            case 13:
                try
                {
                    playedBst.RemoveMax();
                    cout<<"Il massimo e' stato cancellato!"<<endl;
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                break;
            case 14:
                cout<<"Di quale valore si desidera eliminarne il predecessore?"<<endl;
                cin>>inserimento;
                try
                {
                    playedBst.RemovePredecessor(inserimento);
                    cout<<"Il predecessore e stato cancellato dall'albero!"<<endl;
                }
                catch(length_error err)
                {
                    cerr<<err.what()<<endl;
                }
                break;
            case 15:
                cout<<"Di quale valore si desidera eliminarne il successore?"<<endl;
                cin>>inserimento;
                try
                {
                    playedBst.RemoveSuccessor(inserimento);
                    cout<<"Il predecessore e stato cancellato dall'albero!"<<endl;
                }
                catch(length_error err)
                {
                    cerr<<err.what()<<endl;
                }
                break;
            case 16:
                cout<<"Qual'e il valore in input?"<<endl;
                cin>>lunghmax;
                playedBst.Fold(AppendIfLessThanN, &lunghmax, &risultato);
                risultato = init;
                cout<<"Risultato: "<<risultato<<endl;;
                break;
            case 17:
                cout<<"Albero: ";
                playedBst.MapInOrder(VisualizeContainer<string>,nullptr);
                cout<<endl<<endl;
                break;
            case 0: 

                break;
            default:
                cout<<"Opzione non esistente, riprovare!"<<endl<<endl;
                break;
            }
        }
    }
}

void TestBTVec(Tipo tp,ulong dim)
{   
    int input;
    Operazione scelta = Operazione::Invalid;
    if(tp == Tipo::Int)
    {
        lasd::StackLst<lasd::BinaryTree<int>::Node*> parent;
        lasd::BinaryTree<int>::Node* currElement = nullptr;
        int sceltaExp;
        int contaScelta;
        int res;
        int testval;
        lasd::Vector<int> sourcevec(dim);
        for (int i = 0; i<dim;i++ )
        {
            sourcevec[i] = dist(gen);
        } 
        lasd::BinaryTreeVec<int> testBT(sourcevec);

        do
        {
            cout<<"1. Visita in Ampiezza, PreOrder, PostOrder e Order"<<endl<<"2. Controllo di esistenza di un valore"<<endl<<"3. Prodotto di tutti i valori minori di un valore"<<endl<<"4. Triplicazione di tutti i valori"<<endl<<"5. Esplorazione dell'albero"<<endl<<"6. Esplorazione per iteratori"<<endl<<"0. Uscita dal test"<<endl;
            cin>>input;
            if(input ==1 ) scelta = Operazione::FullContainer;    
            if(input ==2 ) scelta = Operazione::CheckExist;
            if(input ==3 ) scelta = Operazione::ProprietaryFoldFun;
            if(input ==4 ) scelta = Operazione::ProprietaryMapFun;
            if(input == 5) scelta = Operazione::LibFunct;
            if(input == 6) scelta = Operazione::TopNPop;
            if(input ==0 ) scelta = Operazione::End;
            if(input > 6 || input < 0) scelta = Operazione::Invalid;

            switch (scelta)
            {
            case  Operazione::FullContainer:
                cout<<"Visita in Ampiezza : ";
                testBT.MapBreadth(VisualizeContainer<int>,nullptr);
                cout<<endl<<endl;
                cout<<"Visita in PreOrder : ";
                testBT.MapPreOrder(VisualizeContainer<int>,nullptr);
                cout<<endl<<endl;
                cout<<"Visita in PostOrder : ";
                testBT.MapPostOrder(VisualizeContainer<int>,nullptr);
                cout<<endl<<endl;
                cout<<"Visita in Order : ";  
                testBT.MapInOrder(VisualizeContainer<int>,nullptr); 
                cout<<endl<<endl;     
                break;
            case Operazione::CheckExist:
                cout<<"Di quale valore si desidera testare l'esistenza? ";
                cin>>testval;
                cout<<testval<<(testBT.Exists(testval)? " " :   " non")<<" esiste!"<<endl;
                break;
                break;
            case Operazione::ProprietaryFoldFun:
                cout<<"Qual'e il valore in input? "; cin>>testval;
                res = 1;
                testBT.FoldPreOrder(MulIfLessThanN, &testval , &res);
                cout<<endl<<endl;
                cout<<"Risultato: "<<res;
                cout<<endl<<endl;
                break;

            case Operazione::ProprietaryMapFun:
                testBT.MapPreOrder(TripleThemUp,nullptr);
                testBT.MapBreadth(VisualizeContainer<int>,nullptr);
                cout<<endl<<endl;
                break;
            
            case Operazione::LibFunct:
                currElement = &testBT.Root();
                
                do
                {  
                    contaScelta = 0;
                    cout<<"Elemento corrente: "<<currElement->Element()<<endl;
                    cout<<"1. Accesso al figlio sx"<<endl<<"2. Accesso al figlio dx"<<endl<<"3. Ritorna al nodo precedente"<<endl;
                    cout<<"0. Ritorna al menu precedente"<<endl;
                    cin>>sceltaExp;

                    switch (sceltaExp)
                    {
                    case 1:
                       
                        if(currElement->HasLeftChild())
                        {
                            parent.Push(currElement);
                            currElement = &currElement->LeftChild();
                        }
                        else
                            cout<<"Figlio sx inesistente!"<<endl;
                        break;
                    case 2:
                        if(currElement->HasRightChild())
                        {
                            parent.Push(currElement);
                            currElement = &currElement->RightChild();
                        }
                        else
                            cout<<"Figlio dx inesistente!"<<endl;
                        break;
                    case 3:
                        if(!parent.Empty()) currElement = parent.TopNPop();
                        else cout<<"Non hai ancora effettuato nessuna discesa nell'albero!"<<endl;
                        break;
                    case 0:
                        break;
                    default:
                        cout<<"Opzione non valida, riprovare."<<endl;
                        break;
                    }

                } while (sceltaExp != 0);
                                
                                
                break;
            case Operazione::TopNPop:
                lasd::ForwardIterator<int>* it;
                cout<<"Che tipo di iteratore si vuole utilizzare?\n1. PreOrder;\n2. PostOrder;\n3. Breadth;\n4. InOrder."<<endl;
                cin>>sceltaExp;

                if(sceltaExp ==1) it = new lasd::BTPreOrderIterator<int>(testBT);
                else if(sceltaExp == 2) it = new lasd::BTPostOrderIterator<int>(testBT);
                else if(sceltaExp == 3)it = new lasd::BTBreadthIterator<int>(testBT);
                else it = new lasd::BTInOrderIterator<int>(testBT);

                do
                {
                    cout<<"1. Stampa elemento corrente"<<endl<<"2. Vai al prossimo elemento"<<endl<<"3. Modifica elemento corrente"<<endl;
                    cin>>sceltaExp;

                    if(sceltaExp == 1) cout<<"L'elemento corrente e': "<<it->operator*()<<endl;
                    else if(sceltaExp == 3) 
                    {
                        cout<<"Quale valore deve avere il nodo corrente?"<<endl;
                        cin>>testval;
                        it->operator*() = testval;
                    }
                    else it->operator++();

                    if(it->Terminated())cout<<"Termine esplorazione!"<<endl<<endl;  
                } while (sceltaExp!= 0 && !it->Terminated());
                
                delete it;

                break;
            case Operazione::End:
                
                break;
            default:
                cout<<"Operazione non valida, riprovare."<<endl<<endl<<endl<<endl;
                break;
            }

        } while (scelta != Operazione::End);
    
    }
    else if(tp == Tipo::Double)
    {
        lasd::StackLst<lasd::BinaryTree<double>::Node*> parent;
        lasd::BinaryTree<double>::Node* currElement = nullptr;
        int sceltaExp;
        int contaScelta;
        double testval;
        double res;
        lasd::Vector<double> sourcevec(dim);
        for(int i = 0; i <dim; i++)
        {
            sourcevec[i] = trunc( (double) distAndNeg(gen)/distUnder(gen) *100)/100;
        }
        lasd::BinaryTreeVec<double> testBT(sourcevec);
        do
        {
            cout<<"1. Visita in Ampiezza, PreOrder, PostOrder e Order"<<endl<<"2. Controllo di esistenza di un valore"<<endl<<"3.  Somma di tutti i valori maggiori di uno a scelta"<<endl<<"4. Elevazione al cubo di tutti i valori"<<endl<<"5. Esplorazione dell'albero"<<endl<<"6. Esplorazione per iteratori"<<endl<<"0. Uscita dal test"<<endl;
            cin>>input;
            if(input ==1 ) scelta = Operazione::FullContainer;    
            if(input ==2 ) scelta = Operazione::CheckExist;
            if(input ==3 ) scelta = Operazione::ProprietaryFoldFun;
            if(input ==4 ) scelta = Operazione::ProprietaryMapFun;
            if(input == 5) scelta = Operazione::LibFunct;
            if(input==6) scelta = Operazione::TopNPop;
            if(input ==0 ) scelta = Operazione::End;
            if(input > 6 || input < 0) scelta = Operazione::Invalid;
            switch (scelta)
            {
            case  Operazione::FullContainer:
                cout<<"Visita in Ampiezza : ";
                testBT.MapBreadth(VisualizeContainer<double>,nullptr);
                cout<<endl<<endl;
                cout<<"Visita in PreOrder : ";
                testBT.MapPreOrder(VisualizeContainer<double>,nullptr);
                cout<<endl<<endl;
                cout<<"Visita in PostOrder : ";
                testBT.MapPostOrder(VisualizeContainer<double>,nullptr);
                cout<<endl<<endl;
                cout<<"Visita in Order : ";  
                testBT.MapInOrder(VisualizeContainer<double>,nullptr); 
                cout<<endl<<endl;     
                break;
            case Operazione::CheckExist:
                cout<<"Di quale valore si desidera testare l'esistenza? ";
                cin>>testval;
                cout<<testval<<(testBT.Exists(testval)? " " :   " non")<<" esiste!"<<endl;
                break;
                break;
            case Operazione::ProprietaryFoldFun:
                cout<<"Qual'e il valore in input? "; cin>>input;
                res = 0;
                testBT.FoldPreOrder(SumIfHigherThanN, &testval , &res);
                cout<<endl<<endl;
                cout<<"Risultato: "<<res;
                cout<<endl<<endl;
                break;

            case Operazione::ProprietaryMapFun:
                testBT.MapPreOrder(MultiplyByItself2Times,nullptr);
                cout<<endl<<endl;
                cout<<"Risultato: ";
                testBT.MapBreadth(VisualizeContainer<double>,nullptr);
                cout<<endl<<endl;
                break;
            
            case Operazione::LibFunct:
                currElement = &testBT.Root();
                
                do
                {  
                    contaScelta = 0;
                    cout<<"Elemento corrente: "<<currElement->Element()<<endl;
                    cout<<"1. Accesso al figlio sx"<<endl<<"2. Accesso al figlio dx"<<endl<<"3. Ritorna al nodo precedente"<<endl;
                    cout<<"0. Ritorna al menu precedente"<<endl;
                    cin>>sceltaExp;

                    switch (sceltaExp)
                    {
                    case 1:
                        parent.Push(currElement);
                        currElement = &currElement->LeftChild();
                        break;
                    case 2:
                        parent.Push(currElement);
                        currElement = &currElement->RightChild();
                        break;
                    case 3:
                        currElement = parent.TopNPop();
                        break;
                    case 0:
                        break;
                    default:
                        cout<<"Opzione non valida, riprovare."<<endl;
                        break;
                    }

                } while (sceltaExp != 0);
                                
                                
                break;
                lasd::ForwardIterator<double>* it;
                cout<<"Che tipo di iteratore si vuole utilizzare?\n1. PreOrder;\n2. PostOrder;\n3. Breadth;\n4. InOrder."<<endl;
                cin>>sceltaExp;

                if(sceltaExp ==1) it = new lasd::BTPreOrderIterator<double>(testBT);
                else if(sceltaExp == 2) it = new lasd::BTPostOrderIterator<double>(testBT);
                else if(sceltaExp == 3)it = new lasd::BTBreadthIterator<double>(testBT);
                else it = new lasd::BTInOrderIterator<double>(testBT);

                do
                {
                    cout<<"1. Stampa elemento corrente"<<endl<<"2. Vai al prossimo elemento"<<endl<<"3. Modifica elemento corrente"<<endl;
                    cin>>sceltaExp;

                    if(sceltaExp == 1) cout<<"L'elemento corrente e': "<<it->operator*()<<endl;
                    else if(sceltaExp == 3) 
                    {
                        cout<<"Quale valore deve avere il nodo corrente?"<<endl;
                        cin>>testval;
                        it->operator*() = testval;
                    }
                    else it->operator++();

                    if(it->Terminated())cout<<"Termine esplorazione!"<<endl<<endl;  
                } while (sceltaExp!= 0 && !it->Terminated());
                
                delete it;

                break;
            case Operazione::End:
                break;
            default:
                cout<<"Operazione non valida, riprovare."<<endl<<endl<<endl<<endl;
                break;
            }

        } while (scelta != Operazione::End);
    }
    else if(tp == Tipo::String)
    {
        lasd::StackLst<lasd::BinaryTree<string>::Node*> parent;
        lasd::BinaryTree<string>::Node* currElement = nullptr;
        int sceltaExp;
        int contaScelta;
        lasd::Vector<string> sourcevec(dim);
        string res;
        string testval;
        int dimatt = 0;

        for(int i = 0; i<dim; i++)
        {
            res = init + CHARACTERS[distC(gen)];    
            dimatt = 1;
            while(dimatt < 10 && randomstop(gen)!= 0)
            {
                res = res+CHARACTERS[distC(gen)];
                dimatt++;
            }
            sourcevec[i] = res;
        }
        lasd::BinaryTreeVec<string> testBT(sourcevec);
        do
        {
            cout<<"1. Visita in Ampiezza, PreOrder, PostOrder e Order"<<endl<<"2. Controllo di esistenza di un valore"<<endl<<"3.  Concatenazione di tutte le stringhe minori di un valore a scelta"<<endl<<"4. Concatenazione in testa di tutte le stringhe di una a scelta"<<endl<<"5. Esplorazione dell'albero"<<endl<<"6. Esplorazione per iteratori"<<endl<<"0. Uscita dal test"<<endl<<"0. Uscita dal test"<<endl;
            cin>>input;
            if(input ==1 ) scelta = Operazione::FullContainer;    
            if(input ==2 ) scelta = Operazione::CheckExist;
            if(input ==3 ) scelta = Operazione::ProprietaryFoldFun;
            if(input ==4 ) scelta = Operazione::ProprietaryMapFun;
            if(input ==5) scelta = Operazione::LibFunct;
            if(input == 6) scelta = Operazione::TopNPop;
            if(input ==0 ) scelta = Operazione::End;
            if(input > 6 || input < 0) scelta = Operazione::Invalid;

            switch (scelta)
            {
            case  Operazione::FullContainer:
                cout<<"Visita in Ampiezza : ";
                testBT.MapBreadth(VisualizeContainer<string>,nullptr);
                cout<<endl<<endl;
                cout<<"Visita in PreOrder : ";
                testBT.MapPreOrder(VisualizeContainer<string>,nullptr);
                cout<<endl<<endl;
                cout<<"Visita in PostOrder : ";
                testBT.MapPostOrder(VisualizeContainer<string>,nullptr);
                cout<<endl<<endl;
                cout<<"Visita in Order : ";  
                testBT.MapInOrder(VisualizeContainer<string>,nullptr); 
                cout<<endl<<endl;     
                break;
            case Operazione::CheckExist:
                cout<<"Di quale valore si desidera testare l'esistenza? ";
                cin>>testval;
                cout<<testval<<(testBT.Exists(testval)? " " :   " non")<<" esiste!"<<endl;
                break;
            case Operazione::ProprietaryFoldFun:
                cout<<"Qual'e il valore in input? "; cin>>input;
                res = init;
                testBT.FoldPreOrder(AppendIfLessThanN, &input , &res);
                cout<<endl<<endl;
                cout<<"Risultato: "<<res;
                cout<<endl<<endl;
                break;

            case Operazione::ProprietaryMapFun:
                cout<<"Quale stringa concatenare? "; cin>>testval;
                testBT.MapPreOrder(AppendV, &testval);
                cout<<endl<<endl;
                cout<<"Risultato: ";
                testBT.MapBreadth(VisualizeContainer<string>,nullptr);
                cout<<endl<<endl;
                break;
            case Operazione::LibFunct:
                currElement = &testBT.Root();
                
                do
                {  
                    contaScelta = 0;
                    cout<<"Elemento corrente: "<<currElement->Element()<<endl;
                    cout<<"1. Accesso al figlio sx"<<endl<<"2. Accesso al figlio dx"<<endl<<"3. Ritorna al nodo precedente"<<endl;
                    cout<<"0. Ritorna al menu precedente"<<endl;
                    cin>>sceltaExp;

                    switch (sceltaExp)
                    {
                    case 1:
                        parent.Push(currElement);
                        currElement = &currElement->LeftChild();
                        break;
                    case 2:
                        parent.Push(currElement);
                        currElement = &currElement->RightChild();
                        break;
                    case 3:
                        currElement = parent.TopNPop();
                        break;
                    case 0:
                        break;
                    default:
                        cout<<"Opzione non valida, riprovare."<<endl;
                        break;
                    }

                } while (sceltaExp != 0);
                                
                                
                break;
                case Operazione::TopNPop:
                lasd::ForwardIterator<string>* it;
                cout<<"Che tipo di iteratore si vuole utilizzare?\n1. PreOrder;\n2. PostOrder;\n3. Breadth;\n4. InOrder."<<endl;
                cin>>sceltaExp;

                if(sceltaExp ==1) it = new lasd::BTPreOrderIterator<string>(testBT);
                else if(sceltaExp == 2) it = new lasd::BTPostOrderIterator<string>(testBT);
                else if(sceltaExp == 3)it = new lasd::BTBreadthIterator<string>(testBT);
                else it = new lasd::BTInOrderIterator<string>(testBT);

                do
                {
                    cout<<"1. Stampa elemento corrente"<<endl<<"2. Vai al prossimo elemento"<<endl<<"3. Modifica elemento corrente"<<endl;
                    cin>>sceltaExp;

                    if(sceltaExp == 1) cout<<"L'elemento corrente e': "<<it->operator*()<<endl;
                    else if(sceltaExp == 3) 
                    {
                        cout<<"Quale valore deve avere il nodo corrente?"<<endl;
                        cin>>testval;
                        it->operator*() = testval;
                    }
                    else it->operator++();

                    if(it->Terminated())cout<<"Termine esplorazione!"<<endl<<endl;  
                } while (sceltaExp!= 0 && !it->Terminated());
                
                delete it;


                break;
            case Operazione::End:
                break;
            default:
                cout<<"Operazione non valida, riprovare."<<endl<<endl<<endl<<endl;
                break;
            }
        }while(scelta != Operazione::End);
    }

}

void TestBTLnk(Tipo tp,ulong dim)
{   
    int input;
    Operazione scelta = Operazione::Invalid;
    if(tp == Tipo::Int)
    {
        lasd::StackLst<lasd::BinaryTree<int>::Node*> parent;
        lasd::BinaryTree<int>::Node* currElement = nullptr;
        int sceltaExp;
        int contaScelta;
        int res;
        int testval;
        lasd::Vector<int> sourcevec(dim);
        for (int i = 0; i<dim;i++ )
        {
            sourcevec[i] = dist(gen);
        } 
        lasd::BinaryTreeLnk<int> testBT(sourcevec);

        do
        {
            cout<<"1. Visita in Ampiezza, PreOrder, PostOrder e Order"<<endl<<"2. Controllo di esistenza di un valore"<<endl<<"3. Prodotto di tutti i valori minori di un valore"<<endl<<"4. Triplicazione di tutti i valori"<<endl<<"5. Esplorazione dell'albero"<<endl<<"6. Esplorazione per iteratori"<<endl<<"0. Uscita dal test"<<endl;
            cin>>input;
            if(input ==1 ) scelta = Operazione::FullContainer;    
            if(input ==2 ) scelta = Operazione::CheckExist;
            if(input ==3 ) scelta = Operazione::ProprietaryFoldFun;
            if(input ==4 ) scelta = Operazione::ProprietaryMapFun;
            if(input == 5) scelta = Operazione::LibFunct;
            if(input == 6) scelta = Operazione::TopNPop;
            if(input ==0 ) scelta = Operazione::End;
            if(input > 6 || input < 0) scelta = Operazione::Invalid;

            switch (scelta)
            {
            case  Operazione::FullContainer:
                cout<<"Visita in Ampiezza : ";
                testBT.MapBreadth(VisualizeContainer<int>,nullptr);
                cout<<endl<<endl;
                cout<<"Visita in PreOrder : ";
                testBT.MapPreOrder(VisualizeContainer<int>,nullptr);
                cout<<endl<<endl;
                cout<<"Visita in PostOrder : ";
                testBT.MapPostOrder(VisualizeContainer<int>,nullptr);
                cout<<endl<<endl;
                cout<<"Visita in Order : ";  
                testBT.MapInOrder(VisualizeContainer<int>,nullptr); 
                cout<<endl<<endl;     
                break;
            case Operazione::CheckExist:
                cout<<"Di quale valore si desidera testare l'esistenza? ";
                cin>>testval;
                cout<<testval<<(testBT.Exists(testval)? " " :   " non")<<" esiste!"<<endl;
                break;
                break;
            case Operazione::ProprietaryFoldFun:
                cout<<"Qual'e il valore in input? "; cin>>testval;
                res = 1;
                testBT.FoldPreOrder(MulIfLessThanN, &testval , &res);
                cout<<endl<<endl;
                cout<<"Risultato: "<<res;
                cout<<endl<<endl;
                break;

            case Operazione::ProprietaryMapFun:
                testBT.MapPreOrder(TripleThemUp,nullptr);
                cout<<endl<<endl;
                cout<<"Risultato: ";
                testBT.MapBreadth(VisualizeContainer<int>,nullptr);
                cout<<endl<<endl;
                break;
            
            case Operazione::End:
                break;
            case Operazione::LibFunct:
                currElement = &testBT.Root();
                
                do
                {  
                    contaScelta = 0;
                    cout<<"Elemento corrente: "<<currElement->Element()<<endl;
                    cout<<"1. Accesso al figlio sx"<<endl<<"2. Accesso al figlio dx"<<endl<<"3. Ritorna al nodo precedente"<<endl;
                    cout<<"0. Ritorna al menu precedente"<<endl;
                    cin>>sceltaExp;

                    switch (sceltaExp)
                    {
                    case 1:
                       
                        if(currElement->HasLeftChild())
                        {
                            parent.Push(currElement);
                            currElement = &currElement->LeftChild();
                        }
                        else
                            cout<<"Figlio sx inesistente!"<<endl;
                        break;
                    case 2:
                        if(currElement->HasRightChild())
                        {
                            parent.Push(currElement);
                            currElement = &currElement->RightChild();
                        }
                        else
                            cout<<"Figlio dx inesistente!"<<endl;
                        break;
                    case 3:
                        if(!parent.Empty()) currElement = parent.TopNPop();
                        else cout<<"Non hai ancora effettuato nessuna discesa nell'albero!"<<endl;
                        break;
                    case 0:
                        break;
                    default:
                        cout<<"Opzione non valida, riprovare."<<endl;
                        break;
                    }

                } while (sceltaExp != 0);
                                
                                
                break;
            case Operazione::TopNPop:
                lasd::ForwardIterator<int>* it;
                cout<<"Che tipo di iteratore si vuole utilizzare?\n1. PreOrder;\n2. PostOrder;\n3. Breadth;\n4. InOrder."<<endl;
                cin>>sceltaExp;

                if(sceltaExp ==1) it = new lasd::BTPreOrderIterator<int>(testBT);
                else if(sceltaExp == 2) it = new lasd::BTPostOrderIterator<int>(testBT);
                else if(sceltaExp == 3)it = new lasd::BTBreadthIterator<int>(testBT);
                else it = new lasd::BTInOrderIterator<int>(testBT);

                do
                {
                    cout<<"1. Stampa elemento corrente"<<endl<<"2. Vai al prossimo elemento"<<endl<<"3. Modifica elemento corrente"<<endl;
                    cin>>sceltaExp;

                    if(sceltaExp == 1) cout<<"L'elemento corrente e': "<<it->operator*()<<endl;
                    else if(sceltaExp == 3) 
                    {
                        cout<<"Quale valore deve avere il nodo corrente?"<<endl;
                        cin>>testval;
                        it->operator*() = testval;
                    }
                    else it->operator++();

                    if(it->Terminated())cout<<"Termine esplorazione!"<<endl<<endl;  
                } while (sceltaExp!= 0 && !it->Terminated());
                
                delete it;

                break;                
            default:
                cout<<"Operazione non valida, riprovare."<<endl<<endl<<endl<<endl;
                break;
            }

        } while (scelta != Operazione::End);
    
    }
    else if(tp == Tipo::Double)
    {
        lasd::StackLst<lasd::BinaryTree<double>::Node*> parent;
        lasd::BinaryTree<double>::Node* currElement = nullptr;
        int sceltaExp;
        int contaScelta;
        double testval;
        double res;
        lasd::Vector<double> sourcevec(dim);
        for(int i = 0; i <dim; i++)
        {
            sourcevec[i] = trunc((double) distAndNeg(gen)/distUnder(gen) *100)/100;
        }
        lasd::BinaryTreeLnk<double> testBT(sourcevec);
        do
        {
            cout<<"1. Visita in Ampiezza, PreOrder, PostOrder e Order"<<endl<<"2. Controllo di esistenza di un valore"<<endl<<"3.  Somma di tutti i valori maggiori di uno a scelta"<<endl<<"4. Elevazione al cubo di tutti i valori"<<endl<<"5. Esplorazione dell'albero"<<endl<<"6. Esplorazione per iteratori"<<endl<<"0. Uscita dal test"<<endl<<"0. Uscita dal test"<<endl;
            cin>>input;
            if(input ==1 ) scelta = Operazione::FullContainer;    
            if(input ==2 ) scelta = Operazione::CheckExist;
            if(input ==3 ) scelta = Operazione::ProprietaryFoldFun;
            if(input ==4 ) scelta = Operazione::ProprietaryMapFun;
            if(input == 5) scelta = Operazione::LibFunct;
            if(input==6) scelta = Operazione::TopNPop;
            if(input ==0 ) scelta = Operazione::End;
            if(input > 6 || input < 0) scelta = Operazione::Invalid;

            switch (scelta)
            {
            case  Operazione::FullContainer:
                cout<<"Visita in Ampiezza : ";
                testBT.MapBreadth(VisualizeContainer<double>,nullptr);
                cout<<endl<<endl;
                cout<<"Visita in PreOrder : ";
                testBT.MapPreOrder(VisualizeContainer<double>,nullptr);
                cout<<endl<<endl;
                cout<<"Visita in PostOrder : ";
                testBT.MapPostOrder(VisualizeContainer<double>,nullptr);
                cout<<endl<<endl;
                cout<<"Visita in Order : ";  
                testBT.MapInOrder(VisualizeContainer<double>,nullptr); 
                cout<<endl<<endl;     
                break;
            case Operazione::CheckExist:
                cout<<"Di quale valore si desidera testare l'esistenza? ";
                cin>>testval;
                cout<<testval<<(testBT.Exists(testval)? " " :   " non")<<" esiste!"<<endl;
                break;
                break;
            case Operazione::ProprietaryFoldFun:
                cout<<"Qual'e il valore in input? "; cin>>input;
                res = 0;
                testBT.FoldPreOrder(SumIfHigherThanN, &testval , &res);
                cout<<endl<<endl;
                cout<<"Risultato: "<<res;
                cout<<endl<<endl;
                break;

            case Operazione::ProprietaryMapFun:
                testBT.MapPreOrder(MultiplyByItself2Times,nullptr);
                cout<<endl<<endl;
                cout<<"Risultato: ";
                testBT.MapBreadth(VisualizeContainer<double>,nullptr);
                cout<<endl<<endl;
                break;
            
            case Operazione::End:
                break;
            case Operazione::LibFunct:
                currElement = &testBT.Root();
                
                do
                {  
                    contaScelta = 0;
                    cout<<"Elemento corrente: "<<currElement->Element()<<endl;
                    cout<<"1. Accesso al figlio sx"<<endl<<"2. Accesso al figlio dx"<<endl<<"3. Ritorna al nodo precedente"<<endl;
                    cout<<"0. Ritorna al menu precedente"<<endl;
                    cin>>sceltaExp;

                    switch (sceltaExp)
                    {
                    case 1:
                        parent.Push(currElement);
                        currElement = &currElement->LeftChild();
                        break;
                    case 2:
                        parent.Push(currElement);
                        currElement = &currElement->RightChild();
                        break;
                    case 3:
                        currElement = parent.TopNPop();
                        break;
                    case 0:
                        break;
                    default:
                        cout<<"Opzione non valida, riprovare."<<endl;
                        break;
                    }

                } while (sceltaExp != 0);
                                
                                
                break;
                case Operazione::TopNPop:
                lasd::ForwardIterator<double>* it;
                cout<<"Che tipo di iteratore si vuole utilizzare?\n1. PreOrder;\n2. PostOrder;\n3. Breadth;\n4. InOrder."<<endl;
                cin>>sceltaExp;

                if(sceltaExp ==1) it = new lasd::BTPreOrderIterator<double>(testBT);
                else if(sceltaExp == 2) it = new lasd::BTPostOrderIterator<double>(testBT);
                else if(sceltaExp == 3)it = new lasd::BTBreadthIterator<double>(testBT);
                else it = new lasd::BTInOrderIterator<double>(testBT);

                do
                {
                    cout<<"1. Stampa elemento corrente"<<endl<<"2. Vai al prossimo elemento"<<endl<<"3. Modifica elemento corrente"<<endl;
                    cin>>sceltaExp;

                    if(sceltaExp == 1) cout<<"L'elemento corrente e': "<<it->operator*()<<endl;
                    else if(sceltaExp == 3) 
                    {
                        cout<<"Quale valore deve avere il nodo corrente?"<<endl;
                        cin>>testval;
                        it->operator*() = testval;
                    }
                    else it->operator++();

                    if(it->Terminated())cout<<"Termine esplorazione!"<<endl<<endl;  
                } while (sceltaExp!= 0 && !it->Terminated());
                
                delete it;

                break;
            default:
                cout<<"Operazione non valida, riprovare."<<endl<<endl<<endl<<endl;
                break;
            }

        } while (scelta != Operazione::End);
    }
    else if(tp == Tipo::String)
    {
        lasd::StackLst<lasd::BinaryTree<string>::Node*> parent;
        lasd::BinaryTree<string>::Node* currElement = nullptr;
        int sceltaExp;
        int contaScelta;
        lasd::Vector<string> sourcevec(dim);
        string res;
        string testval;
        int dimatt = 0;

        for(int i = 0; i<dim; i++)
        {
            res =init + CHARACTERS[distC(gen)];    
            dimatt = 1;
            while(dimatt < 10 && randomstop(gen)!= 0)
            {
                res = res+CHARACTERS[distC(gen)];
                dimatt++;
            }
            sourcevec[i] = res;
        }
        lasd::BinaryTreeLnk<string> testBT(sourcevec);
        do
        {
            cout<<"1. Visita in Ampiezza, PreOrder, PostOrder e Order"<<endl<<"2. Controllo di esistenza di un valore"<<endl<<"3.  Concatenazione di tutte le stringhe minori di un valore a scelta"<<endl<<"4. Concatenazione in testa di tutte le stringhe di una a scelta"<<endl<<"5. Esplorazione dell'albero"<<endl<<"6. Esplorazione per iteratori"<<endl<<"0. Uscita dal test"<<endl<<"0. Uscita dal test"<<endl;
            cin>>input;
            if(input ==1 ) scelta = Operazione::FullContainer;    
            if(input ==2 ) scelta = Operazione::CheckExist;
            if(input ==3 ) scelta = Operazione::ProprietaryFoldFun;
            if(input ==4 ) scelta = Operazione::ProprietaryMapFun;
            if(input ==5) scelta = Operazione::LibFunct;
            if(input == 6) scelta = Operazione::TopNPop;
            if(input ==0 ) scelta = Operazione::End;
            if(input > 6 || input < 0) scelta = Operazione::Invalid;

            switch (scelta)
            {
            case  Operazione::FullContainer:
                cout<<"Visita in Ampiezza : ";
                testBT.MapBreadth(VisualizeContainer<string>,nullptr);
                cout<<endl<<endl;
                cout<<"Visita in PreOrder : ";
                testBT.MapPreOrder(VisualizeContainer<string>,nullptr);
                cout<<endl<<endl;
                cout<<"Visita in PostOrder : ";
                testBT.MapPostOrder(VisualizeContainer<string>,nullptr);
                cout<<endl<<endl;
                cout<<"Visita in Order : ";  
                testBT.MapInOrder(VisualizeContainer<string>,nullptr); 
                cout<<endl<<endl;     
                break;
            case Operazione::CheckExist:
                cout<<"Di quale valore si desidera testare l'esistenza? ";
                cin>>testval;
                cout<<testval<<(testBT.Exists(testval)? " " : " non")<<" esiste!"<<endl;
                break;
            case Operazione::ProprietaryFoldFun:
                cout<<"Qual'e il valore in input? "; cin>>input;
                res = init;
                testBT.FoldPreOrder(AppendIfLessThanN, &input , &res);
                cout<<endl<<endl;
                cout<<"Risultato: "<<res;
                cout<<endl<<endl;
                break;

            case Operazione::ProprietaryMapFun:
                cout<<"Qual'e il valore in input? "; cin>>testval;
                testBT.MapPreOrder(AppendV, &testval);
                cout<<endl<<endl;
                cout<<"Risultato: ";
                testBT.MapBreadth(VisualizeContainer<string>,nullptr);
                cout<<endl<<endl;
                break;
            
            case Operazione::End:
                break;
            case Operazione::LibFunct:
                currElement = &testBT.Root();
                
                do
                {  
                    contaScelta = 0;
                    cout<<"Elemento corrente: "<<currElement->Element()<<endl;
                    cout<<"1. Accesso al figlio sx"<<endl<<"2. Accesso al figlio dx"<<endl<<"3. Ritorna al nodo precedente"<<endl;
                    cout<<"0. Ritorna al menu precedente"<<endl;
                    cin>>sceltaExp;

                    switch (sceltaExp)
                    {
                    case 1:
                        parent.Push(currElement);
                        currElement = &currElement->LeftChild();
                        break;
                    case 2:
                        parent.Push(currElement);
                        currElement = &currElement->RightChild();
                        break;
                    case 3:
                        currElement = parent.TopNPop();
                        break;
                    case 0:
                        break;
                    default:
                        cout<<"Opzione non valida, riprovare."<<endl;
                        break;
                    }

                } while (sceltaExp != 0);
                                
                                
                break;
                lasd::ForwardIterator<string>* it;
                cout<<"Che tipo di iteratore si vuole utilizzare?\n1. PreOrder;\n2. PostOrder;\n3. Breadth;\n4. InOrder."<<endl;
                cin>>sceltaExp;

                if(sceltaExp ==1) it = new lasd::BTPreOrderIterator<string>(testBT);
                else if(sceltaExp == 2) it = new lasd::BTPostOrderIterator<string>(testBT);
                else if(sceltaExp == 3)it = new lasd::BTBreadthIterator<string>(testBT);
                else it = new lasd::BTInOrderIterator<string>(testBT);

                do
                {
                    cout<<"1. Stampa elemento corrente"<<endl<<"2. Vai al prossimo elemento"<<endl<<"3. Modifica elemento corrente"<<endl;
                    cin>>sceltaExp;

                    if(sceltaExp == 1) cout<<"L'elemento corrente e': "<<it->operator*()<<endl;
                    else if(sceltaExp == 3) 
                    {
                        cout<<"Quale valore deve avere il nodo corrente?"<<endl;
                        cin>>testval;
                        it->operator*() = testval;
                    }
                    else it->operator++();

                    if(it->Terminated())cout<<"Termine esplorazione!"<<endl<<endl;  
                } while (sceltaExp!= 0 && !it->Terminated());
                
                delete it;

                break;                
            default:
                cout<<"Operazione non valida, riprovare."<<endl<<endl<<endl<<endl;
                break;
            }
        }while(scelta != Operazione::End);
    }
}


void TestQueueLst(Tipo tp, ulong dim)
{
    if(tp == Tipo::Int)
        {
            Operazione op = Operazione::Invalid;
            lasd::QueueLst<int> testS;
            int input;
            
            int n;
            int res = 0;
            
            int test;
            for (int i = 0; i<dim ;i++ )
            {
                testS.Enqueue(dist(gen));
            } 

            while(op != Operazione::End)
            {  
                op = Operazione::Invalid;
                cout<<"Scegliere l'operazione che si desidera effettuare:"<<endl<<"1. Visualizzare il primo elemento"<<endl<<"2. Effettuare TopNPop"<<endl<<"3. Test di vuotezza della struttura"<<endl<<"4. Controllo della dimensione della struttura"<<endl<<"5. Svuotamento della struttura "<<endl<<"6. Inserimento di un valore in testa"<<endl<<"0. Fine test"<<endl;                  
                cin>>input;
                if(input == 1) op = Operazione::Top;
                if(input == 2) op = Operazione::TopNPop;
                if(input == 3) op = Operazione::EmptinessCheck;
                if(input == 4) op = Operazione::CheckDim;
                if(input == 5) op = Operazione::Clear;
                if(input == 6) op = Operazione::LibFunct;
                if(input == 0) op = Operazione::End;

                switch (op)
                {
                case Operazione::Top:
                    cout<<"Il primo elemento è: "<<testS.Head()<<endl;
                    cout<<endl;
                    break;
                case Operazione::TopNPop:
                    cout<<"Rimovo l'elemento in testa...: "<<testS.HeadNDequeue()<<endl;
                    cout<<endl;
                    break;
                case Operazione::EmptinessCheck:
                    cout<<"La struttura "<<(testS.Empty()? "e " : "non e ")<<"vuota!"<<endl;
                    cout<<endl<<endl;
                    break;
                case Operazione::CheckDim:
                    cout<<"La struttura contiene "<<testS.Size()<<" valori!"<<endl;
                    break;
                case Operazione::Clear:
                    cout<<"Svuoto la struttura... ";
                    testS.Clear();
                    cout<<endl;
                    break;
                case Operazione::LibFunct:
                    cout<<"Quale valore deve essere inserito? ";
                    cin>>test;
                    cout<<"Inserisco "<<test<<" in testa!"<<endl;
                    testS.Enqueue(test);
                    break;
                case Operazione::End:
                    cout<<"Fine test su StackList!"<<endl;
                    break;
                default:
                    cout<<"Operazione non valida, riprovare"<<endl;            
                }
            }
        }
        else if(tp == Tipo::Double)
        {
            Operazione op = Operazione::Invalid;
            lasd::QueueLst<double> testS;
            int input;
            double n;
            double res = 1;
            double test;
        

            for (int i = 0; i<testS.Size();i++ )
            {
                testS.Enqueue((double) (trunc((double) ((double) distAndNeg(gen)/(double)(distUnder(gen)) * 100))/100));

            } 

            while(op != Operazione::End)
            {  
                op = Operazione::Invalid;
                cout<<"Scegliere l'operazione che si desidera effettuare:"<<endl<<"1. Visualizzare il primo elemento"<<endl<<"2. Effettuare TopNPop"<<endl<<"3. Test di vuotezza della struttura"<<endl<<"4. Controllo della dimensione della struttura"<<endl<<"5. Svuotamento della struttura "<<endl<<"6. Inserimento di un valore in testa"<<endl<<"0. Fine test"<<endl;                  
                cin>>input;
                if(input == 1) op = Operazione::Top;
                if(input == 2) op = Operazione::TopNPop;
                if(input == 3) op = Operazione::EmptinessCheck;
                if(input == 4) op = Operazione::CheckDim;
                if(input == 5) op = Operazione::Clear;
                if(input == 6) op = Operazione::LibFunct;
                if(input == 0) op = Operazione::End;

                switch (op)
                {
                case Operazione::Top:
                    cout<<"Il primo elemento è: "<<testS.Head()<<endl;
                    cout<<endl;
                    break;
                case Operazione::TopNPop:
                    cout<<"Rimovo l'elemento in testa...: "<<testS.HeadNDequeue()<<endl;
                    cout<<endl;
                    break;
                case Operazione::EmptinessCheck:
                    cout<<"La struttura "<<(testS.Empty()? "e " : "non e ")<<"vuota!"<<endl;
                    cout<<endl<<endl;
                    break;
                case Operazione::CheckDim:
                    cout<<"La struttura contiene "<<testS.Size()<<" valori!"<<endl;
                    break;
                case Operazione::Clear:
                    cout<<"Svuoto la struttura... ";
                    testS.Clear();
                    cout<<endl;
                    break;
                case Operazione::LibFunct:
                    cout<<"Quale valore deve essere inserito? ";
                    cin>>test;
                    cout<<"Inserisco "<<test<<" in testa!"<<endl;
                    testS.Enqueue(test);
                    break;
                case Operazione::End:
                    cout<<"Fine test su StackList!"<<endl;
                    break;
                default:
                    cout<<"Operazione non valida, riprovare"<<endl;            
                }
            }       
        }
        else if(tp == Tipo::String)
        {
            Operazione op = Operazione::Invalid;
            lasd::QueueLst<string> testS;
            int input;
            int n;
            string res = init;
            string test;
            int dimatt;
            int rs;
            ulong i = 0;
            while(i <= dim && dim != 0)
            {
                string a = init;
                a+= CHARACTERS[distC(gen)];
                dimatt = 1;
                while(dimatt<10 && randomstop(gen)!=1)
                {
                    a += CHARACTERS[distC(gen)];
                    dimatt++;
                }
                testS.Enqueue(a);
                i++;
            }

            while(op != Operazione::End)
            {  
                op = Operazione::Invalid;
                cout<<"Scegliere l'operazione che si desidera effettuare:"<<endl<<"1. Visualizzare il primo elemento"<<endl<<"2. Effettuare TopNPop"<<endl<<"3. Test di vuotezza della struttura"<<endl<<"4. Controllo della dimensione della struttura"<<endl<<"5. Svuotamento della struttura "<<endl<<"6. Inserimento di un valore in testa"<<endl<<"0. Fine test"<<endl;                  
                cin>>input;
                if(input == 1) op = Operazione::Top;
                if(input == 2) op = Operazione::TopNPop;
                if(input == 3) op = Operazione::EmptinessCheck;
                if(input == 4) op = Operazione::CheckDim;
                if(input == 5) op = Operazione::Clear;
                if(input == 6) op = Operazione::LibFunct;
                if(input == 0) op = Operazione::End;

                switch (op)
                {
                case Operazione::Top:
                    cout<<"Il primo elemento è: "<<testS.Head()<<endl;
                    cout<<endl;
                    break;
                case Operazione::TopNPop:
                    cout<<"Rimovo l'elemento in testa...: "<<testS.HeadNDequeue()<<endl;
                    cout<<endl;
                    break;
                case Operazione::EmptinessCheck:
                    cout<<"La struttura "<<(testS.Empty()? "e " : "non e ")<<"vuota!"<<endl;
                    cout<<endl<<endl;
                    break;
                case Operazione::CheckDim:
                    cout<<"La struttura contiene "<<testS.Size()<<" valori!"<<endl;
                    break;
                case Operazione::Clear:
                    cout<<"Svuoto la struttura... ";
                    testS.Clear();
                    cout<<endl;
                    break;
                case Operazione::LibFunct:
                    cout<<"Quale valore deve essere inserito? ";
                    cin>>test;
                    cout<<"Inserisco "<<test<<" in testa!"<<endl;
                    testS.Enqueue(test);
                    break;
                case Operazione::End:
                    cout<<"Fine test su StackList!"<<endl;
                    break;
                default:
                    cout<<"Operazione non valida, riprovare"<<endl;            
                }
            }       
        }
}

void TestQueueVec(Tipo tp, ulong dim)
{
    if(tp == Tipo::Int)
        {
            Operazione op = Operazione::Invalid;
            lasd::QueueVec<int> testS;
            int input;
            int n;
            int res = 0;
            int test;
            for (int i = 0; i<dim ;i++ )
            {
                testS.Enqueue(dist(gen));
            } 

            while(op != Operazione::End)
            {  
                op = Operazione::Invalid;
                cout<<"Scegliere l'operazione che si desidera effettuare:"<<endl<<"1. Visualizzare il primo elemento"<<endl<<"2. Effettuare TopNPop"<<endl<<"3. Test di vuotezza della struttura"<<endl<<"4. Controllo della dimensione della struttura"<<endl<<"5. Svuotamento della struttura "<<endl<<"6. Inserimento di un valore in testa"<<endl<<"0. Fine test"<<endl;                  
                cin>>input;
                if(input == 1) op = Operazione::Top;
                if(input == 2) op = Operazione::TopNPop;
                if(input == 3) op = Operazione::EmptinessCheck;
                if(input == 4) op = Operazione::CheckDim;
                if(input == 5) op = Operazione::Clear;
                if(input == 6) op = Operazione::LibFunct;
                if(input == 0) op = Operazione::End;

                switch (op)
                {
                case Operazione::Top:
                    cout<<"Il primo elemento è: "<<testS.Head()<<endl;
                    cout<<endl;
                    break;
                case Operazione::TopNPop:
                    cout<<"Rimovo l'elemento in testa...: "<<testS.HeadNDequeue()<<endl;
                    cout<<endl;
                    break;
                case Operazione::EmptinessCheck:
                    cout<<"La struttura "<<(testS.Empty()? "e " : "non e ")<<"vuota!"<<endl;
                    cout<<endl<<endl;
                    break;
                case Operazione::CheckDim:
                    cout<<"La struttura contiene "<<testS.Size()<<" valori!"<<endl;
                    break;
                case Operazione::Clear:
                    cout<<"Svuoto la struttura... ";
                    testS.Clear();
                    cout<<endl;
                    break;
                case Operazione::LibFunct:
                    cout<<"Quale valore deve essere inserito? ";
                    cin>>test;
                    cout<<"Inserisco "<<test<<" in testa!"<<endl;
                    testS.Enqueue(test);
                    break;
                case Operazione::End:
                    cout<<"Fine test su StackList!"<<endl;
                    break;
                default:
                    cout<<"Operazione non valida, riprovare"<<endl;            
                }
            }
        }
        else if(tp == Tipo::Double)
        {
            Operazione op = Operazione::Invalid;
            lasd::QueueVec<double> testS;
            int input;
            double n;
            double res = 1;
            double test;
        

            for (int i = 0; i<testS.Size();i++ )
            {
                testS.Enqueue((double) (trunc((double) ((double) distAndNeg(gen)/(double)(distUnder(gen)) * 100))/100));

            } 

            while(op != Operazione::End)
            {  
                op = Operazione::Invalid;
                cout<<"Scegliere l'operazione che si desidera effettuare:"<<endl<<"1. Visualizzare il primo elemento"<<endl<<"2. Effettuare TopNPop"<<endl<<"3. Test di vuotezza della struttura"<<endl<<"4. Controllo della dimensione della struttura"<<endl<<"5. Svuotamento della struttura "<<endl<<"6. Inserimento di un valore in testa"<<endl<<"0. Fine test"<<endl;                  
                cin>>input;
                if(input == 1) op = Operazione::Top;
                if(input == 2) op = Operazione::TopNPop;
                if(input == 3) op = Operazione::EmptinessCheck;
                if(input == 4) op = Operazione::CheckDim;
                if(input == 5) op = Operazione::Clear;
                if(input == 6) op = Operazione::LibFunct;
                if(input == 0) op = Operazione::End;

                switch (op)
                {
                case Operazione::Top:
                    cout<<"Il primo elemento è: "<<testS.Head()<<endl;
                    cout<<endl;
                    break;
                case Operazione::TopNPop:
                    cout<<"Rimovo l'elemento in testa...: "<<testS.HeadNDequeue()<<endl;
                    cout<<endl;
                    break;
                case Operazione::EmptinessCheck:
                    cout<<"La struttura "<<(testS.Empty()? "e " : "non e ")<<"vuota!"<<endl;
                    cout<<endl<<endl;
                    break;
                case Operazione::CheckDim:
                    cout<<"La struttura contiene "<<testS.Size()<<" valori!"<<endl;
                    break;
                case Operazione::Clear:
                    cout<<"Svuoto la struttura... ";
                    testS.Clear();
                    cout<<endl;
                    break;
                case Operazione::LibFunct:
                    cout<<"Quale valore deve essere inserito? ";
                    cin>>test;
                    cout<<"Inserisco "<<test<<" in testa!"<<endl;
                    testS.Enqueue(test);
                    break;
                case Operazione::End:
                    cout<<"Fine test su StackList!"<<endl;
                    break;
                default:
                    cout<<"Operazione non valida, riprovare"<<endl;            
                }
            }       
        }
        else if(tp == Tipo::String)
        {
            Operazione op = Operazione::Invalid;
            lasd::QueueVec<string> testS;
            int input;
            int n;
            string res = init;
            string test;
            int dimatt;
            int rs;
            ulong i = 0;
            while(i <= dim && dim != 0)
            {
                string a = init;
                a+= CHARACTERS[distC(gen)];
                dimatt = 1;
                while(dimatt<10 && randomstop(gen)!=1)
                {
                    a += CHARACTERS[distC(gen)];
                    dimatt++;
                }
                testS.Enqueue(a);
                i++;
            }

            while(op != Operazione::End)
            {  
                op = Operazione::Invalid;
                cout<<"Scegliere l'operazione che si desidera effettuare:"<<endl<<"1. Visualizzare il primo elemento"<<endl<<"2. Effettuare TopNPop"<<endl<<"3. Test di vuotezza della struttura"<<endl<<"4. Controllo della dimensione della struttura"<<endl<<"5. Svuotamento della struttura "<<endl<<"6. Inserimento di un valore in testa"<<endl<<"0. Fine test"<<endl;                  
                cin>>input;
                if(input == 1) op = Operazione::Top;
                if(input == 2) op = Operazione::TopNPop;
                if(input == 3) op = Operazione::EmptinessCheck;
                if(input == 4) op = Operazione::CheckDim;
                if(input == 5) op = Operazione::Clear;
                if(input == 6) op = Operazione::LibFunct;
                if(input == 0) op = Operazione::End;

                switch (op)
                {
                case Operazione::Top:
                    cout<<"Il primo elemento è: "<<testS.Head()<<endl;
                    cout<<endl;
                    break;
                case Operazione::TopNPop:
                    cout<<"Rimovo l'elemento in testa...: "<<testS.HeadNDequeue()<<endl;
                    cout<<endl;
                    break;
                case Operazione::EmptinessCheck:
                    cout<<"La struttura "<<(testS.Empty()? "e " : "non e ")<<"vuota!"<<endl;
                    cout<<endl<<endl;
                    break;
                case Operazione::CheckDim:
                    cout<<"La struttura contiene "<<testS.Size()<<" valori!"<<endl;
                    break;
                case Operazione::Clear:
                    cout<<"Svuoto la struttura... ";
                    testS.Clear();
                    cout<<endl;
                    break;
                case Operazione::LibFunct:
                    cout<<"Quale valore deve essere inserito? ";
                    cin>>test;
                    cout<<"Inserisco "<<test<<" in testa!"<<endl;
                    testS.Enqueue(test);
                    break;
                case Operazione::End:
                    cout<<"Fine test su StackList!"<<endl;
                    break;
                default:
                    cout<<"Operazione non valida, riprovare"<<endl;            
                }
            }       
        }
}

void TestStackLst(Tipo tp, ulong dim)
{
        if(tp == Tipo::Int)
        {
            Operazione op = Operazione::Invalid;
            lasd::StackLst<int> testS;
            int input;
            int n;
            int res = 0;
            int test;
            for (int i = 0; i<dim ;i++ )
            {
                testS.Push(dist(gen));
            } 

            while(op != Operazione::End)
            {  
                op = Operazione::Invalid;
                cout<<"Scegliere l'operazione che si desidera effettuare:"<<endl<<"1. Visualizzare il primo elemento"<<endl<<"2. Effettuare TopNPop"<<endl<<"3. Test di vuotezza della struttura"<<endl<<"4. Controllo della dimensione della struttura"<<endl<<"5. Svuotamento della struttura "<<endl<<"6. Inserimento di un valore in testa"<<endl<<"0. Fine test"<<endl;                  
                cin>>input;
                if(input == 1) op = Operazione::Top;
                if(input == 2) op = Operazione::TopNPop;
                if(input == 3) op = Operazione::EmptinessCheck;
                if(input == 4) op = Operazione::CheckDim;
                if(input == 5) op = Operazione::Clear;
                if(input == 6) op = Operazione::LibFunct;
                if(input == 0) op = Operazione::End;

                switch (op)
                {
                case Operazione::Top:
                    cout<<"Il primo elemento è: "<<testS.Top()<<endl;
                    cout<<endl;
                    break;
                case Operazione::TopNPop:   
                    cout<<"Rimovo l'elemento in testa...: "<<testS.TopNPop()<<endl;
                    cout<<endl;
                    break;
                case Operazione::EmptinessCheck:
                    cout<<"La struttura "<<(testS.Empty()? "e " : "non e ")<<"vuota!"<<endl;
                    cout<<endl<<endl;
                    break;
                case Operazione::CheckDim:
                    cout<<"La struttura contiene "<<testS.Size()<<" valori!"<<endl;
                    break;
                case Operazione::Clear:
                    cout<<"Svuoto la struttura... ";
                    testS.Clear();
                    cout<<endl;
                    break;
                case Operazione::LibFunct:
                    cout<<"Quale valore deve essere inserito? ";
                    cin>>test;
                    cout<<"Inserisco "<<test<<" in testa!"<<endl;
                    testS.Push(test);
                    break;
                case Operazione::End:
                    cout<<"Fine test su StackList!"<<endl;
                    break;
                default:
                    cout<<"Operazione non valida, riprovare"<<endl;            
                }
            }
        }
        else if(tp == Tipo::Double)
        {
            Operazione op = Operazione::Invalid;
            lasd::StackLst<double> testS;
            int input;
            double n;
            double res = 1;
            double test;
        

            for (int i = 0; i<testS.Size();i++ )
            {
                testS.Push((double) (trunc((double) ((double) distAndNeg(gen)/(double)(distUnder(gen)) * 100))/100));

            } 

            while(op != Operazione::End)
            {  
                op = Operazione::Invalid;
                cout<<"Scegliere l'operazione che si desidera effettuare:"<<endl<<"1. Visualizzare il primo elemento"<<endl<<"2. Effettuare TopNPop"<<endl<<"3. Test di vuotezza della struttura"<<endl<<"4. Controllo della dimensione della struttura"<<endl<<"5. Svuotamento della struttura "<<endl<<"6. Inserimento di un valore in testa"<<endl<<"0. Fine test"<<endl;                  
                cin>>input;
                if(input == 1) op = Operazione::Top;
                if(input == 2) op = Operazione::TopNPop;
                if(input == 3) op = Operazione::EmptinessCheck;
                if(input == 4) op = Operazione::CheckDim;
                if(input == 5) op = Operazione::Clear;
                if(input == 6) op = Operazione::LibFunct;
                if(input == 0) op = Operazione::End;

                switch (op)
                {
                case Operazione::Top:
                    cout<<"Il primo elemento è: "<<testS.Top()<<endl;
                    cout<<endl;
                    break;
                case Operazione::TopNPop:
                    cout<<"Rimovo l'elemento in testa...: "<<testS.TopNPop()<<endl;
                    cout<<endl;
                    break;
                case Operazione::EmptinessCheck:
                    cout<<"La struttura "<<(testS.Empty()? "e " : "non e ")<<"vuota!"<<endl;
                    cout<<endl<<endl;
                    break;
                case Operazione::CheckDim:
                    cout<<"La struttura contiene "<<testS.Size()<<" valori!"<<endl;
                    break;
                case Operazione::Clear:
                    cout<<"Svuoto la struttura... ";
                    testS.Clear();
                    cout<<endl;
                    break;
                case Operazione::LibFunct:
                    cout<<"Quale valore deve essere inserito? ";
                    cin>>test;
                    cout<<"Inserisco "<<test<<" in testa!"<<endl;
                    testS.Push(test);
                    break;
                case Operazione::End:
                    cout<<"Fine test su StackList!"<<endl;
                    break;
                default:
                    cout<<"Operazione non valida, riprovare"<<endl;            
                }
            }       
        }
        else if(tp == Tipo::String)
        {
            Operazione op = Operazione::Invalid;
            lasd::StackLst<string> testS;
            int input;
            int n;
            string res = init;
            string test;
            int dimatt;
            int rs;
            ulong i = 0;
            while(i <= dim && dim != 0)
            {
                string a = init;
                a+= CHARACTERS[distC(gen)];
                dimatt = 1;
                while(dimatt<10 && randomstop(gen)!=1)
                {
                    a += CHARACTERS[distC(gen)];
                    dimatt++;
                }
                testS.Push(a);
                i++;
            }

            while(op != Operazione::End)
            {  
                op = Operazione::Invalid;
                cout<<"Scegliere l'operazione che si desidera effettuare:"<<endl<<"1. Visualizzare il primo elemento"<<endl<<"2. Effettuare TopNPop"<<endl<<"3. Test di vuotezza della struttura"<<endl<<"4. Controllo della dimensione della struttura"<<endl<<"5. Svuotamento della struttura "<<endl<<"6. Inserimento di un valore in testa"<<endl<<"0. Fine test"<<endl;                  
                cin>>input;
                if(input == 1) op = Operazione::Top;
                if(input == 2) op = Operazione::TopNPop;
                if(input == 3) op = Operazione::EmptinessCheck;
                if(input == 4) op = Operazione::CheckDim;
                if(input == 5) op = Operazione::Clear;
                if(input == 6) op = Operazione::LibFunct;
                if(input == 0) op = Operazione::End;

                switch (op)
                {
                case Operazione::Top:
                    cout<<"Il primo elemento è: "<<testS.Top()<<endl;
                    cout<<endl;
                    break;
                case Operazione::TopNPop:
                    cout<<"Rimovo l'elemento in testa...: "<<testS.TopNPop()<<endl;
                    cout<<endl;
                    break;
                case Operazione::EmptinessCheck:
                    cout<<"La struttura "<<(testS.Empty()? "e " : "non e ")<<"vuota!"<<endl;
                    cout<<endl<<endl;
                    break;
                case Operazione::CheckDim:
                    cout<<"La struttura contiene "<<testS.Size()<<" valori!"<<endl;
                    break;
                case Operazione::Clear:
                    cout<<"Svuoto la struttura... ";
                    testS.Clear();
                    cout<<endl;
                    break;
                case Operazione::LibFunct:
                    cout<<"Quale valore deve essere inserito? ";
                    cin>>test;
                    cout<<"Inserisco "<<test<<" in testa!"<<endl;
                    testS.Push(test);
                    break;
                case Operazione::End:
                    cout<<"Fine test su StackList!"<<endl;
                    break;
                default:
                    cout<<"Operazione non valida, riprovare"<<endl;            
                }
            }       
        }
}

void TestStackVec(Tipo tp, ulong dim)
{
        if(tp == Tipo::Int)
        {
            Operazione op = Operazione::Invalid;
            lasd::StackLst<int> testS;
            int input;
            int n;
            int res = 0;
            int test;
            for (int i = 0; i<dim ;i++ )
            {
                testS.Push(dist(gen));
            } 

            while(op != Operazione::End)
            {  
                op = Operazione::Invalid;
                cout<<"Scegliere l'operazione che si desidera effettuare:"<<endl<<"1. Visualizzare il primo elemento"<<endl<<"2. Effettuare TopNPop"<<endl<<"3. Test di vuotezza della struttura"<<endl<<"4. Controllo della dimensione della struttura"<<endl<<"5. Svuotamento della struttura "<<endl<<"6. Inserimento di un valore in testa"<<endl<<"0. Fine test"<<endl;                  
                cin>>input;
                if(input == 1) op = Operazione::Top;
                if(input == 2) op = Operazione::TopNPop;
                if(input == 3) op = Operazione::EmptinessCheck;
                if(input == 4) op = Operazione::CheckDim;
                if(input == 5) op = Operazione::Clear;
                if(input == 6) op = Operazione::LibFunct;
                if(input == 0) op = Operazione::End;

                switch (op)
                {
                case Operazione::Top:
                    cout<<"Il primo elemento è: "<<testS.Top()<<endl;
                    cout<<endl;
                    break;
                case Operazione::TopNPop:
                    cout<<"Rimovo l'elemento in testa...: "<<testS.TopNPop()<<endl;
                    cout<<endl;
                    break;
                case Operazione::EmptinessCheck:
                    cout<<"La struttura "<<(testS.Empty()? "e " : "non e ")<<"vuota!"<<endl;
                    cout<<endl<<endl;
                    break;
                case Operazione::CheckDim:
                    cout<<"La struttura contiene "<<testS.Size()<<" valori!"<<endl;
                    break;
                case Operazione::Clear:
                    cout<<"Svuoto la struttura... ";
                    testS.Clear();
                    cout<<endl;
                    break;
                case Operazione::LibFunct:
                    cout<<"Quale valore deve essere inserito? ";
                    cin>>test;
                    cout<<"Inserisco "<<test<<" in testa!"<<endl;
                    testS.Push(test);
                    break;
                case Operazione::End:
                    cout<<"Fine test su StackList!"<<endl;
                    break;
                default:
                    cout<<"Operazione non valida, riprovare"<<endl;            
                }
            }
        }
        else if(tp == Tipo::Double)
        {
            Operazione op = Operazione::Invalid;
            lasd::StackVec<double> testS;
            int input;
            double n;
            double res = 1;
            double test;
        

            for (int i = 0; i<testS.Size();i++ )
            {
                testS.Push((double) (trunc((double) ((double) distAndNeg(gen)/(double)(distUnder(gen)) * 100))/100));

            } 

            while(op != Operazione::End)
            {  
                op = Operazione::Invalid;
                cout<<"Scegliere l'operazione che si desidera effettuare:"<<endl<<"1. Visualizzare il primo elemento"<<endl<<"2. Effettuare TopNPop"<<endl<<"3. Test di vuotezza della struttura"<<endl<<"4. Controllo della dimensione della struttura"<<endl<<"5. Svuotamento della struttura "<<endl<<"6. Inserimento di un valore in testa"<<endl<<"0. Fine test"<<endl;                  
                cin>>input;
                if(input == 1) op = Operazione::Top;
                if(input == 2) op = Operazione::TopNPop;
                if(input == 3) op = Operazione::EmptinessCheck;
                if(input == 4) op = Operazione::CheckDim;
                if(input == 5) op = Operazione::Clear;
                if(input == 6) op = Operazione::LibFunct;
                if(input == 0) op = Operazione::End;

                switch (op)
                {
                case Operazione::Top:
                    cout<<"Il primo elemento è: "<<testS.Top()<<endl;
                    cout<<endl;
                    break;
                case Operazione::TopNPop:
                    cout<<"Rimovo l'elemento in testa...: "<<testS.TopNPop()<<endl;
                    cout<<endl;
                    break;
                case Operazione::EmptinessCheck:
                    cout<<"La struttura "<<(testS.Empty()? "e " : "non e ")<<"vuota!"<<endl;
                    cout<<endl<<endl;
                    break;
                case Operazione::CheckDim:
                    cout<<"La struttura contiene "<<testS.Size()<<" valori!"<<endl;
                    break;
                case Operazione::Clear:
                    cout<<"Svuoto la struttura... ";
                    testS.Clear();
                    cout<<endl;
                    break;
                case Operazione::LibFunct:
                    cout<<"Quale valore deve essere inserito? ";
                    cin>>test;
                    cout<<"Inserisco "<<test<<" in testa!"<<endl;
                    testS.Push(test);
                    break;
                case Operazione::End:
                    cout<<"Fine test su StackList!"<<endl;
                    break;
                default:
                    cout<<"Operazione non valida, riprovare"<<endl;            
                }
            }       
        }
        else if(tp == Tipo::String)
        {
            Operazione op = Operazione::Invalid;
            lasd::StackVec<string> testS;
            int input;
            int n;
            string res = init;
            string test;
            int dimatt;
            int rs;
            ulong i = 0;
            while(i < dim && dim != 0)
            {
                string a = init;
                a+= CHARACTERS[distC(gen)];
                dimatt = 1;
                while(dimatt<10 && randomstop(gen)!=1)
                {
                    a += CHARACTERS[distC(gen)];
                    dimatt++;
                }
                testS.Push(a);
                i++;
            }

            while(op != Operazione::End)
            {  
                op = Operazione::Invalid;
                cout<<"Scegliere l'operazione che si desidera effettuare:"<<endl<<"1. Visualizzare il primo elemento"<<endl<<"2. Effettuare TopNPop"<<endl<<"3. Test di vuotezza della struttura"<<endl<<"4. Controllo della dimensione della struttura"<<endl<<"5. Svuotamento della struttura "<<endl<<"6. Inserimento di un valore in testa"<<endl<<"0. Fine test"<<endl;                  
                cin>>input;
                if(input == 1) op = Operazione::Top;
                if(input == 2) op = Operazione::TopNPop;
                if(input == 3) op = Operazione::EmptinessCheck;
                if(input == 4) op = Operazione::CheckDim;
                if(input == 5) op = Operazione::Clear;
                if(input == 6) op = Operazione::LibFunct;
                if(input == 0) op = Operazione::End;

                switch (op)
                {
                case Operazione::Top:
                    cout<<"Il primo elemento è: "<<testS.Top()<<endl;
                    cout<<endl;
                    break;
                case Operazione::TopNPop:
                    cout<<"Rimovo l'elemento in testa...: "<<testS.TopNPop()<<endl;
                    cout<<endl;
                    break;
                case Operazione::EmptinessCheck:
                    cout<<"La struttura "<<(testS.Empty()? "e " : "non e ")<<"vuota!"<<endl;
                    cout<<endl<<endl;
                    break;
                case Operazione::CheckDim:
                    cout<<"La struttura contiene "<<testS.Size()<<" valori!"<<endl;
                    break;
                case Operazione::Clear:
                    cout<<"Svuoto la struttura... ";
                    testS.Clear();
                    cout<<endl;
                    break;
                case Operazione::LibFunct:
                    cout<<"Quale valore deve essere inserito? ";
                    cin>>test;
                    cout<<"Inserisco "<<test<<" in testa!"<<endl;
                    testS.Push(test);
                    break;
                case Operazione::End:
                    cout<<"Fine test su StackList!"<<endl;
                    break;
                default:
                    cout<<"Operazione non valida, riprovare"<<endl;            
                }
            }       
        }
}

void Test(Struttura st, Tipo tp)
{
    ulong dim;
    cout<<"Inserire la dimensione desiderata per la stuttura: ";
    cin>>dim;
    cout<<endl;

    if(st == Struttura::Vettore)
    {
        if(tp == Tipo::Int)
        {
            Operazione op = Operazione::Invalid;
            lasd::Vector<int> testV(dim);
            ulong oldSiz;
            int input;
            int n;
            int res = 0;
            int test;
            for (int i = 0; i<testV.Size();i++ )
            {
                testV[i] = dist(gen);
            } 

            while(op != Operazione::End)
            {  
                op = Operazione::Invalid;
                cout<<"Scegliere l'operazione che si desidera effettuare:"<<endl<<"1. Visualizzare il primo elemento"<<endl<<"2. Visualizzare l'ultimo elemento"<<endl<<"3. Visualizzare tutti gli elementi"<<endl<<"4. Controllare l'esistenza di un valore arbitrario"<<endl<<"5. Sommare tutti i valori minori di un n arbitrario"<<endl<<"6. Raddoppiare tutti gli elementi"<<endl<<"7. Ridimensionamento dell'array"<<endl<<"0. Fine test"<<endl;                  
                cin>>input;
                if(input == 1) op = Operazione::Front;
                if(input == 2) op = Operazione::Back;
                if(input == 3) op = Operazione::FullContainer;
                if(input == 4) op = Operazione::CheckExist;
                if(input == 5) op = Operazione::ProprietaryFoldFun;
                if(input == 6) op = Operazione::ProprietaryMapFun;
                if(input == 7) op = Operazione::LibFunct;
                if(input == 0) op = Operazione::End;

                switch (op)
                {
                case Operazione::Front:
                    cout<<"Il primo elemento è: "<<testV.Front()<<endl;
                    cout<<endl;
                    break;
                case Operazione::Back:
                    cout<<"L'ultimo elemento è: "<<testV.Back()<<endl;
                    cout<<endl;
                    break;
                case Operazione::FullContainer:
                    cout<<"Stampo tutti gli elementi..."<<endl;
                    testV.Map(VisualizeContainer<int> , nullptr);
                    
                        cout<<endl<<endl;
                    break;
                case Operazione::CheckExist:
                    cout<<"Di quale elemento si desidera verificare l'esistenza? ";
                    cin>>test;
                    cout<<endl<<"Il valore "<<test<<(testV.Exists(test)? init : " non")<<" esiste!";
                    cout<<endl;
                    break;
                case Operazione::ProprietaryFoldFun:
                    cout<<"Qual'è il valore di n? ";
                    cin>>n;
                    res = 0;
                    testV.Fold(SumIfLessThanN,&n,&res);
                    cout<<"Il risultato è: "<<res<<"!"<<endl;
                    cout<<endl;
                    break;
                case Operazione::ProprietaryMapFun:
                    cout<<"Raddoppio tutti gli elementi..."<<endl;
                    testV.Map(DoubleThemUp, nullptr);
                    cout<<"Fatto!"<<endl;
                    break;
                case Operazione::LibFunct:
                    cout<<"Quale deve essere la nuova dimensione del Vettore?"<<endl;
                    cin>>input;
                    oldSiz = testV.Size();
                    testV.Resize(input);
                    if (oldSiz<testV.Size()) 
                        for (ulong i = oldSiz; i<testV.Size();i++ )
                        {
                            testV[i] = dist(gen);
                        } 
                    break;
                case Operazione::End:
                    cout<<"Fine test su Vettore!"<<endl;
                    break;
                default:
                    cout<<"Operazione non valida, riprovare"<<endl;            
                }
            }
        }
        else if(tp == Tipo::Double)
        {
            Operazione op = Operazione::Invalid;
            lasd::Vector<double> testV(dim);
            int input;
            ulong oldSiz;
            double n;
            double res = 1;
            double test;
        

            for (int i = 0; i<testV.Size();i++ )
            {
                testV[i] = (double) (trunc((double) ((double) distAndNeg(gen)/(double)(distUnder(gen)) * 100))/100);

            } 

            while(op != Operazione::End)
            {  
                op = Operazione::Invalid;
                cout<<"Scegliere l'operazione che si desidera effettuare:"<<endl<<"1. Visualizzare il primo elemento"<<endl<<"2. Visualizzare l'ultimo elemento"<<endl<<"3. Visualizzare tutti gli elementi"<<endl<<"4. Controllare l'esistenza di un valore arbitrario"<<endl<<"5. Sommare tutti i valori minori di un n arbitrario"<<endl<<"6. Raddoppiare tutti gli elementi"<<endl<<"7. Ridimensionamento dell'array"<<endl<<"0. Fine test"<<endl;                  
                cin>>input;
                if(input == 1) op = Operazione::Front;
                if(input == 2) op = Operazione::Back;
                if(input == 3) op = Operazione::FullContainer;
                if(input == 4) op = Operazione::CheckExist;
                if(input == 5) op = Operazione::ProprietaryFoldFun;
                if(input == 6) op = Operazione::ProprietaryMapFun;
                if(input == 7) op = Operazione::LibFunct;
                if(input == 0) op = Operazione::End;
                switch (op)
                {
                    case Operazione::Front:
                        cout<<"Il primo elemento è: "<<testV.Front()<<endl;
                        cout<<endl;
                        break;
                    case Operazione::Back:
                        cout<<"L'ultimo elemento è: "<<testV.Back()<<endl;
                        cout<<endl;
                        break;
                    case Operazione::FullContainer:
                        cout<<"Stampo tutti gli elementi..."<<endl;
                        cout<<endl;
                        testV.Map(VisualizeContainer<double> , nullptr);

                        cout<<endl<<endl;
                        break;
                    case Operazione::CheckExist:
                        cout<<"Di quale elemento si desidera verificare l'esistenza? ";
                        cin>>test;
                        cout<<endl<<"Il valore "<<test<<(testV.Exists(test)? init : " non")<<" esiste!";
                        cout<<endl;
                        cout<<endl;
                        break;
                    case Operazione::ProprietaryFoldFun:
                        cout<<"Qual'è il valore di n? ";
                        cin>>n;
                        res = 1;
                        testV.Fold(MultiplyIfHigherThanN,&n,&res);
                        cout<<"Il risultato è: "<<res<<"!"<<endl;
                        cout<<endl;
                        break;
                    case Operazione::ProprietaryMapFun:
                        cout<<"Applico la potenza di 2 a tutti gli elementi..."<<endl;
                        testV.Map(MultiplyByItself, nullptr);
                        cout<<"Fatto!"<<endl;
                        cout<<endl;
                        break;
                    case Operazione::LibFunct:
                        cout<<"Quale deve essere la nuova dimensione del Vettore?"<<endl;
                        cin>>input;
                        oldSiz = testV.Size();
                        testV.Resize(input);
                        if (oldSiz<testV.Size()) 
                            for (ulong i = oldSiz; i<testV.Size();i++ )
                            {
                                testV[i] = (double) (trunc((double) ((double) distAndNeg(gen)/(double)(distUnder(gen)) * 100))/100);
                            } 
                        break;
                    case Operazione::End:
                        cout<<"Fine test su Vettore!"<<endl;
                        cout<<endl;
                        break;
                    default:
                        cout<<"Operazione non valida, riprovare"<<endl;    
                        cout<<endl;        
                    }
            }       
        }
        else if(tp == Tipo::String)
        {
            Operazione op = Operazione::Invalid;
            lasd::Vector<string> testV(dim);
            int input;
            ulong oldSiz;
            int n;
            string res = init;
            string test;
            int dimatt;
            int rs;

            for (int i = 0; i<testV.Size();i++ )
            {
                string a = init;
                a+= CHARACTERS[distC(gen)];
                dimatt = 1;
                while(dimatt<10 && randomstop(gen)!=1)
                {
                    a += CHARACTERS[distC(gen)];
                    dimatt++;
                }
                testV[i] = a;
                i++;
            } 

            while(op != Operazione::End)
            {  
                op = Operazione::Invalid;
                cout<<"Scegliere l'operazione che si desidera effettuare:"<<endl<<"1. Visualizzare il primo elemento"<<endl<<"2. Visualizzare l'ultimo elemento"<<endl<<"3. Visualizzare tutti gli elementi"<<endl<<"4. Controllare l'esistenza di un valore arbitrario"<<endl<<"5. Sommare tutti i valori minori di un n arbitrario"<<endl<<"6. Raddoppiare tutti gli elementi"<<endl<<"7. Ridimensionamento dell'array"<<endl<<"0. Fine test"<<endl;                  
                cin>>input;
                if(input == 1) op = Operazione::Front;
                if(input == 2) op = Operazione::Back;
                if(input == 3) op = Operazione::FullContainer;
                if(input == 4) op = Operazione::CheckExist;
                if(input == 5) op = Operazione::ProprietaryFoldFun;
                if(input == 6) op = Operazione::ProprietaryMapFun;
                if(input == 7) op = Operazione::LibFunct;
                if(input == 0) op = Operazione::End;
                switch (op)
                {
                    case Operazione::Back:
                        cout<<"L'ultimo elemento è: "<<testV.Back()<<endl;
                        cout<<endl;
                        break;
                    case Operazione::FullContainer:
                        cout<<"Stampo tutti gli elementi..."<<endl;
                        cout<<endl;
                        testV.Map(VisualizeContainer<string> , nullptr);
                        
                        cout<<endl<<endl;                      
                        break;
                    case Operazione::CheckExist:
                        cout<<"Di quale elemento si desidera verificare l'esistenza? ";
                        cin>>test;
                        cout<<endl<<"Il valore "<<test<<(testV.Exists(test)? init : " non")<<" esiste!";
                        cout<<endl;
                        cout<<endl;
                        break;
                    case Operazione::ProprietaryFoldFun:
                        cout<<"Qual'è il valore di n? ";
                        cin>>n;
                        res = init;
                        testV.Fold(AppendIfLessThanN,&n,&res);
                        cout<<"Il risultato è: "<<res<<"!"<<endl;
                        cout<<endl;
                        break;
                    case Operazione::ProprietaryMapFun:
                        cout<<"Applico uppercase a tutti gli elementi..."<<endl;
                        testV.Map(Uppercase, nullptr);
                        cout<<"Fatto!"<<endl;
                        cout<<endl;
                        break;
                    case Operazione::LibFunct:
                        cout<<"Quale deve essere la nuova dimensione del Vettore?"<<endl;
                        cin>>input;
                        oldSiz = testV.Size();
                        testV.Resize(input);
                        if (oldSiz<testV.Size()) 
                            for (ulong i = oldSiz; i<testV.Size();i++ )
                            {
                                testV[i] = init + CHARACTERS[distC(gen)];
                                dimatt = 1;
                                while(dimatt<10 && randomstop(gen)!=1)
                                {
                                    testV[i] = testV[i] + CHARACTERS[distC(gen)];
                                    dimatt++;
                                }
                            } 
                        break;
                    case Operazione::End:
                        cout<<"Fine test su Vettore!"<<endl;
                        cout<<endl;
                        break;
                    default:
                        cout<<"Operazione non valida, riprovare"<<endl;    
                        cout<<endl;        
                }
            }       
        }    
    }
    else if(st == Struttura::Lista)
    {
        if(tp == Tipo::Int)
        {
            Operazione op = Operazione::Invalid;
            lasd::List<int> testL;
            int input;
            int n;
            int res = 0;
            int test;
            for (int i = 0; i<dim ;i++ )
            {
                testL.InsertAtBack(dist(gen));
            } 

            while(op != Operazione::End)
            {  
                op = Operazione::Invalid;
                cout<<"Scegliere l'operazione che si desidera effettuare:"<<endl<<"1. Visualizzare il primo elemento"<<endl<<"2. Visualizzare l'ultimo elemento"<<endl<<"3. Visualizzare tutti gli elementi"<<endl<<"4. Controllare l'esistenza di un valore arbitrario"<<endl<<"5. Sommare tutti i valori minori di un n arbitrario"<<endl<<"6. Raddoppiare tutti gli elementi"<<endl<<"7. Inserire un elemento in coda/testa"<<endl<<"0. Fine test"<<endl;                  
                cin>>input;
                if(input == 1) op = Operazione::Front;
                if(input == 2) op = Operazione::Back;
                if(input == 3) op = Operazione::FullContainer;
                if(input == 4) op = Operazione::CheckExist;
                if(input == 5) op = Operazione::ProprietaryFoldFun;
                if(input == 6) op = Operazione::ProprietaryMapFun;
                if(input == 7) op = Operazione::LibFunct;
                if(input == 0) op = Operazione::End;

                switch (op)
                {
                case Operazione::Front:
                    cout<<"Il primo elemento è: "<<testL.Front()<<endl;
                    cout<<endl;
                    break;
                case Operazione::Back:
                    cout<<"L'ultimo elemento è: "<<testL.Back()<<endl;
                    cout<<endl;
                    break;
                case Operazione::FullContainer:
                    cout<<"Stampo tutti gli elementi..."<<endl;
                    testL.Map(VisualizeContainer<int> , nullptr);
                    cout<<endl<<endl;
                    break;
                case Operazione::CheckExist:
                    cout<<"Di quale elemento si desidera verificare l'esistenza? ";
                    cin>>test;
                    cout<<endl<<"Il valore "<<test<<(testL.Exists(test)? init : " non")<<" esiste!";
                    cout<<endl;
                    break;
                case Operazione::ProprietaryFoldFun:
                    cout<<"Qual'è il valore di n? ";
                    cin>>n;
                    res = 0;
                    testL.Fold(SumIfLessThanN,&n,&res);
                    cout<<"Il risultato è: "<<res<<"!"<<endl;
                    cout<<endl;
                    break;
                case Operazione::ProprietaryMapFun:
                    cout<<"Raddoppio tutti gli elementi..."<<endl;
                    testL.Map(DoubleThemUp, nullptr);
                    cout<<"Fatto!"<<endl;
                    break;
                case Operazione::LibFunct:
                    cout<<"1. Inserimento in testa;\n2. Inserimento in coda;\n";
                    cin>>input;
                    cout<<"Quale valore deve essere inserito? ";
                    cin>>test;
                    cout<<"Inserisco "<<test<<" in "<<(input==1 ? "testa" : "coda")<<"!"<<endl;
                    if(input == 1) testL.InsertAtFront(test);
                    if(input == 2) testL.InsertAtBack(test);
                    break;
                case Operazione::End:
                        cout<<"Fine test su Lista!"<<endl;
                    break;
                default:
                    cout<<"Operazione non valida, riprovare"<<endl;            
                }
            }
        }
        else if(tp == Tipo::Double)
        {
            Operazione op = Operazione::Invalid;
            lasd::List<double> testL;
            int input;
            double n;
            double res = 1;
            double test;
        

            for (int i = 0; i<dim;i++ )
            {
                testL.InsertAtBack((double) (trunc((double) ((double) distAndNeg(gen)/(double)(distUnder(gen)) * 100))/100));

            } 

            while(op != Operazione::End)
            {  
                op = Operazione::Invalid;
                cout<<"Scegliere l'operazione che si desidera effettuare:"<<endl<<"1. Visualizzare il primo elemento"<<endl<<"2. Visualizzare l'ultimo elemento"<<endl<<"3. Visualizzare tutti gli elementi"<<endl<<"4. Controllare l'esistenza di un valore arbitrario"<<endl<<"5. Prodotto di tutti i valori maggiori di un n arbitrario"<<endl<<"6. Elevare tutti gli elementi alla seconda"<<endl<<"0. Fine test"<<endl;                  
                cin>>input;
                if(input == 1) op = Operazione::Front;
                if(input == 2) op = Operazione::Back;
                if(input == 3) op = Operazione::FullContainer;
                if(input == 4) op = Operazione::CheckExist;
                if(input == 5) op = Operazione::ProprietaryFoldFun;
                if(input == 6) op = Operazione::ProprietaryMapFun;
                if(input == 7) op = Operazione::LibFunct;
                if(input == 0) op = Operazione::End;
                switch (op)
                {
                    case Operazione::Front:
                        cout<<"Il primo elemento è: "<<testL.Front()<<endl;
                        cout<<endl;
                        break;
                    case Operazione::Back:
                        cout<<"L'ultimo elemento è: "<<testL.Back()<<endl;
                        cout<<endl;
                        break;
                    case Operazione::FullContainer:
                        cout<<"Stampo tutti gli elementi..."<<endl;
                        cout<<endl;
                        testL.Map(VisualizeContainer<double> , nullptr);
                        cout<<endl<<endl;
                        break;
                    case Operazione::CheckExist:
                        cout<<"Di quale elemento si desidera verificare l'esistenza? ";
                        cin>>test;
                        cout<<endl<<"Il valore "<<test<<(testL.Exists(test)? init : " non")<<" esiste!";
                        cout<<endl;
                        cout<<endl;
                        break;
                    case Operazione::ProprietaryFoldFun:
                        cout<<"Qual'è il valore di n? ";
                        cin>>n;
                        res = 1;
                        testL.Fold(MultiplyIfHigherThanN,&n,&res);
                        cout<<"Il risultato è: "<<res<<"!"<<endl;
                        cout<<endl;
                        break;
                    case Operazione::ProprietaryMapFun:
                        cout<<"Applico la potenza di 2 a tutti gli elementi..."<<endl;
                        testL.Map(MultiplyByItself, nullptr);
                        cout<<"Fatto!"<<endl;
                        cout<<endl;
                        break;
                    case Operazione::LibFunct:
                        cout<<"1. Inserimento in testa;\n2. Inserimento in coda;\n";
                        cin>>input;
                        cout<<"Quale valore deve essere inserito? ";
                        cin>>test;
                        cout<<"Inserisco "<<test<<" in "<<(input==1 ? "testa" : "coda")<<"!"<<endl;
                        if(input == 1) testL.InsertAtFront(test);
                        if(input == 2) testL.InsertAtBack(test);
                        break;
                    case Operazione::End:
                        cout<<"Fine test su Lista!"<<endl;
                        cout<<endl;
                        break;
                    default:
                        cout<<"Operazione non valida, riprovare"<<endl;    
                        cout<<endl;        
                    }
            }       
        }
        else if(tp == Tipo::String)
        {
            Operazione op = Operazione::Invalid;
            lasd::List<string> testL;
            int input;
            int n;
            string res = init;
            string test;
            int dimatt;
            int rs;

            for (int i = 0; i<dim;i++ )
            {
                string a = init;
                a+= CHARACTERS[distC(gen)];
                dimatt = 1;
                while(dimatt<10 && randomstop(gen)!=1)
                {
                    a += CHARACTERS[distC(gen)];
                    dimatt++;
                }
                testL.InsertAtBack(a);
                i++;
            } 

            while(op != Operazione::End)
            {  
                op = Operazione::Invalid;
                cout<<"Scegliere l'operazione che si desidera effettuare:"<<endl<<"1. Visualizzare il primo elemento"<<endl<<"2. Visualizzare l'ultimo elemento"<<endl<<"3. Visualizzare tutti gli elementi"<<endl<<"4. Controllare l'esistenza di un valore arbitrario"<<endl<<"5. Concatenare tutte le stringhe di lunghezza minore od uguale ad un n arbitrario"<<endl<<"6. Uppercase a tutti i caratteri delle stringhe"<<endl<<"0. Fine test"<<endl;                  
                cin>>input;
                if(input == 1) op = Operazione::Front;
                if(input == 2) op = Operazione::Back;
                if(input == 3) op = Operazione::FullContainer;
                if(input == 4) op = Operazione::CheckExist;
                if(input == 5) op = Operazione::ProprietaryFoldFun;
                if(input == 6) op = Operazione::ProprietaryMapFun;
                if(input == 7) op = Operazione::LibFunct;
                if(input == 0) op = Operazione::End;
                switch (op)
                {
                    case Operazione::Front:
                        cout<<"Il primo elemento è: "<<testL.Front()<<endl;
                        cout<<endl;
                        break;
                    case Operazione::Back:
                        cout<<"L'ultimo elemento è: "<<testL.Back()<<endl;
                        cout<<endl;
                        break;
                    case Operazione::FullContainer:
                        cout<<"Stampo tutti gli elementi..."<<endl;
                        cout<<endl;
                        testL.Map(VisualizeContainer<string> , nullptr);
                        cout<<endl;                        
                        break;
                    case Operazione::CheckExist:
                        cout<<"Di quale elemento si desidera verificare l'esistenza? ";
                        cin>>test;
                        cout<<endl<<"Il valore "<<test<<(testL.Exists(test)? init : " non")<<" esiste!";
                        cout<<endl;
                        cout<<endl;
                        break;
                    case Operazione::ProprietaryFoldFun:
                        cout<<"Qual'è il valore di n? ";
                        cin>>n;
                        res = init;
                        testL.Fold(AppendIfLessThanN,&n,&res);
                        cout<<"Il risultato è: "<<res<<"!"<<endl;
                        cout<<endl;
                        break;
                    case Operazione::ProprietaryMapFun:
                        cout<<"Applico uppercase a tutti gli elementi..."<<endl;
                        testL.Map(Uppercase, nullptr);
                        cout<<"Fatto!"<<endl;
                        cout<<endl;
                        break;
                    case Operazione::LibFunct:
                        cout<<"1. Inserimento in testa;\n2. Inserimento in coda;\n";
                        cin>>input;
                        cout<<"Quale valore deve essere inserito? ";
                        cin>>test;
                        cout<<"Inserisco "<<test<<" in "<<(input==1 ? "testa" : "coda")<<"!"<<endl;
                        if(input == 1) testL.InsertAtFront(test);
                        if(input == 2) testL.InsertAtBack(test);
                        break;
                    case Operazione::End:
                        cout<<"Fine test su Lista!"<<endl;
                        cout<<endl;
                        break;
                    default:
                        cout<<"Operazione non valida, riprovare"<<endl;    
                        cout<<endl;        
                }
            }       
        }
    }
    else if(st == Struttura::Stack)
    {
        int input;
        cout<<"Quale implementazione si desidera utilizzare?\n1. Vettore;\n 2. Lista.\n";
        cin>>input;
        if(input == 1) TestStackVec(tp, dim);
        else TestStackLst(tp,dim);
    }
    else if(st == Struttura::Queue)
    {
        int input;
        cout<<"Quale implementazione si desidera utilizzare? \n1. Vettore;\n 2. Lista.\n";
        cin>>input;
        if(input == 1) TestQueueVec(tp, dim);
        else TestQueueLst(tp,dim);
    }
    else if(st == Struttura::BT)
    {
        int input;
        cout<<"Quale implementazione si desidera utilizzare? \n1. Vettore;\n2. Lista.\n";
        cin>>input;
        if(input == 1) TestBTVec(tp, dim);
        else TestBTLnk(tp,dim);
    }
    else if(st == Struttura::BST)
    {
        int input;
        TestBST(tp,dim);
    }
    else if(st == Struttura::Hashtable)
    {
      int iput;
      cout<<"Quale implementazione?\n1. Open addressing\n2. Closed addressing\n";
      cin>>iput;

      if(iput ==1) TestHTO(tp, dim);
      else TestHTC(tp,dim);
    }
}    

void mytest()
{
        Struttura scelta1 = Struttura::Invalid;
        while(scelta1 != Struttura::Exit)
        {
            scelta1 = Struttura::Invalid;
            int input;
            cout<<"Scegliere il tipo di struttura che si desidera testare"<<endl<<"1. Vettore"<<endl<<"2. Lista"<<endl<<"3. Stack"<<endl<<"4. Coda"<<endl<<"5. Albero binario"<<endl<<"6. Albero binario di ricerca"<<endl<<"7. Hashtable"<<endl<<"0. Uscita dal test personale (questo avvierà il test del professore)"<<endl;
            cin>>input;
            cout<<endl;
            if(input==1) scelta1 = Struttura::Vettore;
            if(input==2) scelta1 = Struttura::Lista;
            if(input==3) scelta1 = Struttura::Stack;
            if(input==4) scelta1 = Struttura::Queue;
            if(input==5) scelta1 = Struttura::BT;
            if(input==6) scelta1 = Struttura::BST;
            if(input==7) scelta1 = Struttura::Hashtable;
            if(input==0) scelta1 = Struttura::Exit;
            if(scelta1 != Struttura::Invalid && scelta1!= Struttura::Exit)
            {
                Tipo scelta2 = Tipo::Invalid;

                while(scelta2 != Tipo::Exit)
                    {
                        scelta2 = Tipo::Invalid;
                        int input;
                        cout<<"Scegliere il tipo di dato"<<endl<<"1. Integer"<<endl<<"2. Double"<<endl<<"3. String"<<endl<<"0. Tornare alla selezione della struttura"<<endl;
                        cin>>input;
                        cout<<endl;
                        if(input==1) scelta2 = Tipo::Int;
                        if(input==2) scelta2 = Tipo::Double;
                        if(input==3) scelta2 = Tipo::String;
                        if(input==0) scelta2 = Tipo::Exit;
                        if (scelta2 == Tipo::Exit)
                        {

                        }
                        else if (scelta2 == Tipo::Int || scelta2 == Tipo::String || scelta2 == Tipo::Double)
                        {
                            Test(scelta1, scelta2);
                            scelta2 = Tipo::Exit;
                        }
                        else
                            cout<<"Valore non valido, riprovare"<<endl;
                            
                    }
            }
            else if (scelta1 == Struttura::Exit){}  
            else
            {
                cout<<"Valore non valido, riprovare"<<endl;
            }              
        }
}
