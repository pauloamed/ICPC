#ifndef NODE
#define NODE

struct Node{
    Node **children; //criando ponteiro de vetor para criar os filhos
    unsigned char content; // variavel que guadará os caracteres dos nós
    // criando construtor do nó
    Node(Node* a = nullptr, Node* b = nullptr, unsigned char _content = '\0'){
        children = new Node*[2]; // criando novo nó
        children[0] = a; // atribuindo filho a esquerda
        children[1] = b; //atribuindo filho a direita
        content = _content; // atribuindo caractere que será guardado
    }
};

#endif
