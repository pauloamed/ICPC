#include<bits/stdc++.h>

size_t char2pos(char c){
    return c - 'a';
}

struct Node{
    char content;
    Node **children;
    bool isTerminal;

    Node(size_t alphabet_size){
        children = new Node*[alphabet_size];

        for(auto i(0u); i < alphabet_size; ++i)
            children[i] = nullptr;

        isTerminal = false;
        content = '\0';
    }

    ~Node(){
        delete children;
    }
};

class Trie{
private:
    Node *root;
    size_t sizeAlphabet;
    size_t sizeTree;

    bool _search(std::string x, Node* current_node, size_t current_pos){
        if( current_pos == x.size() ){
            if(current_node->isTerminal) return true;
            else return false;
        }else{
            size_t char_pos = char2pos(x[current_pos]);
            if(current_node->children[char_pos]){
                return _search(x, current_node->children[char_pos], current_pos+1);
            }else return false;
        }
    }

    bool _insert(std::string x, Node* current_node, size_t current_pos){
        if( current_pos == x.size() ){
            bool ans = current_node->isTerminal;
            current_node->isTerminal = true;
            return ans;
        }else{
            size_t char_pos = char2pos(x[current_pos]);
            if(current_node->children[char_pos] == nullptr){
                current_node->children[char_pos] = new Node(sizeAlphabet);
                current_node->children[char_pos]->content = x[current_pos];
            }
            return _insert(x, current_node->children[char_pos], current_pos+1);
        }
    }

    std::pair<bool,bool> _remove(std::string x, Node* current_node, size_t current_pos){
        if( current_pos == x.size()){
            bool ans = current_node->isTerminal;
            current_node->isTerminal = false;
            for(auto i(0u); i < sizeAlphabet; ++i){
                if(current_node->children[i]){
                    return {false, ans};
                }
            }
            return {ans, ans};
        }else{
            size_t char_pos = char2pos(x[current_pos]);
            bool ret = _remove(x, current_node->children[char_pos], current_pos+1).second;
            if(ret){

                if(current_node->isTerminal) return {false, ret};
                for(auto i(0u); i < sizeAlphabet; ++i){
                    if(current_node->children[i]) return {false, ret};
                }

                delete current_node->children[char_pos];
                current_node->children[char_pos] = nullptr;

                return {true, ret};
            }else{
                return {false, ret};
            }

        }
    }

    void _print(Node *current_node, std::string &current_str){
        current_str.push_back(current_node->content);

        // std::cout << current_node->content << std::endl;
        if(current_node->isTerminal){
            std::cout << current_str << std::endl;
        }

        for(auto i(0); i < sizeAlphabet; ++i){
            if(current_node->children[i])
                _print(current_node->children[i], current_str);
        }

        current_str.pop_back();
    }

public:
    Trie(size_t sizeAlphabet){
        root = new Node(sizeAlphabet);
        this->sizeAlphabet = sizeAlphabet;
    }

    ~Trie(){
        delete root;
    }

    bool search(std::string x){
        return _search(x, root, 0);
    }

    bool insert(std::string x){
        return _insert(x, root, 0);
    }

    bool remove(std::string x){
        return _remove(x, root, 0).second;
    }

    void print(){
        std::string temp = "";
        _print(root, temp);
    }
};

int main(){
    Trie trie(25);
    if(trie.insert("abcde")) printf("Inserido\n");
    else printf("Falha em insercao\n");
    if(trie.insert("abcd")) printf("Inserido\n");
    else printf("Falha em insercao\n");
    if(trie.insert("eeee")) printf("Inserido\n");
    else printf("Falha em insercao\n");
    if(trie.insert("ddeb")) printf("Inserido\n");
    else printf("Falha em insercao\n");


    if(trie.search("abcde")) printf("Achado\n");
    else printf("Falha em busca\n");
    if(trie.search("abcd")) printf("Achado\n");
    else printf("Falha em busca\n");
    if(trie.search("eeee")) printf("Achado\n");
    else printf("Falha em busca\n");
    if(trie.search("ddeb")) printf("Achado\n");
    else printf("Falha em busca\n");



    if(trie.remove("abcd")) printf("Removido\n");
    else printf("Falha em remocao\n");
    if(trie.remove("ddeb")) printf("Removido\n");
    else printf("Falha em remocao\n");

    trie.print();



}
