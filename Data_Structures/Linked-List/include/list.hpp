#ifndef LIST_
#define LIST_


#include<iostream>
#include <initializer_list>
#include <iterator>

namespace sc{


    template < typename T >
    class list{
        // Aliases
        using value_type = T; // Tipo representando o valor guardado na lsita
        using size_type = size_t; // Tipo representando a medida de tamanho
        using reference = T&; // Tipo representando referencia para tipo guardado
        using const_reference = const T&; // Tipo representando referencia constante para tipo guardado

        struct Node{
            // O que Node ira guardar
            value_type _info;

            // Enderecos do node anterior e seguinte
            Node * _prev, * _next;

            /*!
            \brief Construtor padrao de Node
            Caso nao seja passado parametro inicializa um noh com nullptr,
            info é inicializada com o valor padrão
            */
            Node( T info = T(), Node * previous = nullptr, Node * next = nullptr);


            /*!
            \brief Destrutor de Node
            Destroi elemento guardado por Node
            */
            ~Node( void );
        };

        // Aliases
        using Nodeptr = Node *; // Tipo representando ponteiro para estrutura Node

        // Nós cabeça e "rabo"
        Nodeptr _hNode, _tNode;

        // Tamanho atual da lista
        size_type _size;

    public:

    class iterator{
        public:
        //declaracao dos aliases usados na construcao da classe
        using size_type = size_t;
        using pointer = T*;
        using reference = T&;
        using difference_type = size_t;
        using Nodeptr = Node *; // Tipo representando ponteiro para estrutura Node

    private:
            //declaracao dos atributos da classe
            Nodeptr _ptr; //ponteiro guardado pelo iterador

            friend class list;
            template<typename Tt>
            friend Nodeptr get_ptr( iterator itr );

        public:
            /*-----------------------CONSTRUTORES-DESTRUTORES-E-ATRIBUICOES-------------------*/

            /*!
            \brief Construtor padrão (iterator)
            É usado quando é passado nenhum parametro ou um ponteiro para data_type

            */
            iterator(Nodeptr ptr = nullptr);

            /*!
            \brief Destrutor (~iterator)
            Invoca destrutor padrao do C++

            */
            ~iterator() = default;

            /*!
            \brief Construtor copia (iterator)
            Copia valor (poteiro interno) de objeto passado por parametro para objeto atual
            \param const iterator& itr : parametro que recebe referencia constante do objeto
            */
            iterator(const iterator& itr);

            /*!
            \brief Operador de copia (operator=)
            Copia valor de objeto passado por parametro para objeto atual

            \param const iterator& rhs : parametro que recebe referencia constante do objeto

            */
            iterator& operator=( const iterator& rhs );
            /*-------------------------------------ACESSO--------------------------------------*/

            /*!
            \brief operator*
            acessa a info do elemento (noh) guardado pelo ponteiro (*)

            \return *_ptr: retorna o valor (referencia) guardada no info ponteiro Nodeptr
            */
            reference operator* ( void ) const;

            /*--------------------------OPERADORES-DECREMENTO/INCREMENTO-----------------------*/


            /*!
            \brief operator++
            Pŕe incremento, não recebe parametros

            \return ++_ptr : retorna elemento ja incrementado
            */
            iterator &operator++(); //pre

            /*!
            \brief operator++
            Pós incremento

            \param int dummy:
            \return _ptr++ : retorna elemento ainda nao incrementado
            */
            iterator operator++( int dummy ); //pos

            /*!
            \brief operator--
            Pŕe decremento, nao recebe parametros

            \return --_ptr : retorna elemento ja decrementado
            */
            iterator &operator--();

            /*!
            \brief operator--
            Pós decremento

            \param  int dummy :
            \return _ptr-- : retorna elemento ainda nao decrementado
            */
            iterator operator--(int dummy);

            /*------------------------------OPEARDORES-BOOLEANOS------------------------------*/

            /*!
            \brief operator==
            checa se dois iteradores sao iguais, ou seja, se apontam para mesma memoria

            \param const iterator& rhs : recebe referencia do iterador
            \return _ptr == rhs._ptr : true
            */
            bool operator==(const iterator& rhs) const;

            /*!
            \brief operator!=
            checa se dois iteradores sao diferentes, ou seja, se apontam para memorias diferentes

            \param const iterator& rhs :recebe referencia do iterador
            \return _ptr != rhs._ptr : true
            */
            bool operator!=(const iterator& rhs) const;


            /*----------------------------OPEARDORES-SOMA-SUBTRACAO-----------------------------*/



            /*!
            \brief  operator+
            Recebe um valor por parametro para somar com a posicao atual e acessar o noh desejado
            \param int val : valor passado por parametro
            \return temp : retorna novo noh atual
            */
            iterator operator+(int val);


            /*!
            \brief  operator-
            Recebe um valor por parametro para subtrair da posicao atual e acessar o noh desejado
            \param int val : valor passado por parametro
            \return temp : retorna novo noh atual
            */

            iterator operator-( int val );

            /*!
            \brief  operator-
            Calcula distancia entre dois iteradores

            \param list<T>::iterator itr : passa iterador como parametro
            \return cont : retorna a distancia
            */

            difference_type operator-( iterator itr );

        };

        class const_iterator{
            public:
            //declaracao dos aliases usados na construcao da classe
            using size_type = size_t;
            using pointer = T*;
            using reference = T&;
            using const_reference = const T&;
            using difference_type = size_t;
            using Nodeptr = Node *; // Tipo representando ponteiro para estrutura Node

        private:
            //declaracao dos atributos da classe
            Nodeptr _ptr; //ponteiro guardado pelo iterador

            friend class list;
            template<typename Tt>
            friend Nodeptr get_ptr( const_iterator itr );

        public:
            /*-----------------------CONSTRUTORES-DESTRUTORES-E-ATRIBUICOES-------------------*/

            /*!
            \brief Construtor padrão (iterator)
            É usado quando é passado nenhum parametro ou um ponteiro para data_type

            */
            const_iterator(Nodeptr ptr = nullptr);

            /*!
            \brief Destrutor (~iterator)
            Invoca destrutor padrao do C++

            */
            ~const_iterator() = default;

            /*!
            \brief Construtor copia (iterator)
            Copia valor (poteiro interno) de objeto passado por parametro para objeto atual
            \param const iterator& itr : parametro que recebe referencia constante do objeto
            */
            const_iterator(const const_iterator& itr);

            /*!
            \brief Operador de copia (operator=)
            Copia valor de objeto passado por parametro para objeto atual

            \param const iterator& rhs : parametro que recebe referencia constante do objeto

            */
            const_iterator& operator=( const const_iterator& rhs );
            /*-------------------------------------ACESSO--------------------------------------*/

            /*!
            \brief operator*
            acessa a info do elemento (noh) guardado pelo ponteiro (*)

            \return *_ptr: retorna o valor (referencia) guardada no info ponteiro Nodeptr
            */
            const_reference operator* ( void ) const;

            /*--------------------------OPERADORES-DECREMENTO/INCREMENTO-----------------------*/


            /*!
            \brief operator++
            Pŕe incremento, não recebe parametros

            \return ++_ptr : retorna elemento ja incrementado
            */
            const_iterator & operator++(); //pre

            /*!
            \brief operator++
            Pós incremento

            \param int dummy:
            \return _ptr++ : retorna elemento ainda nao incrementado
            */
            const_iterator operator++( int dummy ); //pos

            /*!
            \brief operator--
            Pŕe decremento, nao recebe parametros

            \return --_ptr : retorna elemento ja decrementado
            */
            const_iterator &operator--();

            /*!
            \brief operator--
            Pós decremento

            \param  int dummy :
            \return _ptr-- : retorna elemento ainda nao decrementado
            */
            const_iterator operator--(int dummy);

            /*------------------------------OPEARDORES-BOOLEANOS------------------------------*/

            /*!
            \brief operator==
            checa se dois iteradores sao iguais, ou seja, se apontam para mesma memoria

            \param const iterator& rhs : recebe referencia do iterador
            \return _ptr == rhs._ptr : true
            */
            bool operator==(const const_iterator& rhs) const;

            /*!
            \brief operator!=
            checa se dois iteradores sao diferentes, ou seja, se apontam para memorias diferentes

            \param const iterator& rhs :recebe referencia do iterador
            \return _ptr != rhs._ptr : true
            */
            bool operator!=(const const_iterator& rhs) const;


            /*----------------------------OPEARDORES-SOMA-SUBTRACAO-----------------------------*/



            /*!
            \brief  operator+
            Recebe um valor por parametro para somar com a posicao atual e acessar o noh desejado
            \param int val : valor passado por parametro
            \return temp : retorna novo noh atual
            */
            const_iterator operator+(int val);


            /*!
            \brief  operator-
            Recebe um valor por parametro para subtrair da posicao atual e acessar o noh desejado
            \param int val : valor passado por parametro
            \return temp : retorna novo noh atual
            */

            const_iterator operator-(int val);


            /*!
            \brief  operator-
            Calcula distancia entre dois iteradores

            \param list<T>::iterator itr : passa iterador como parametro
            \return cont : retorna a distancia
            */

            difference_type operator-( const_iterator itr );
        };

        /*------------------------------------SPECIAL-MEMBERS-------------------------------*/


        /*!
        \brief Construtor padrao da lista
        Cria uma lista vazia
        */
        list( );

        /*!
        \brief Construtor size
        Cria uma nova lista com valores padrao ( value_type() ) de tamanho n
        (passado por parametro)

        \param typename list<T>::size_type n  : parametro que representa o tamanho da lista
        */
        list( size_type n );


        /*!
        \brief Copy construtor
        Copia os atributos do objeto passado por parametro para o objeto atual
        \param const list<T> &obj : objeto passado por parametro
        */
        list( const list &obj );


        /*!
        \brief initializer_list constructor
        Copiando os elementos da lista passada para a lista atual

        \param const std::initializer_list<T> & il : lista passada por parametro
        */
        list(const std::initializer_list<T> & il);


        /*!
        \brief Range constructor
        Criando lista com os elementos do intervalo passado por parametro
        \param IT first : passando começo da range
        \param IT last : passando final da range
        */
        template<typename IT>
        list(IT first, IT last);


        /*!
        \brief Destrutor
        Destroi a lista
        */
        ~list();

        /*------------------------------------ASSIGNMENT------------------------------------*/


        /*!
        \brief Operador de copia
        Copia os elementos do objeto passadopor parametro para o objeto atual
        \param const list<T>& rhs : objeto passado por referencia
        */
        list& operator=( const list<T>& rhs );


        /*!
        \brief Operador de copia (initializer_list)
        Copia os elementos da initializer_list passada por parametro para o objeto atual
        \param std::initializer_list<value_type> &il : initializer_list passada por parametro
        */
        list& operator=( std::initializer_list<value_type> &il );

        /*------------------------------------GET-ITERATORS---------------------------------*/



        /*!
        \brief Funcao begin
        Funcao que retorna iterator apontando para inicio da lista

        \return iterator( _hNode->_next ) :iterador apontando para o inicio
        */
        // Funcao para retornar iterator apontando para inicio da lista
        iterator begin( void ) const;

        /*!
        \brief Funcao end
        Funcao que retorna iterator apontando para final da lista
        \return iterator( _tNode->prev ) : iterador apontando para o final
        */
        // Funcao para retornar iterator apontando para final da lista
        iterator end( void ) const;

        /*!
        \brief Funcao cbegin
        Funcao que retorna const_iterator apontando para inicio da lista


        \return iterator( _hNode->_next ) : iterador apontando para o inicio
        */
        // Funcao para retornar const_iterator apontando para inicio da lista
        const_iterator cbegin( void ) const;

        /*!
        \brief Funcao cend
        Funcao que retorna const_iterator apontando para final da lista
        \return iterator( _tNode->prev ) : iterador apontando para o final
        */
        // Funcao para retornar const_iterator apontando para final da lista
        const_iterator cend( void ) const;

        /*------------------------------------COMMON-OPERATIONS-----------------------------*/


        /*!
        \brief Funcao empty
        Funcao que indica se a lista esta vazia
        \return bool : retorna verdadeiro caso o tamanho da lista seja 0
        */
        // Funcao que indica se a lista esta vazia
        bool empty( void ) const;

        /*!
        \brief Funcao size
        Funcao para indicar tamanho atual da lista
        \return _size : retorna o tamanho
        */
        // Funcao para indicar tamanho atual da lista
        size_type size( void ) const;

        /*!
        \brief Funcao clear
        Metodo para excluir lista
        */
        // Metodo para excluir lista
        void clear( void );


        /*!
        \brief Funcao front
        Funcao para retornar referencia constante do primeiro elemento da lista

        \return operator[]( 0 ) : retornando referencia do primeiro elemento
        */
        // Funcao para retornar referencia constante do primeiro elemento da lista
        const_reference front( void ) const;


        /*!
        \brief Funcao back
        Funcao para retornar referencia constante do ultimo elemento da lista
        \return operator[]( size() - 1 ) : retornando referencia do ultimo elemento
        */
        // Funcao para retornar referencia constante do ultimo elemento da lista
        const_reference back( void ) const;

        /*!
        \brief Funcao push_front
        Metodo para adicionar um elemento (noh) no inicio da lista

        \param const_reference e : elemento passado por parametro
        */
        // Metodo para adicionar um elemento (no) no inicio da lista
        void push_front( const_reference e );

        /*!
        \brief Funcao push_back
        Metodo para adicionar um elemento (noh) no final da lista

        \param const_reference e : elemento passado por parametro
        */
        // Metodo para adicionar um elemento (no) no final da lista
        void push_back( const_reference e );


        /*!
        \brief Funcao pop_front
        Metodo para remover um elemento do inicio da lista
        */
        // Metodo para remover um elemento do inicio da lista
        void pop_front( void );


        /*!
        \brief Funcao pop_back
        Metodo para remover um elemento do final da lista
        */
        // Metodo para remover um elemento do final da lista
        void pop_back( void );


        /*!
        \brief Funcao assign
        Metodo para atualizar todos valores dos nos para value
        \param const T& value : valor passado por parametro
        */
        // Metodo para atualizar todos valores dos nos para value
        void assign(const T& value );


        /*!
        \brief Funcao assign
        Metodo para atribuir elementos de [first,last) a lista (substituir os valores da lista)
        \param InItr first : passando começo do intervalo
        \param InItr last : passando fim do intervalo
        */
        // Metodo para atribuir elementos de [first,last) a lista
        template < typename InItr >
        void assign( InItr first, InItr last );


        /*!
        \brief Funcao assign
        Metodo para atribuir elementos de uma initializer_list a lista
        \param std::initializer_list<T> ilist : initializer_list passada por parametro
        */
        // Metodo para atribuir elementos de uma initializer_list a lista
        void assign( std::initializer_list<T> ilist );


        /*------------------------------------OPERATORS-OVERLOADING-------------------------*/


        /*!
        \brief Funcao operator[]
        Sobrecarga de operador[]: Acessar n-esimo elemento
        \param typename list<T>::size_type n : posicao do elemento
        \return curr->_info : retorna a referencia pro n-esimo elemento
        */
        // Sobrecarga de operador[]: Acessar n-esimo elemento
        reference operator[]( size_type n);
        /*!
        \brief Funcao const operator[]
        Sobrecarga de operador[]: Acessar n-esimo elemento
        \param typename list<T>::size_type n : posicao do elemento
        \return curr->_info : retorna a referencia pro n-esimo elemento
        */

        // Sobrecarga de operador[]: Acessar n-esimo elemento
        const_reference operator[]( size_type n) const;


        /*!
        \brief Funcao operator==
        Sobrecarga de operador==: Ver se listas sao iguais
        \param const list<T> &rhs : objeto passado por parametro
        \return bool : retorna true se os objetos forem iguais, false caso contrario
        */
        // Sobrecarga de operador==: Ver se listas sao iguais
        bool operator==( const list &rhs);

        /*!
        \brief Funcao operator!=
        Sobrecarga de operador==: Ver se listas sao diferentes
        \param const list<T> &rhs : objeto passado por parametro
        \return bool : retorna true se os objetos forem diferentes, false caso contrario
        */
        // Sobrecarga de operador==: Ver se listas sao diferentes
        bool operator!=( const list &rhs);

        /*------------------------------------ITERATORS-FUNCS-------------------------------*/


        /*!
        \brief Funcao insert
        Funcao para inserir nó com valor element logo antes de itr. Retorna
        iterador para elemento inserido
        \param typename list<T>::iterator itr : recebe iterator
        \param typename list<T>::const_reference element : recebe elemento
        \return iterator( temp ) : Retornando iterador para elemento inserido
        */
        // Funcao para inserir nó com valor element logo antes de itr. Retorna
        // iterador para elemento inserido
        iterator insert(iterator itr, const_reference element);


        /*!
        \brief Funcao insert (const)
        Funcao para inserir nó com valor element logo antes de itr. Retorna
        const_iterador para elemento inserido
        \param typename list<T>::iterator itr : recebe iterador
        \param typename list<T>::const_reference element : recebe elemento
        \return const_iterator( temp ) : Retornando iterador para elemento inserido
        */
        // Funcao para inserir nó com valor element logo antes de itr.
        // Retorna const_iterator para elemento inserido
        const_iterator insert(const_iterator itr, const_reference element);



        /*!
        \brief Funcao insert
        Funcao para inserir Range definida por [first,last) logo antes de itr.
        Retorna iterator para primeiro nó do intervalo criado
        \param typename list<T>::iterator itr : recebe iterador
        \param IT first : recebe começo do intervalo
        \param IT last : recebe final do intervalo
        \return iterator( first_node_from_temp_list ) : Retornando iterator formado pelo primeiro noh do intervalo inserido
        */
        // Funcao para inserir Range definida por [first,last) logo antes de itr.
        // Retorna iterator para primeiro nó do intervalo criado
        template <typename IT>
        iterator insert(iterator itr, IT first, IT last);



        /*!
        \brief Funcao insert
        Funcao para inserir Range definida por [first,last) logo antes de itr.
        Retorna const_iterator para primeiro nó do intervalo criado
        \param const_iterator itr : recebe iterador
        \param IT first : recebe começo do intervalo
        \param IT last : recebe final do intervalo
        \return iterator( first_node_from_temp_list ) : Retornando iterator formado pelo primeiro noh do intervalo inserido
        */
        // Funcao para inserir Range definida por [first,last) logo antes de itr.
        // Retorna const_iterator para primeiro nó do intervalo criado
        template <typename IT>
        const_iterator insert(const_iterator itr, IT first, IT last);


        /*!
        \brief Funcao insert
        Funcao para inserir initializer_list il logo antes de itr.
        \param typename list<T>::iterator itr : recebe iterador
        \param const std::initializer_list<value_type> &il : recebe initializer_list
        \return insert( itr, il.begin(), il.end() ) : Retorna iterator para primeiro nó da lista inserida criado
        */
        // Funcao para inserir initializer_list il logo antes de itr.
        // Retorna iterator para primeiro nó da lista inserida criado
        iterator insert(iterator itr, const std::initializer_list<value_type> &il);



        /*!
        \brief Funcao insert
        Funcao para inserir initializer_list il logo antes de itr.
        \param typename list<T>::const_iterator itr : recebe iterador
        \param const std::initializer_list<value_type> &il : recebe initializer_list
        \return insert( itr, il.begin(), il.end() ) : Retorna const_iterator para primeiro nó da lista inserida criado
        */
        // Funcao para inserir initializer_list il logo antes de itr.
        // Retorna const_iterator para primeiro nó da lista inserida criado
        const_iterator insert(const_iterator itr, const std::initializer_list<value_type> &il);


        /*!
        \brief Funcao erase
        Funcao para remover nó em itr
        \param iterator itr : recebendo iterador
        \return erase( itr, itr + 1) : Retorna iterator para primeiro nó da lista logo após o nó apagado
        */
        // Funcao para remover nó em itr.
        // Retorna iterator para primeiro nó da lista logo após o nó apagado
        iterator erase(iterator itr);

        /*!
        \brief Funcao erase
        Funcao para remover nó em itr
        \param const_iterator itr : recebendo iterador
        \return erase( itr, itr + 1) : Retorna iterator para primeiro nó da lista logo após o nó apagado
        */
        // Funcao para remover nó em itr.
        // Retorna const_iterator para primeiro nó da lista logo após o nó apagado
        const_iterator erase(const_iterator itr);

        /*!
        \brief Funcao erase
        Funcao para remover intervalo em itr
        \param typename list<T>::iterator first: passando começo do intervalo
        \param typename list<T>::iterator last : passando final do intervalo
        \return iterador( get_ptr( last ) ):Retorna iterator para primeiro nó da lista logo após o intervalo excluido
        */
        // Funcao para remover intervalo em itr.
        // Retorna iterator para primeiro nó da lista logo após o intervalo
        iterator erase(iterator first, iterator last);



        /*!
        \brief Funcao erase
        Funcao para remover intervalo em itr
        \param typename list<T>::const_iterator first: passando começo do intervalo
        \param typename list<T>::const_iterator last : passando final do intervalo
        \return const_iterador( get_ptr( last ) ):Retorna iterator para primeiro nó da lista logo após o intervalo excluido
        */
        // Funcao para remover intervalo em itr.
        // Retorna const_iterator para primeiro nó da lista logo após o intervalo
        const_iterator erase(const_iterator first, const_iterator last);

        /*!
        \brief Funcao find
        Funcao para achar primeiro nó com valor igual a value
        \param  const T & value : recebe valor para ser procurado
        \return iterator( curr ) : Retorna iterador para primeiro nó achado com valor value
        */
        // Funcao para achar primeiro nó com valor igual a value
        // Retorna iterador para primeiro nó achado com valor value
        iterator find( const T & value );


        /*!
        \brief Funcao find
        Funcao para achar primeiro nó com valor igual a value
        \param  const T & value : recebe valor para ser procurado
        \return const_iterator( curr ) : Retorna iterador para primeiro nó achado com valor value
        */
        // Funcao para achar primeiro nó com valor igual a value
        // Retorna const_iterator para primeiro nó achado com valor value
        const_iterator find( const T & value ) const;



        /*!
        \brief Funcao get_ptr
        Recupera o nó guardado pelo iterator itr
        \param typename list<T>::iterator itr : recebe iterator
        \return itr._ptr : retorna nó
        */
        Nodeptr get_ptr( iterator itr );


        /*!
        \brief Funcao get_ptr
        Recupera o nó guardado pelo const_iterator itr
        \param typename list<T>::const_iterator itr : recebe iterator
        \return itr._ptr : retorna nó
        */
        Nodeptr get_ptr( const_iterator itr );
    };
}

template < typename T >
std::ostream& operator<< (std::ostream& os, const sc::list<T>& l);

#include "list.inl"

#endif
