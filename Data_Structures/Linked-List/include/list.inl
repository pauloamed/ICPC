#include "list.hpp"

namespace sc {

    // Construtor padrao de Node
    template < typename T >
    list<T>::Node::Node( T info, typename list<T>::Nodeptr previous, typename list<T>::Nodeptr next):
    _info( info ), _prev( previous ), _next( next ){ /*empty*/ }

    // Destrutor de Node
    template < typename T >
    list<T>::Node::~Node( void ){
        // Destruindo elemento guardado por Node
        _info.~T();
    }

    // Construtor padrao do iterator
    template < typename T >
    list<T>::iterator::iterator(typename list<T>::iterator::Nodeptr ptr):_ptr( ptr ){ /**/ }

    // Construtor de copia do iterator
    template < typename T >
    list<T>::iterator::iterator(const iterator& itr):_ptr(itr._ptr){ /**/ }

    // Atribuicao de copia entre iteradores
    template < typename T >
    typename list<T>::iterator& list<T>::iterator::operator=( const iterator& rhs ){
        _ptr = rhs._ptr;
        return *this;
    }

    // Sobrecarga do operador *, para acessar valor de elemento guardao em nó
    template < typename T >
    typename list<T>::reference list<T>::iterator::operator* ( void ) const{
        //retorna o valor (referencia) guardada em _ptr
        return _ptr->_info;
    }

    // Acessar proximo elemento (pre-incremento)
    template < typename T >
    typename list<T>::iterator & list<T>::iterator::operator++( void ){
        _ptr = _ptr->_next;
        return *this;
    }

    // Acessar proximo elemento (pos-incremento)
    template < typename T >
    typename list<T>::iterator list<T>::iterator::operator++( int dummy){
        // Criando variavel temporaria para ser retornada
        auto temp( _ptr );
        _ptr = _ptr->_next;
        return temp;
    }

    // Acessar elemento anterior (pre-incremento)
    template < typename T >
    typename list<T>::iterator & list<T>::iterator::operator--(){
        _ptr = _ptr->_prev;
        return *this;
    }

    // Acessar elemento anterior (pos-incremento)
    template < typename T >
    typename list<T>::iterator list<T>::iterator::operator--(int dummy){
        // Criando variavel temporaria para ser retornada
        auto temp( _ptr );
        _ptr = _ptr->_prev;
        return temp;
    }

    template < typename T >
    bool list<T>::iterator::operator==(const list<T>::iterator& rhs) const{
        // Se forem iguais retornar true
        return _ptr == rhs._ptr;
    }

    template < typename T >
    bool list<T>::iterator::operator!=(const list<T>::iterator& rhs) const{
        // Se forem diferentes retornar true
        return _ptr != rhs._ptr;
    }

    template < typename T >
    typename list<T>::iterator list<T>::iterator::operator+(int val){
        // Subproblema de operator-, caso val seja negativo
        if( val < 0) { return operator-( val * -1);}

        // Acessar o nó desejado, com operacao de iterador
        auto temp( *this );
        while ( (val--) > 0 ){
            temp++;
        }
        return temp;
    }

    template < typename T >
    typename list<T>::iterator list<T>::iterator::operator-(int val){
        // Subproblema de operator+, caso val seja negativo
        if( val < 0) { return operator+( val * -1);}

        // Acessar o nó desejado, com operacao de iterador
        auto temp( *this );
        while ( (val--) > 0 ){
            temp--;
        }
        return temp;
    }

    template < typename T >
    typename list<T>::iterator::difference_type list<T>::iterator::operator-( list<T>::iterator itr ){
        auto cont( 0u );
        while( itr++ != *this){ cont++; }
        return cont;
    }

    // Construtor padrao do iterator
    template < typename T >
    list<T>::const_iterator::const_iterator(typename list<T>::const_iterator::Nodeptr ptr):_ptr( ptr ){ /**/ }

    // Construtor de copia do iterator
    template < typename T >
    list<T>::const_iterator::const_iterator(const const_iterator& itr):_ptr(itr._ptr){ /**/ }

    // Atribuicao de copia entre iteradores
    template < typename T >
    typename list<T>::const_iterator& list<T>::const_iterator::operator=( const const_iterator& rhs ){
        _ptr = rhs._ptr;
        return *this;
    }

    // Sobrecarga do operador *, para acessar valor de elemento guardao em nó
    template < typename T >
    typename list<T>::const_reference list<T>::const_iterator::operator* ( void ) const{
        //retorna o valor (referencia) guardada em _ptr
        return _ptr->_info;
    }

    // Acessar proximo elemento (pre-incremento)
    template < typename T >
    typename list<T>::const_iterator & list<T>::const_iterator::operator++(){
        _ptr = _ptr->_next;
        return *this;
    }

    // Acessar proximo elemento (pos-incremento)
    template < typename T >
    typename list<T>::const_iterator list<T>::const_iterator::operator++( int dummy){
        // Criando variavel temporaria para ser retornada
        auto temp(_ptr);
        _ptr = _ptr->_next;
        return temp;
    }

    // Acessar elemento anterior (pre-incremento)
    template < typename T >
    typename list<T>::const_iterator & list<T>::const_iterator::operator--(){
        _ptr = _ptr->_prev;
        return *this;
    }

    // Acessar elemento anterior (pos-incremento)
    template < typename T >
    typename list<T>::const_iterator list<T>::const_iterator::operator--(int dummy){
        // Criando variavel temporaria para ser retornada
        auto temp(_ptr);
        _ptr = _ptr->_prev;
        return temp;
    }

    template < typename T >
    bool list<T>::const_iterator::operator==(const list<T>::const_iterator& rhs) const{
        // Se forem iguais retornar true
        return _ptr == rhs._ptr;
    }

    template < typename T >
    bool list<T>::const_iterator::operator!=(const list<T>::const_iterator& rhs) const{
        // Se forem diferentes retornar true
        return _ptr != rhs._ptr;
    }

    template < typename T >
    typename list<T>::const_iterator list<T>::const_iterator::operator+(int val){
        // Subproblema de operator-, caso val seja negativo
        if( val < 0) { return operator-( val * -1);}

        // Acessar o nó desejado, com operacao de iterador
        auto temp( *this );
        while ( (val--) > 0 ){
            temp++;
        }
        return temp;
    }

    template < typename T >
    typename list<T>::const_iterator list<T>::const_iterator::operator-(int val){
        // Subproblema de operator+, caso val seja negativo
        if( val < 0) { return operator+( val * -1);}

        // Acessar o nó desejado, com operacao de iterador
        auto temp( *this );
        while ( (val--) > 0 ){
            temp--;
        }
        return temp;
    }

    template < typename T >
    typename list<T>::const_iterator::difference_type list<T>::const_iterator::operator-( list<T>::const_iterator itr ){
        auto cont( 0 );
        while( itr++ != *this){ cont++; }
        return cont;
    }

    // Construtor padrao da lista
    template < typename T >
    list<T>::list( void ):_hNode( new Node() ), _tNode( new Node() ), _size( 0 ){
        // Criando lista vazia
        _hNode->_next = _tNode;
        _tNode->_prev = _hNode;
    }

    // Constructor (size)
    template < typename T >
    list<T>::list( typename list<T>::size_type n ):_hNode( new Node() ), _tNode( new Node() ), _size( n ){
        // Criar nova lista com valores padrao ( value_type() ) de tamanho n (passado por parametro)
        _hNode->_next = _tNode;
        _tNode->_prev = _hNode;

        // Nó atual ( comecando do Head ) vai criar seu posterior, com valor padrao
        typename list<T>::Nodeptr curr( _hNode );
        while( n > 0 ){
            // Criando nó posterior com valor padrao (com info padrao, prev = atual, next = ultimo)
            curr->_next = new Node( typename list<T>::value_type(), curr, _tNode );
            // Atualizando nó atual
            curr = curr->_next;
            // Atualizando valor de n
            n--;
        }

        // Definindo ultimo nó
        _tNode->_prev = curr;
    }

    // Copy constructor
    template < typename T >
    list<T>::list( const list<T> &obj ):_hNode( new Node() ), _tNode( new Node() ), _size( 0 ){
        // Criando lista vazia
        _hNode->_next = _tNode;
        _tNode->_prev = _hNode;
        // Chamar atribuicao de copia para (obj)
        insert( begin(), obj.begin(), obj.end() );
    }

    // initializer_list constructor
    template < typename T >
    list<T>::list(const std::initializer_list<T> & il):_hNode( new Node() ), _tNode( new Node() ), _size( 0 ){
        // Criando lista vazia
        _hNode->_next = _tNode;
        _tNode->_prev = _hNode;

        // Subproblema: insert de intervalo
        insert( begin(), il.begin(), il.end() );
    }

    // Range constructor
    template<typename T>
    template<typename IT>
    list<T>::list(IT first, IT last):_hNode( new Node() ), _tNode( new Node() ), _size( 0 ){
        // Criando lista vazia
        _hNode->_next = _tNode;
        _tNode->_prev = _hNode;

        // Subproblema: insert de intervalo
        insert( begin(), first, last );
    }

    // Destrutor
    template<typename T>
    list<T>::~list( void ){
        // Subproblema de clear()
        clear();

        delete _tNode;
        delete _hNode;
    }

    /*------------------------------------ASSIGNMENT------------------------------------*/

    // Operador de copia
    template<typename T>
    list<T>& list<T>::operator=( const list<T>& rhs ){
        // Subproblema de assign
        assign( rhs.begin() , rhs.end() );

        return *this;
    }

    // Operador de copia (initializer_list)
    template<typename T>
    list<T>& list<T>::operator=( std::initializer_list<T> &il ){
        // Subproblema de assign
        assign( il.begin(), il.end() );

        return *this;
    }

    /*------------------------------------GET-ITERATORS---------------------------------*/

    // Funcao para retornar iterator apontando para inicio da lista
    template<typename T>
    typename list<T>::iterator list<T>::begin( void ) const{
        return typename list<T>::iterator::iterator( _hNode->_next );
    }

    // Funcao para retornar iterator apontando para final da lista
    template<typename T>
    typename list<T>::iterator list<T>::end( void ) const{
        return typename list<T>::iterator::iterator( _tNode );
    }

    // Funcao para retornar const_iterator apontando para inicio da lista
    template<typename T>
    typename list<T>::const_iterator list<T>::cbegin( void ) const {
        return typename list<T>::const_iterator::const_iterator( _hNode->_next );
    }

    // Funcao para retornar const_iterator apontando para final da lista
    template<typename T>
    typename list<T>::const_iterator list<T>::cend( void ) const {
        return typename list<T>::const_iterator::const_iterator( _tNode );
    }

    /*------------------------------------COMMON-OPERATIONS-----------------------------*/

    // Funcao que indica se a lista esta vazia
    template<typename T>
    bool list<T>::empty( void ) const{
        return _size == 0; // Lista estara vazia caso seu tamanho seja 0
    }

    // Funcao para indicar tamanho atual da lista
    template<typename T>
    typename list<T>::size_type list<T>::size( void ) const{
        return _size; // Atributo com essa mesma funcao
    }

    // Metodo para excluir lista
    template<typename T>
    void list<T>::clear( void ){
        // Subproblema de erase
        erase( begin(), end() );
    }

    // Funcao para retornar referencia constante do primeiro elemento da lista
    template<typename T>
    typename list<T>::const_reference list<T>::front( void ) const{
        // Subproblema de []
        return operator[]( 0 );
    }

    // Funcao para retornar referencia constante do ultimo elemento da lista
    template<typename T>
    typename list<T>::const_reference list<T>::back( void ) const{
        // Subproblema de []
        return operator[]( size() - 1 );
    }

    // Metodo para adicionar um elemento (no) no inicio da lista
    template<typename T>
    void list<T>::push_front( typename list<T>::const_reference e ){
        // Subproblema de insert
        insert( begin(), e );
    }

    // Metodo para adicionar um elemento (no) no final da lista
    template<typename T>
    void list<T>::push_back( typename list<T>::const_reference e ){
        // Subproblema de insert
        insert( end(), e );
    }

    // Metodo para remover um elemento do inicio da lista
    template<typename T>
    void list<T>::pop_front( void ){
        // Subproblema de erase
        erase( begin() );
    }

    // Metodo para remover um elemento do final da lista
    template<typename T>
    void list<T>::pop_back( void ){
        // Subproblema de erase
        erase( end() - 1 );
    }

    // Metodo para atualizar todos valores dos nos para value
    template<typename T>
    void list<T>::assign(const T& value ){
        // Criando ponteiro que guarda o primeiro nó
        typename list<T>::Nodeptr curr( _hNode->_next );
        while (curr != _tNode){
            curr->_info = value;
            curr = curr->_next;
        }
    }

    // Metodo para atribuir elementos de [first,last) a lista (substituir os valores da lista)
    template<typename T>
    template < typename InItr >
    void list<T>::assign( InItr first, InItr last ){
        // Calculando tamanho do intervalo cujos valores vao substituir os elementos da lista
        size_type sizeOfInterval = last - first;

        // Caso o tamanho do intervalo seja menor que o tamanho da lista
        // Caso o tamanho da lista seja maior que o tamanho do intervalo
        if( sizeOfInterval < _size){
            // Apagar elementos restantes (erase)
            erase( begin() + sizeOfInterval, end());
        }else if(sizeOfInterval > _size){
            // Usar insert para inserir elementos que nao poderao ser substituidos
            insert( end(), first + _size, last );
        }

        // Substituindo elementos da lista
        typename list<T>::Nodeptr curr( _hNode->_next );
        while( curr != _tNode ){
            curr->_info = *(first++);
            curr = curr->_next;
        }

        // Atualizando tamanho
        _size = sizeOfInterval;
    }

    // Metodo para atribuir elementos de uma initializer_list a lista
    template<typename T>
    void list<T>::assign( std::initializer_list<T> ilist ){
        // Subproblema de assign
        assign( ilist.begin() , ilist.end() );
    }


    /*------------------------------------OPERATORS-OVERLOADING-------------------------*/

    // Sobrecarga de operador[]: Acessar n-esimo elemento
    template<typename T>
    typename list<T>::reference list<T>::operator[]( typename list<T>::size_type n ){
        if( n <= _size / 2){
            typename list<T>::Nodeptr curr( _hNode->_next );
            while ( n > 0 ){
                curr = curr->_next;
                n--;
            }
            return curr->_info;
        }else{
            n = _size - n - 1;
            typename list<T>::Nodeptr curr( _tNode->_prev );
            while ( n > 0 ){
                curr = curr->_prev;
                n--;
            }
            return curr->_info;
        }
    }

    // Sobrecarga de operador[]: Acessar n-esimo elemento
    template<typename T>
    typename list<T>::const_reference list<T>::operator[]( typename list<T>::size_type n ) const {
        if( n <= _size / 2){
            typename list<T>::Nodeptr curr( _hNode->_next );
            while ( n > 0 ){
                curr = curr->_next;
                n--;
            }
            return curr->_info;
        }else{
            n = _size - n - 1;
            typename list<T>::Nodeptr curr( _tNode->_prev );
            while ( n > 0 ){
                curr = curr->_prev;
                n--;
            }
            return curr->_info;
        }
    }

    // Sobrecarga de operador==: Ver se listas sao iguais
    template<typename T>
    bool list<T>::operator==( const list<T> &rhs){
        // Sera igual se os tamanhos forem iguais (e os valores tambem)
        if( _size == rhs._size){
            // Criando iteradores para percorrer as listas
            auto curr_this( begin() );
            auto curr_rhs( rhs.begin() );

            // Enquanto os valores forem iguais, avançar
            while( *curr_this == *curr_rhs && curr_this != end()){
                curr_this++;
                curr_rhs++;
            }

            // Se chegamos ao final, as listas sao iguais
            return curr_this == end();

        }else{
            return false;
        }
    }

    // Sobrecarga de operador==: Ver se listas sao diferentes
    template<typename T>
    bool list<T>::operator!=( const list<T> &rhs){
        return !( operator==( rhs ) ); // Caso a lista nao seja igual, eh diferente
    }

    /*------------------------------------ITERATORS-FUNCS-------------------------------*/

    // Funcao para inserir nó com valor element logo antes de itr. Retorna
    // iterador para elemento inserido
    template<typename T>
    typename list<T>::iterator list<T>::insert(typename list<T>::iterator itr, typename list<T>::const_reference element){
        // Recuperando nó em itr e itr-1
        typename list<T>::Nodeptr node_itr( get_ptr(itr) );
        typename list<T>::Nodeptr pnode_itr( node_itr->_prev );

        // Criando nó que será inserido
        typename list<T>::Nodeptr temp( new Node( element, pnode_itr, node_itr) );

        // Atualizando node_itr e temp
        pnode_itr->_next = temp;
        node_itr->_prev = temp;

        //Atualizando tamanho
        _size++;

        // Retornando
        return iterator( temp );
    }

    // Funcao para inserir nó com valor element logo antes de itr.
    // Retorna const_iterator para elemento inserido
    template<typename T>
    typename list<T>::const_iterator list<T>::insert(typename list<T>::const_iterator itr, typename list<T>::const_reference element){
        // Recuperando nó em itr e itr-1
        typename list<T>::Nodeptr node_itr( get_ptr(itr) );
        typename list<T>::Nodeptr pnode_itr( node_itr->_prev );

        // Criando nó que será inserido
        typename list<T>::Nodeptr temp( new Node( element, pnode_itr, node_itr) );

        // Atualizando node_itr e temp
        pnode_itr->_next = temp;
        node_itr->_prev = temp;

        //Atualizando tamanho
        _size++;

        // Retornando
        return const_iterator( temp );
    }

    // Funcao para inserir Range definida por [first,last) logo antes de itr.
    // Retorna iterator para primeiro nó do intervalo criado
    template <typename T>
    template <typename IT>
    typename list<T>::iterator list<T>::insert( typename list<T>::iterator itr, IT first, IT last ){
        // Queremos criar uma lista temporaria, pra adiciona-la logo antes de itr
        auto frontNode(  get_ptr( itr ) );
        auto backNode(  get_ptr( itr - 1) );

        // Calculando variavel auxiliar
        auto sizeOfInterval = last - first;

        // Atualizando tamanho
        _size += sizeOfInterval;

        // Criando lista temporaria
        list<T> temp_list( sizeOfInterval );
        temp_list.assign( first, last );


        // Recuperando ultimo nó válido da lista temporaria
        typename list<T>::Nodeptr last_node_from_temp_list( get_ptr(temp_list.end() - 1) );

        // O próximo elemento do ultimo nó da lista temporaria eh o nó em itr
        last_node_from_temp_list->_next = frontNode;
        // E o anterior ao frontNode eh o last_node_from_temp_list
        frontNode->_prev = last_node_from_temp_list;

        // Recuperando primeiro nó válido da lista temporaria
        typename list<T>::Nodeptr first_node_from_temp_list( get_ptr(temp_list.begin()) );

        // O elemento anterior do primeiro nó válido da lista temporaria eh o nó em itr - 1
        first_node_from_temp_list->_prev = backNode;
        // E o contrario...
        backNode->_next = first_node_from_temp_list;

        // Resetando lista temporaria para ser excluida
        temp_list._hNode->_next = temp_list._tNode;
        temp_list._tNode->_prev = temp_list._hNode;

        // Retornando iterator formado pelo primeiro no do intervalo inserido
        return iterator( first_node_from_temp_list );
    }

    // Funcao para inserir Range definida por [first,last) logo antes de itr.
    // Retorna const_iterator para primeiro nó do intervalo criado
    template <typename T>
    template <typename IT>
    typename list<T>::const_iterator list<T>::insert( typename list<T>::const_iterator itr, IT first, IT last){
        // Queremos criar uma lista temporaria, pra adiciona-la logo antes de itr
        auto frontNode(  get_ptr( itr ) );
        auto backNode(  get_ptr( itr - 1) );

        // Calculando variavel auxiliar
        auto sizeOfInterval = last - first;

        // Atualizando tamanho
        _size += sizeOfInterval;

        // Criando lista temporaria
        list<T> temp_list( sizeOfInterval );
        temp_list.assign( first, last );

        // Recuperando ultimo nó válido da lista temporaria
        typename list<T>::Nodeptr last_node_from_temp_list( get_ptr(temp_list.end() - 1) );

        // O próximo elemento do ultimo nó da lista temporaria eh o nó em itr
        last_node_from_temp_list->_next = frontNode;
        // E o anterior ao frontNode eh o last_node_from_temp_list
        frontNode->_prev = last_node_from_temp_list;

        // Recuperando primeiro nó válido da lista temporaria
        typename list<T>::Nodeptr first_node_from_temp_list( get_ptr(temp_list.begin()) );

        // O elemento anterior do primeiro nó válido da lista temporaria eh o nó em itr - 1
        first_node_from_temp_list->_prev = backNode;
        // E o contrario...
        backNode->_next = first_node_from_temp_list;

        // Resetando lista temporaria para ser excluida
        temp_list._hNode->_next = temp_list._tNode;
        temp_list._tNode->_prev = temp_list._hNode;

        // Retornando const_iterator formado pelo primeiro no do intervalo inserido
        return const_iterator( first_node_from_temp_list );
    }

    // Funcao para inserir initializer_list il logo antes de itr.
    // Retorna iterator para primeiro nó da lista inserida criado
    template<typename T>
    typename list<T>::iterator list<T>::insert( typename list<T>::iterator itr, const std::initializer_list<T> &il){
        // Subproblema de insert de range
        return insert( itr, il.begin(), il.end() );
    }

    // Funcao para inserir initializer_list il logo antes de itr.
    // Retorna const_iterator para primeiro nó da lista inserida criado
    template<typename T>
    typename list<T>::const_iterator list<T>::insert( typename list<T>::const_iterator itr, const std::initializer_list<T> &il){
        // Subproblema de insert de range
        return insert( itr, il.begin(), il.end() );
    }

    // Funcao para remover nó em itr.
    // Retorna iterator para primeiro nó da lista logo após o nó apagado
    template<typename T>
    typename list<T>::iterator list<T>::erase( typename list<T>::iterator itr ){
        // Subproblema de erase de intervalo
        return erase( itr, itr + 1);
    }

    // Funcao para remover nó em itr.
    // Retorna const_iterator para primeiro nó da lista logo após o nó apagado
    template<typename T>
    typename list<T>::const_iterator list<T>::erase( typename list<T>::const_iterator itr ){
        // Subproblema de erase de intervalo
        return erase( itr, itr + 1);
    }

    // Funcao para remover intervalo em itr.
    // Retorna iterator para primeiro nó da lista logo após o intervalo excluido
    template<typename T>
    typename list<T>::iterator list<T>::erase( typename list<T>::iterator first, typename list<T>::iterator last ){
        // Caso first == last, nada sera excluido
        if(first == last) return first;

        // Calculando variavel auxiliar
        auto sizeOfInterval = last - first;

        // Criando variavel para receber o primeiro elemento do intervalo e criando uma variavel temporaria
        typename list<T>::Nodeptr curr( get_ptr( first ) ), temp;
        typename list<T>::Nodeptr last_ptr( get_ptr( last ) );
        while( curr != last_ptr ){
            ( curr->_next )->_prev = curr->_prev;
            ( curr->_prev )->_next = curr->_next;
            temp = curr->_next;
            delete curr;
            curr = temp;
        }

        // Atualizando tamanho
        _size-=sizeOfInterval;

        return typename list<T>::iterator::iterator( get_ptr( last ) );
    }

    // Funcao para remover intervalo em itr.
    // Retorna const_iterator para primeiro nó da lista logo após o intervalo
    template<typename T>
    typename list<T>::const_iterator list<T>::erase( typename list<T>::const_iterator first, typename list<T>::const_iterator last ){
        // Caso first == last, nada sera excluido
        if(first == last) return first;

        // Calculando variavel auxiliar
        auto sizeOfInterval = last - first;

        // Criando variavel para receber o primeiro elemento do intervalo e criando uma variavel temporaria
        typename list<T>::Nodeptr curr( get_ptr( first ) ), temp;
        typename list<T>::Nodeptr last_ptr( get_ptr( last ) );
        while( curr != last_ptr ){
            ( curr->_next )->_prev = curr->_prev;
            ( curr->_prev )->_next = curr->_next;
            temp = curr->_next;
            delete curr;
            curr = temp;
        }

        // Atualizando tamanho
        _size -= sizeOfInterval;

        return typename list<T>::const_iterator::const_iterator( get_ptr( last ) );
    }

    // Funcao para achar primeiro nó com valor igual a value
    // Retorna iterador para primeiro nó achado com valor value
    template<typename T>
    typename list<T>::iterator list<T>::find( const T & value ){
        typename list<T>::Nodeptr curr( _hNode->_next );
        while( curr->_info != value && curr != _tNode ){
            curr = curr->_next;
        }
        return typename list<T>::iterator::iterator( curr );
    }

    // Funcao para achar primeiro nó com valor igual a value
    // Retorna const_iterator para primeiro nó achado com valor value
    template<typename T>
    typename list<T>::const_iterator list<T>::find( const T & value ) const{
        typename list<T>::Nodeptr curr( _hNode->_next );
        while( curr->_info != value && curr != _tNode ){
            curr = curr->_next;
        }
        return typename list<T>::const_iterator::const_iterator( curr );
    }

    // Recupera o nó guardado pelo iterator itr
    template<typename T>
    typename list<T>::Nodeptr list<T>::get_ptr( typename list<T>::iterator itr ){
        return itr._ptr;
    }

    // Recupera o nó guardado pelo const_iterator itr
    template<typename T>
    typename list<T>::Nodeptr list<T>::get_ptr( typename list<T>::const_iterator itr ){
        return itr._ptr;
    }
}

template < typename T >
std::ostream& operator<< (std::ostream& os, const sc::list<T>& l){
    os << "[ ";
    for (auto i( l.begin() ); i != l.end(); ++i ) {
        os << *i << " ";
    }
    os << "]";
    return os;
}
