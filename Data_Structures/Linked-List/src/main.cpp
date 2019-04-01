#include<initializer_list>
#include<vector>

#include "list.hpp"

int main(){
    /*-----------------------------TESTANDO-CONSTRUTORES-----------------------*/
    std::cout << "------------------------------------------------------------------------\n";

    std::vector<int> v({1,2,3,4,5});

    sc::list<int> lista_padrao;
    sc::list<int> lista_size(5);
    sc::list<int> lista_copy( lista_size );
    sc::list<int> lista_initlist( {2,5,1,2,3} );
    sc::list<int> lista_range( v.begin() + 1, v.end() - 1 );

    std::cout << "\nConstrutor Padrao:\n";
    std::cout << lista_padrao.size() << ": ";
    std::cout << lista_padrao;
    std::cout << "\nConstrutor Size:\n";
    std::cout << lista_size.size() << ": ";
    std::cout << lista_size;
    std::cout << "\nConstrutor Copy:\n";
    std::cout << lista_copy.size() << ": ";
    std::cout << lista_copy;
    std::cout << "\nConstrutor InitList:\n";
    std::cout << lista_initlist.size() << ": ";
    std::cout << lista_initlist;
    std::cout << "\nConstrutor Range:\n";
    std::cout << lista_range.size() << ": ";
    std::cout << lista_range;

    /*-----------------------------TESTANDO-OPERADORES=-----------------------*/
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "\n\n\n";

    lista_padrao = lista_initlist;
    std::cout << "\nOperador de copia (lista_padrao = lista_initlist):\n";
    std::cout << lista_padrao.size() << ": ";
    std::cout << lista_padrao;

    lista_range = lista_copy;
    std::cout << "\nOperador de copia (lista_range = lista_copy):\n";
    std::cout << lista_range.size() << ": ";
    std::cout << lista_range;

    lista_size = {4,3,2,1};
    std::cout << "\nOperador de copia InitList (lista_range = {4,3,2,1}):\n";
    std::cout << lista_size.size() << ": ";
    std::cout << lista_size;

    /*-----------------------------TESTANDO-(C)BEGIN/(C)END-----------------------*/
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "\n\n";

    std::cout << "\nTestando (c)begin/(c)end" << '\n';
    std::cout << lista_size << "\n";
    std::cout << "\nbegin(), end(), cbegin(), cend(): "<< *lista_size.begin() << " "
    << *lista_size.end() << " " << *lista_size.cbegin() << " " << *lista_size.cend() << std::endl;

    /*-----------------------------TESTANDO-CLEAR-SIZE-EMPTY-----------------------*/
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "\n\n";

    std::cout << "\nTestando clear(), empty() e size():\n";
    std::cout << "\nTamanho atual: " << lista_padrao.size();
    lista_padrao.clear();
    std::cout << "\nTamanho apos clear(): " << lista_padrao.size();
    std::cout << "\nEmpty()? apos clear(): " << lista_padrao.empty() << std::endl;

    /*-----------------------------TESTANDO-FRONT-BACK---------------------*/
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "\n\n";

    std::cout << "Testando front(), back():\n";
    std::cout << lista_size << ", " << lista_size.front() << ", " << lista_size.back() << std::endl;

    /*-----------------------------TESTANDO-PUSHFRONT-PUSHBACK-E-POP----------------*/
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "\n\n";

    std::cout << "Testando push_front(), push_back():\n";
    std::cout << lista_size << std::endl;
    lista_size.push_front( -100 );
    lista_size.push_back( -100 );
    std::cout << lista_size << std::endl;
    std::cout << "Testando pop_front(), pop_back():\n";
    lista_size.pop_front();
    lista_size.pop_back();
    std::cout << lista_size << std::endl;

    /*-----------------------------TESTANDO-ASSIGN------------------------------*/
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "\n\n";

    std::cout << "Testando assign (valor):\n";
    std::cout << lista_size << std::endl;
    lista_size.assign( -1);
    std::cout << lista_size << std::endl;

    std::cout << "\nTestando assign :\n";
    std::cout << lista_size << std::endl;
    lista_size.assign( lista_initlist.begin() + 1, lista_initlist.end());
    std::cout << lista_size << std::endl;

    std::cout << "\nTestando assign ({3,4,5,2,1}):\n";
    std::cout << lista_size << std::endl;
    lista_size.assign( {3,4,5,2,1} );
    std::cout << lista_size << std::endl;

    /*-----------------------------TESTANDO-OPEREADOR[]------------------------------*/
    std::cout << "------------------------------------------------------------------------\n";

    const sc::list<int> lista_const({1,2,3});
    lista_padrao = {1,2,3};

    std::cout << "\nTestando operador[] (const), vamos percorrer a lista {1,2,3}:\n";
    for(size_t i(0u); i < lista_const.size(); ++i){
        std::cout << lista_const[i] << " ";
    }std::cout <<'\n';

    std::cout << "\nTestando operador[], vamos percorrer a lista {1,2,3}:\n";
    for(size_t i(0u); i < lista_padrao.size(); ++i){
        std::cout << lista_padrao[i] << " ";
    }std::cout <<'\n';

    /*-----------------------------TESTANDO-OPEREADOR==------------------------------*/
    std::cout << "------------------------------------------------------------------------\n";

    std::cout << "\nTestando operador ==:\n";
    std::cout << "Listas {1,2,3} e {1,2,3} sao iguais? " << (lista_padrao == lista_const) << std::endl;

    lista_padrao = {3,2,1};
    std::cout << "\nTestando operador !=:\n";
    std::cout << "Listas {1,2,3} e {3,2,1} sao diferentes? " << (lista_padrao != lista_const) << std::endl;

    /*-----------------------------TESTANDO-FIND------------------------------*/
    std::cout << "------------------------------------------------------------------------\n";

    std::cout << "\nTestando find(3) em {3,2,1} e imprime indice do itr achado:\n";
    std::cout << lista_padrao.find(3) - lista_padrao.begin() << std::endl;
    std::cout << "\nTestando find(4) em {3,2,1} e imprime indice do itr achado:\n";
    std::cout << lista_padrao.find(4) - lista_padrao.begin() << std::endl;

    // Insert e erase ja foram testados indiretamente

    /*-----------------------------TESTANDO-CONST_ITERATOR------------------------------*/
    std::cout << "\n\n";
    std::cout << "------------------------------------------------------------------------\n";


    std::cout << "Imprimindo {3,3,3,3,3,4,4,4,4} com const_iterator:\n";
    lista_range = {3,3,3,3,3,4,4,4,4};
    for(auto i(lista_range.cbegin()); i != lista_range.cend(); i++ ){
        i = i + 1;
        i = i - 1;
        std::cout << *i << " ";
    }std::cout << "\n";


}
