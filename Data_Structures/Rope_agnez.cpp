#include <iostream>
#include <cstdio>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;

int main(){
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    rope <int> v(n, 0);
    for(int i = 0; i < n; ++i)
        v.mutable_reference_at(i) = i + 1;
    int l, r;
    for(int i = 0; i < m; ++i){
        cin >> l >> r;
        --l, --r;
        rope <int> cur = v.substr(l, r - l + 1);
        v.erase(l, r - l + 1);
        v.insert(v.mutable_begin(), cur); // Insere ANTES do begin()
        //funcoes front, back, push/pop_front/back
        //void insert(size_t i, const charT* s, size_t n)
        //void replace(size_t i, size_t n1, const charT* s, size_t n2):
          //Replaces the n1 elements beginning with the ith element with the elements in the range [s, s + n2). 
    }
    for(int i = 0; i < n; ++i)
        cout << v[i] << " ";
    return 0;
}
