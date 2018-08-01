#include<bits/stdc++.h>
using namespace std;

int size;

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

long long gcd(long long a, long long b){
    long long temp;
    if( a > b ) swap(a,b);

    while( a != 0 ){
        temp = a;
        a = b % a;
        b = temp;
    }
    return b;
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
    scanf("%d", &size);
    for(int i = 1; i <= size; ++i){
        scanf("%lld", v + i);
    }

    long long invsub = inversoes_subarrays( bit );
    // printf("%lld\n", invsub);

    for(int i = 1; i <= size; ++i){
        bit[i] = 0;
    }

    long long formula = (((size * (size + 1)) % primo) * inverso( 2)) % primo;

    long long szs(0);
    for(int i = 1; i <= size; ++i){
        szs = (szs + ( size - (i - 1) ) * i * ( i - 1 )) % primo;
    }
    szs = (szs * inverso(2)) % primo;

    // printf("%lld\n", szs);
    long long numerador =  (( formula * inversoes( bit ) ) % primo);
    // printf("%lld\n", numerador);
    numerador = ( numerador +( ((primo-2) * invsub)%primo )) % primo;
    // printf("%lld\n", numerador);
    numerador = (numerador + szs) % primo;
    // printf("%lld\n", numerador);
    long long mdc = inverso(gcd( formula, numerador ));
    formula = (formula * mdc) % primo;
    numerador = (numerador * mdc) % primo;
    // printf("%lld\n", formula);
    // printf("%lld\n", numerador);

    printf("%lld\n", (numerador * inverso(formula)) % primo );
}
