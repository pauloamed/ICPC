#include<bits/stdc++.h>
using namespace std;

long long mulmod(long long a, long long b, long long mod){ // multiplicacao modular
    // multiplicar (a*b) equivale a sum(a * 2^i * b_i), onde (a*2^i) é representado
    // na linha do meio, b_i na primeira linha, e o passo de sum na ultima linha
    long long ans = 0;
    a %= mod;
    while(b > 0){
        if(b%2) ans = (ans + a) % c;
        a = (a * 2) % c;
        b >>= 1;
    }
    return ans % c;
}


long long fastexp( long long base, int exp){ // recursivo
    if( exp == 0 ) return 1;
    long long ans = fastexp(base, exp/2);
    ans = ans * ans; // ans = mulmod(ans, ans, mod)
    if(exp%2) return ans * base; // mulmod(ans, base, mod)
    else return ans;
}

long long fastexp(long long base, int expo){ // iterativo
    // expo eh visto como sum(2^i * e_i), onde e_i eh o iesimo bit de e
    // queremos base^(expo) = base^(sum(2^i * e_i))
    // base elevada a um somatorio de termos eh um produtorio da base elev. a cada
    // um desses termos: prod(base^((2^i*e_i))) = prod((base^(2^i))^e_i)
    long long ans = 1;
    while(expo > 0){
        if(expo%2) ans = ans * base; // ans = mulmod(ans, base, mod)
        expo >>= 1;
        base = base * base; // base = mulmod(base, base, mod)
    }
    return ans;
}

long long inverso( long long a ){
    // a^(m-1) ≡ 1 (mod m), m primo
    // a^(-1) ≡ a^(m-2) (mod m)
    // o inverso de a eh a^(m-2)
    return fastexp( a, primo - 2 );
}
