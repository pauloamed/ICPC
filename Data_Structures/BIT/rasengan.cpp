#include<bits/stdc++.h>
using namespace std;

long long size;

long long bit[ 100001 ];
long long v[ 100001 ];
long long primo = 1000000007;

long long query( int index, long long bit_v[] ){
    long long ans(0);
    for( ; index > 0; index -= index & (-index)){
        ans = (ans + bit_v[index]) % primo;
    }
    return ans;
}

void update( int index, long long val, long long bit_v[] ){
      for( ; index <= size; index += index & (-index)){
          bit_v[index] = (bit_v[index] + val) % primo;
      }
}

long long inversoes( long long bit_v[] ){
    long long ans(0);
    for(int i = size; i > 0; i--){
        ans = (ans + query( v[i], bit_v )) % primo;
        update( v[i], 1, bit_v );
    }
    return ans;
}

long long inversoes_subarrays( long long bit_v[] ){
    long long ans(0);
    for(int i = size; i > 0; i--){
        ans = (ans + (i * query( v[i], bit_v )) % primo) % primo;
        update( v[i], (size - i + 1), bit_v );
    }
    return ans;
}


long long fastexp( long long base, long long exp){
    if( exp == 0 ) return 1;

    long long ans = fastexp( base, exp/2);
    ans = (ans * ans) % primo;

    if( exp % 2 == 1 ){
        ans = (ans * base) % primo;
    }
    return ans % primo;
}

long long inverso( long long a ){
    return fastexp( a, primo - 2 );
}

int main(){
    scanf("%lld", &size);
    for(int i = 1; i <= size; ++i){
        scanf("%lld", v + i);
    }

    long long invsub = inversoes_subarrays( bit );
    // printf("%lld\n", invsub);

    for(int i = 1; i <= size; ++i){
        bit[i] = 0;
    }

    long long formula = ((size * (size + 1)) / 2) % primo;

    long long szs(0);
    for(long long i = 1; i <= size; ++i){
        szs = (szs + ( size - (i - 1) ) * ((i * ( i - 1 )) % primo)) % primo;
    }
    szs = (szs * inverso(2)) % primo;

    // printf("%lld\n", szs);
    long long numerador =  (( formula * inversoes( bit ) ) % primo);
    // printf("%lld\n", numerador);
    numerador = ( numerador +( ((primo-2) * invsub)%primo )) % primo;
    // printf("%lld\n", numerador);
    numerador = (numerador + szs) % primo;
    // printf("%lld\n", formula);
    // printf("%lld\n", numerador);

    printf("%lld\n", (numerador * inverso(formula)) % primo );
}
