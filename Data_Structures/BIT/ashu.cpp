#include<bits/stdc++.h>
using namespace std;

int v[100000];
int bit_v[100000 + 1];

int query( int index ){
    int ans(0);
    for( index++; index > 0; index -= index & (-index)){
        ans += bit_v[index];
    }
    return ans;
}

void update( int index, int val ){
      for( index++; index <= 100001; index += index & (-index)){
          bit_v[index] += val;
      }
}

int main(){
    int n, id, x, y, q;

    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        scanf("%d", &x);
        v[i] = x % 2;
        update(i+1, v[i]);
    }

    scanf("%d", &q);
    for(int i = 0; i < q; ++i){
        scanf("%d %d %d", &id, &x, &y);
        if( id == 0){
            if( v[x-1] == 0 && y % 2 == 1){
                update(x, 1);
                v[x-1] = 1;
            }else if( v[x-1] == 1 && y % 2 == 0){
                update(x, -1);
                v[x-1] = 0;
            }
        }else if( id == 1){
            printf("%d\n", (y - x + 1) - (query(y) - query(x - 1)));
        }else{
            printf("%d\n", query(y) - query(x - 1));
        }
    }

}
