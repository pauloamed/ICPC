#include<bits/stdc++.h>
using namespace std;


long long bit[100001];
int primo;

long long query( int index ){
    long long ans(0);
    // index -= index & (-index)
    // index menos o bit menos significativo
    for( ; index > 0; index -= index & (-index)){
        ans = (((ans + bit[index]) % primo) + primo) % primo;
    }
    return ans;
}

void update( int index, int val ){
      for( ; index < 100001; index += index & (-index)){
          bit[index] = (bit[index] + val) % primo;
      }
}

void reset(){
    for(int i(0); i < 100001; ++i){
        bit[i] = 0;
    }
}

long long fast_expo( int base, int expo ){
    if( base == 0 ) return 0;
    if( expo == 0 ) return 1;
    if( expo == 1 ) return base;

    long long ans = fast_expo(base, expo/2) % primo;
    ans = (ans * ans) % primo;

    if(ans < 0){
        printf("OVERFLOW\n");
    }

    if(expo % 2 == 1) return (ans * base) % primo;
    else return ans;
}

long long inverso( int a ){
    return fast_expo( a, primo - 2 );
}

void print( void ){
    for (int i(1); i <= 6; ++i) {
        printf("%d ", (((query(i) - query(i-1)) % primo) + primo) % primo);
    }printf("\n");
}

int main(){
    int B, L, N, I, V;
    char c;
    long long atual_la, proximo_la, temp;
    while(scanf("%d %d %d %d", &B, &primo, &L, &N)){
        if( B == 0 ) return 0;

        for(int i(0); i < N; ++i){
            scanf(" %c %d %d", &c, &I, &V);
            if(c == 'E'){
                atual_la = (((query(I) - query(I - 1)) % primo) + primo) % primo;
                proximo_la = ( fast_expo( B, L - I ) * V ) % primo;
                temp = (((proximo_la - atual_la) % primo) + primo) % primo;
                update( I,  temp);
            }else{
                temp = (((query(V) - query(I - 1)) % primo) + primo) % primo;
                // printf("temp: %d\n", temp);
                // printf("fe: %lld\n", fast_expo( B, L - V ));
                // printf("inv: %d\n", inverso(fast_expo( B, L - V )));
                cout << (temp * inverso(fast_expo( B, L - V ))) % primo << endl;
            }
            // print();
        }

        printf("-\n");
        reset();
    }
}
