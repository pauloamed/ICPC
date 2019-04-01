#ifndef HUFFMAN
#define HUFFMAN

#include<fstream> // ifstream e ofstream
#include<string> // string
#include<vector> // vector
#include<map> // map (tableComp)
#include<iostream> // cerr

#include"HeapMin.hpp"
#include"Node.hpp"

#define DELIMITADOR '~'

class Huffman{
private:
    size_t _numChars; // quantidade de caracteres diferentes
    Node *_root; // nó raiz

    // Metodo para adiconar bits de char a um vetor de booleanos
    void _addCharToBoolVec(unsigned char c, std::vector<bool> &v){
        size_t itr(8);
        // Para cada bit, adiociona-lo
        while(itr--){
            // Acessar o primeiro bit
            v.push_back(_mostSigBit(c));

            // Consumir 1 bit do char
            c <<= 1;
        }
    }

    // Metodo para gerar o cabecalho. Percorrimento eh pre-ordem
    void _headerGen(Node *root, std::vector<bool> &walk){
        // Recuperando filhos do no atual
        auto a = root->children[0];
        auto b = root->children[1];

        // Se no atual for folha
        if(!a && !b){
            // Adicionar 1 e o char
            walk.push_back(1);
            _addCharToBoolVec(root->content, walk);
        }else{
            // Adiocnar 0 e seguir o Percorrimento
            walk.push_back(0);
            _headerGen(a, walk);
            _headerGen(b, walk);
        }
    }

    // Recuperar um char dos proximos 8 bits de um vetor de bool
    unsigned char _charFromBoolVec(std::vector<bool> &v, size_t &itr){
        const unsigned char ONE_MASK = 1;
        const unsigned char ZERO_MASK = (1 << 8) - 2;
        size_t i(8);
        char ret = 0;

        // Percorrer os 8 bits correspondentes
        while(i--){
            if(v[itr++]) ret |= ONE_MASK; // Se for um bit positivo, escreva 1
            else ret &= ZERO_MASK; // Senao, escreva 0
            if(i) ret <<= 1;
        }
        return ret;
    }

    // Gerador do header a partir da sequencia de bits
    void _treeGenHeader(Node *current, std::vector<bool> &temp, size_t &itr){
        // Se for 1, esperar um char em ascii
        if(temp[itr++]){
            current->content = _charFromBoolVec(temp, itr);
        }else{
        // Se for 0, criar os filhos e seguir
            current->children[0] = new Node;
            current->children[1] = new Node;

            _treeGenHeader(current->children[0], temp, itr);
            _treeGenHeader(current->children[1], temp, itr);
        }
    }

    // Gerador da tabela de compressao
    void _comprTableGen(Node *root, std::vector<bool> &temp,
        std::map<char, std::vector<bool> > &comprTable){

        auto a = root->children[0];
        auto b = root->children[1];

        if(a){
            temp.push_back(0);
            _comprTableGen(root->children[0], temp, comprTable);
            temp.pop_back();
        }
        if(b){
            temp.push_back(1);
            _comprTableGen(root->children[1], temp, comprTable);
            temp.pop_back();
        }

        if(!a && !b){
            comprTable[root->content] = temp;
        }
    }

    void _maybeResetBuffer(unsigned char &buffer,
                            size_t &buffer_count,
                            std::vector<unsigned char> &compr){

        // Se todos caracteres ja foram consumidos
        if(buffer_count == 7){
            // Zerar a quantidade de caracteres consumidos
            buffer_count = 0;

            // Adicionar um caracter pronto a saida
            compr.push_back(buffer);

            // Zerar o buffer
            buffer = 0;
        }else{
            // "Consumir" 1 caractere do buffer
            buffer <<= 1;
            // Incrementar a quantidade de caracteres consumidos
            buffer_count++;
        }
    }

    // Funcao para retornar o bit mais significativo de um char
    bool _mostSigBit(unsigned char c){
        return (c >> 7);
    }

    // Recuperar os bits de uma string
    std::vector<bool> _bitsFromString(std::string str){
        std::vector<bool> ret;
        for(auto i(0u); i < str.size(); ++i){
            _addCharToBoolVec(str[i], ret);
        }
        return ret;
    }



public:
    Huffman(std::string file_name, bool fromCompressed){
        std::ifstream iff(file_name);
        std::string str;
        // se for compactado pegará apenas o cabeçalho do arquivo
        if(fromCompressed){
            // Recuperando linha de cabecalho
            getline(iff, str, DELIMITADOR);

            std::vector<bool> comprHeader = _bitsFromString(str);

            // Criando raiz da arvore
            _root = new Node;

            // Gerando a arvore a partir do cabecalho
            size_t itr = 0;
            _treeGenHeader(_root, comprHeader, itr);

            // Fechando stream
            iff.close();
        }else{ // se nao for, pegará o arquivo inteiro
            size_t numChars = 256;
            size_t count[numChars];
            for(size_t i(0u); i < numChars; ++i) count[i] = 0;

            char c;
            while(iff.get(c)){
                count[static_cast<size_t> (c)]++;
            }
            iff.close();


            _numChars = 0; // inicializando q quantidade de caracteres diferentes com 0
            HeapMin heap(numChars * 3); // atribuindo valor maximo à heap

            // se a quantidade de letras em uma determinada posição for
			//maior que 0, será inserido na heap a posição dessa letra
            for(auto i = 0u; i < numChars; ++i){
                if(count[i] != 0){
                    heap.insert({count[i], new Node(nullptr, nullptr, i)});
                    _numChars++; // incrementando a variavel que conta a quantidade de caracteres diferentes
                }
            }
            // inserindo caractere de final de arquivo
            heap.insert({1, new Node});

            std::pair<size_t, Node *> a, b;
            while (heap.size() > 1) { // enquanto o tamanho da heap for maior que 1 (possuindo ainda conteudo nela)
                a = heap.top(); //salvando o topo
                heap.remove(); // removendo o topo

                b = heap.top(); //salvando o novo topo
                heap.remove(); // removendo novamente

                //somando o peso de 'a' e 'b' e criando um novo nó
                heap.insert({a.first + b.first, new Node(a.second, b.second)});
            }

            _root = heap.top().second; //atribuindo ao nó raiz o nó que está no topo da heap

        }
    }

    ~Huffman(){
        // TODO DESTRUTOR
    }

    void compress(std::string file_name){
        // Abrindo arquivo que sera comprido
        std::ifstream iff(file_name);

        // Criando tabela de compressao dos caracteres a partir do percorrimento
        // pre-ordem da arvore
        std::vector<bool> header;
        _headerGen(_root, header);

        while(header.size() % 8) header.push_back(0);

        // Delimitando o header
        _addCharToBoolVec(DELIMITADOR, header);

        std::map<char, std::vector<bool> > comprTable;
        std::vector<bool> temp;
        _comprTableGen(_root, temp, comprTable);

        // Mascaras para setar o bit menos significativo como 1 (ONE_MASK) ou
        // como 0 (ZERO_MASK)
        const unsigned char ONE_MASK = 1;
        const unsigned char ZERO_MASK = 254;

        // Vetor que guardara os bytes comprimidos
        std::vector<unsigned char> compr;

        // Vetor que recebera a compressao de um dado caractere
        std::vector<bool> c_compr;

        // Caractere temporario para recuperar texto do arquivo
        char c;

        // Variavel auxiliar para contar quantos bits do buffer ja foram usados
        size_t buffer_count = 0;

        // O buffer (1 byte) de escrita
        unsigned char buffer = 0;


        for(auto it(header.begin()); it != header.end(); ++it){
            if(*it) buffer |= ONE_MASK; // Se for um bit positivo, escreva 1
            else buffer &= ZERO_MASK; // Senao, escreva 0

            // Checando se o buffer esta cheio, e se eh necessario salvar
            _maybeResetBuffer(buffer, buffer_count, compr);
        }

        // Para cada caractere do arquivo, enquanto nao chega em seu fim
        while(iff.get(c)){
            // Recuperando a compressao de um caractere
            c_compr = comprTable[c];

            // Para cada "bit" da compressao
            for(auto it(c_compr.begin()); it != c_compr.end(); ++it){
                if(*it) buffer |= ONE_MASK; // Se for um bit positivo, escreva 1
                else buffer &= ZERO_MASK; // Senao, escreva 0

                // Checando se o buffer esta cheio, e se eh necessario salvar
                _maybeResetBuffer(buffer, buffer_count, compr);
            }
        }

        // Fechando arquivo de leitura
        iff.close();
        c_compr = comprTable['\0'];
        for(auto it(c_compr.begin()); it != c_compr.end(); ++it){
            if(*it) buffer |= ONE_MASK; // Se for um bit positivo, escreva 1
            else buffer &= ZERO_MASK; // Senao, escreva 0

            // Checando se o buffer esta cheio, e se eh necessario salvar
            _maybeResetBuffer(buffer, buffer_count, compr);
        }

        // Caso o buffer atual ainda nao tenha sido salvo, salva-lo
        if(buffer_count){
            buffer <<= (7 - buffer_count);
            compr.push_back(buffer);
        }

        // Abrindo arquivo de escrita
        std::ofstream off(file_name + ".c");

        // Escrever os bytes de escrita
        for(auto it(compr.begin()); it != compr.end(); ++it){
            off << (*it);
        }

        // Fechando arquivo de escrita
        off.close();
    }


    void uncompress(std::string file_name){
        // Abrindo arquivo de leitura
        std::ifstream iff(file_name);

        // Abrindo arquivo de escrita
        file_name.pop_back();
        file_name.pop_back();
        std::ofstream off(file_name + ".u");

        // Passa da primeira linha que eh o cabecalho
        std::string str = "";
        getline(iff, str, DELIMITADOR);

        // Char que sera lido do texto comprimido
        char c;
        // unsigned char _c;

        // Char que vai guardar o conteudo do no folha acessado
        char content;

        // Contador de quantos bits do char foram usados
        size_t bit_count;

        // Marcador do no atual no percorrimento de descompressao da arvore
        Node* current = _root;

        // Para cada char do arquivo
        while(iff.get(c)){
            // Temos ainda 8 bits validos, resetamos o bit_count
            bit_count = 8;


            while(bit_count--){
                // Andando para esq. ou dir. dependendo do bit lido
                if(_mostSigBit(c)) current = current->children[1];
                else current = current->children[0];

                // Consumindo 1 bit do char lido
                if(bit_count) c <<= 1;

                // Se atingimos uma folha
                if(!current->children[0] && !current->children[1]){
                    // Recuperando char de seu conteudo
                    content = current->content;

                    // Se for a marcacao de final de arquivo, acabamos a descomp.
                    if(content == '\0'){
                        // Fechando streams de leitura dos arquivos
                        iff.close();
                        off.close();

                        // Retornamos para a main
                        return;
                    }else{ // Caso nao seja

                        // Escrevendo o char valido no arquivo descomprimido
                        off << content;

                        // Resetando para a raiz
                        current = _root;
                    }
                }
            }
        }

        // Descompressao por fim do arquivo e nao por achar char posto na compr.
        std::cerr << "ERROR 3: End of compression (\\0) char was not found while";
        std::cerr << " uncompressing\n";

        // Fechando streams de leitura dos arquivos
        iff.close();
        off.close();
    }

};

#endif
