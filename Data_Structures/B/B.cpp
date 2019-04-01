#include<bits/stdc++.h>
using namespace std;

class BTree{
private:
    struct node{
        vector<int> vals;
        vector<node *> pts;
    };

    node* root;
    size_t d;

    bool _rsearch(const int val, node *current){
        if(!current) return false;

        for(auto i(0u); i < current->vals.size(); ++i){
            if(val < current->vals[i]){
                return _rsearch(val, current->pts[i]);
            }else if (val == current->vals[i]) {
                return true;
            }
        }
        return _rsearch(val, current->pts.back());
    }

    void cisao(stack<node*> &trail){
        node* last, *parent;
        while(!trail.empty()){
            last = trail.top();
            trail.pop();
            if(last->vals.size() > 2*d){
                int mediana = last->vals[d];
                node* newnode = new node;

                newnode->vals.insert(newnode->vals.begin(),
                        last->vals.begin() + d + 1,
                        last->vals.end());

                newnode->pts.insert(newnode->pts.begin(),
                        last->pts.begin() + d + 1,
                        last->pts.end());

                last->vals.erase(last->vals.begin() + d, last->vals.end());
                last->pts.erase(last->pts.begin() + d + 1, last->pts.end());
                if(trail.empty()){
                    // raiz
                    parent = new node;
                    parent->vals.push_back(mediana);

                    parent->pts.push_back(last);
                    parent->pts.push_back(newnode);

                    this->root = parent;
                }else{
                    parent = trail.top();
                    for(auto i(0u); i <= parent->vals.size(); ++i){
                        if(i == parent->vals.size()){
                            parent->vals.push_back(mediana);
                            parent->pts.push_back(newnode);
                            break;
                        }
                        else if(mediana < parent->vals[i]){
                            parent->vals.insert(parent->vals.begin() + i,
                                    mediana);
                            parent->pts.insert(parent->pts.begin() + i + 1,
                                    newnode);
                            break;
                        }
                    }
                }
            }else{
                break;
            }
        }
    }

    void _print(node *curr){
        if(!curr) return;

        for(auto i(0u); i < curr->vals.size(); ++i){
            cout << curr->vals[i] << " ";
        }cout << endl;

        for(auto i(0u); i < curr->pts.size(); ++i){
            _print(curr->pts[i]);
        }
    }

public:
    BTree(size_t _d, const int val):d(_d){
        root = new node;

        root->pts.push_back(nullptr);
        root->pts.push_back(nullptr);
        root->vals.push_back(val);
    }

    ~BTree(){

    }

    bool isearch(const int val){
        node* current = this->root;

        while(current){
            for(auto i(0u); i < current->vals.size(); ++i){
                if(val < current->vals[i]){
                    current = current->pts[i];
                    break;
                }else if (val == current->vals[i]) {
                    return true;
                }
            }
            current = current->pts.back();
        }
        return false;
    }

    bool rsearch(const int val){
        return _rsearch(val, this->root);
    }

    bool iinsert(const int val){
        node* current = this->root;
        stack<node *> trail;

        // Insere sem medo

        bool flag = false;
        while(!flag){
            trail.push(current);
            for(auto i(0u); i < current->vals.size(); ++i){
                if(val < current->vals[i]){
                    if(current->pts[i]){
                        current = current->pts[i];
                    }else{
                        current->vals.insert(current->vals.begin() + i,
                                val);
                        current->pts.push_back(nullptr);
                        flag = true;
                    }
                    break;
                }else if (val == current->vals[i]) {
                    return false;
                }
            }
            if(current->pts.back()){
                current = current->pts.back();
            }else{
                current->vals.push_back(val);
                current->pts.push_back(nullptr);
                flag = true;
            }
        }

        cisao(trail);
        return true;
    }

    bool iremove(){
        node* current = this->root;
        stack<node *> trail;

        bool flag = false;
        while(!flag){
            trail.push(current);
            for(auto i(0u); i < current->vals.size(); ++i){
                if(val < current->vals[i]){
                    if(current->pts[i]){
                        current = current->pts[i];
                    }else{
                        current->vals.insert(current->vals.begin() + i,
                                val);
                        current->pts.push_back(nullptr);
                        flag = true;
                    }
                    break;
                }else if (val == current->vals[i]) {
                    return false;
                }
            }
            if(current->pts.back()){
                current = current->pts.back();
            }else{
                current->vals.push_back(val);
                current->pts.push_back(nullptr);
                flag = true;
            }
        }

        cisao(trail);
        return true;
    }

    void print(){
        _print(root);
    }

};

int main(){
    BTree a(1, 1);
    for(int i = 2; i < 10; ++i){
        a.iinsert(i);
        a.print();
        printf("\n");
    }
}
