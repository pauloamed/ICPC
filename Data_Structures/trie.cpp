#include <bits/stdc++.h>

using namespace std;

const int ALPHABET_SIZE = 26;

class Trie{
    private:
        class Node{
            public:
                Node *children[ALPHABET_SIZE];
                bool isEndOfWorld;

                Node(){
                    isEndOfWorld = false;
                    for (int i = 0; i < ALPHABET_SIZE; i++){
                        children[i] = NULL;
                    }
                }
        };
    public:
        Node *root;

        Trie(){
            root = new Node();
        }
        
        void insert(string &s){
            Node *current = root;

            for (int i = 0; i < s.size(); i++){
                int index = s[i] - 'a';

                if (!current->children[index]){
                    current->children[index] = new Node();
                }

                current = current->children[index];
            }

            current->isEndOfWorld = true;
        }

        bool search(string &s){
            Node *current = root;

            for (int i = 0; i < s.size(); i++){
                int index = s[i] - 'a';

                if (!current->children[index]){
                    return false;
                }

                current = current->children[index];
            }

            return (current != NULL && current->isEndOfWorld);
        }

        bool isEmpty(Node *current){
            for(int i = 0; i < ALPHABET_SIZE; i++){
                if(current->children[i]){
                    return false;
                }
            }

            return true;
        }

        Node* remove(Node* root, string &s, int i = 0){
            if(!root){
                return NULL;
            }

            if(i == s.size()){
                if(root->isEndOfWorld){
                    root->isEndOfWorld = false;
                }

                if(isEmpty(root)){
                    delete root;
                    root = NULL;
                }

                return root;
            }

            int index = s[i] - 'a';

            Node *current = root->children[index];
            root->children[index] = remove(current, s, i+1);

            if(isEmpty(root) && !root->isEndOfWorld){
                delete root;
                root = NULL;
            }

            return root;
        }
};

int main(){
    int t;

    cin >> t;

    int n;

    while (t--){
        cin >> n;

        Trie *trie = new Trie();
        vector<string> lista(n);

        for (int i = 0; i < n; i++){
            cin >> lista[i];
        }

        sort(lista.begin(), lista.end(), [](string &a, string &b) {
            return a.size() > b.size();
        });

        bool flag = true;

        for (int i = 0; i < n; i++){
            //Testing search
            if (trie->search(lista[i])){
                flag = false;
                break;
            }

            //Testing insertion
            trie->insert(lista[i]);
        }

        //Testing consistency
        flag ? cout << "YES" << endl : cout << "NO" << endl;

        string a = "there";

        //Testing remotion
        cout << "FOUND: " << trie->search(a) << endl;
        trie->remove(trie->root, a);
        cout << "FOUND: " <<  trie->search(a) << endl;
    }

    return 0;
}
