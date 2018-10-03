#include<bits/stdc++.h>
using namespace std;

long long size;

long long bit[100001];
long long v[100001];
long long primo = 1000000007;

long long query( int index ){
    long long ans(0);
    for( ; index > 0; index -= index & (-index)){
        ans = (ans + bit[index]) % primo;
    }
    return ans;
}

void update( int index, long long val){
      for( ; index <= size; index += index & (-index)){
          bit[index] = (bit[index] + val) % primo;
      }
}

void reset(){
    for(int i = 0; i < 100001; ++i){
        bit[i] = 0;
    }
}

long long inversoes(){
    long long ans(0);
    for(int i = size; i > 0; i--){
        ans = (ans + query( v[i] )) % primo;
        update( v[i], 1);
    }
    return ans;
}

long long inversoes_subarrays(){
    long long ans(0);
    for(int i = size; i > 0; i--){
        ans = (ans + (i * query( v[i])) % primo) % primo;
        update( v[i], (size - i + 1));
    }
    return ans;
}


long long fastexp( long long base, long long exp){
    if( exp == 0 ) return 1;
    long long ans = fastexp( base, exp/2);
    ans = (ans * ans) % primo;
    if( exp % 2 == 1 ) return (ans * base) % primo;
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

    long long invsub = inversoes_subarrays();
    reset();
    long long invs = inversoes();
    long long totrevs = ((size * (size + 1)) / 2) % primo;

    // Calular a qntd de pares para cada subsegmento
    long long szs(0);

    // Subsegmento de tamanho i
    // Existem size-i+1 segmentos de tamanho i
    // Para cada segmento desse, eles possuem (i*(i-1)) pares com i<j
    for(long long i = 1; i <= size; ++i){
        szs = (szs + (((size-i+1)*(i*(i-1)))%primo)) % primo;
    }
    szs = (szs * inverso(2)) % primo;

    // long long numerador =  ( formula * invs ) % primo;
    // numerador = ( numerador +( ((primo-2) * invsub)%primo )) % primo;
    // numerador = (numerador + szs) % primo;

    long long numerador = 0;
    numerador += ( totrevs * invs ) % primo;
    numerador += (((szs - invsub) % primo) + primo) % primo;
    printf("%lld\n", (numerador * inverso(totrevs)) % primo );
}
