#include<bits/stdc++.h>
using namespace std;

int bits[2][100001];

long long query( int qual, int index ){
    long long ans(0);
    // index -= index & (-index)
    // index menos o bit menos significativo
    for( index++; index > 0; index -= index & (-index)){
        ans += bits[qual][index];
    }
    return ans;
}

void update( int qual, int index, int val ){
      for( index++; index < 100001; index += index & (-index)){
          bits[qual][index] += val;
      }
}

void reset(){
    for(int i(0); i < 100001; ++i){
        bits[0][i] = bits[1][i] = 0;
    }
}

int main(){
    int n, k, x, y;
    char c;

    while(scanf("%d %d", &n, &k) == 2){
        for(int i(0); i < n; ++i){
            scanf("%d", &x);
            if(x == 0){
                update(0, i, 1);
            }else if(x < 0){
                update(1, i, 1);
            }
        }

        for(int i(0); i < k; ++i){
            scanf(" %c %d %d", &c, &x, &y);
            // printf("%c %d %d\n", c, x, y);
            if(c == 'C'){
                long long query_zero = query(0, x-1) - query(0, x-2);
                long long query_neg = query(1, x-1) - query(1, x-2);

                // printf("::%d %d\n", query_zero, query_neg);

                if(y == 0){
                    if(query_neg > 0){
                        update(1, x-1, -1);
                    }
                    if(query_zero == 0){
                        update(0, x-1, 1);
                    }
                }else if(y < 0){
                    if(query_zero > 0){
                        update(0, x-1, -1);
                    }
                    if(query_neg == 0){
                        update(1, x-1, 1);
                    }
                }else{
                    if(query_zero > 0){
                        update(0, x-1, -1);
                    }
                    if(query_neg > 0){
                        update(1, x-1, -1);
                    }
                }
            }else{
                // printf(":::%d %d\n", query(0, y-1) - query(0, x-2),query(1, y-1) - query(1, x-2));
                if( query(0, y-1) - query(0, x-2) > 0){
                    printf("0");
                }else if((query(1, y-1) - query(1, x-2)) % 2 == 1){
                    printf("-");
                }else{
                    printf("+");
                }
            }
        }
        reset();
        printf("\n");
    }
}
