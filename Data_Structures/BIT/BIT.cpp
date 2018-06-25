#include<bits/stdc++.h>
using namespace std;

int v[100];
int bit_v[100 + 1];

int query( int index ){
    int ans(0);
    // index -= index & (-index)
    // index menos o bit menos significativo
    for( index++; index > 0; index -= index & (-index)){
        ans += bit_v[index];
    }
    return ans;
}

void update( int index, int val ){
      for( index++; index <= 101; index += index & (-index)){
          bit_v[index] += val;
      }
}

int main(){
    // Inicializando vetor original de valores
    for( int i(0); i < 30; ++i){
        v[i] = i;
        update( i, v[i]);
    }

    for( int i(0); i < 30; ++i){
        update(i, 1);
        printf("%d ", query(i) - query(i - 1));
    }printf("\n");



}
