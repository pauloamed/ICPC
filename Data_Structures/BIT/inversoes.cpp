#include<bits/stdc++.h>
using namespace std;

int bit_v[100 + 1];
int v[100];

int query( int index ){
    int ans(0);
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

int inversoes( int size ){
    int ans(0);
    for(int i = size; i > 0; i--){
        ans += query( v[i] );
        update( v[i], 1 );
    }

    return ans;
}

int inversoes_subarrays( int size ){
    int ans(0);
    for(int i = size; i > 0; i--){
        ans += i * query( v[i] );
        update( v[i], (size - i + 1) );
    }
    return ans;
}

int main(){
    int size;
    scanf("%d", &size);
    for(int i = 1; i <= size; ++i){
        scanf("%d", v + i);
    }

    // printf("%d\n", inversoes( size ));
    printf("%d\n", inversoes_subarrays( size ));
}
