ll mulmod(ll a, ll b, ll c){ // multiplicacao modular
    // multiplicar (a*b) equivale a sum(a * 2^i * b_i), onde (a*2^i) é representado
    // na linha do meio, b_i na ultima linha, e o passo de sum na primeira linha
    ll ans = 0;
    a %= c;
    while(b > 0){
        if(b%2) ans = (ans + a) % c;
        a = (a * 2) % c;
        b >>= 1;
    }
    return ans % c;
}

ll power(ll a, ll b, ll p){ // recursivo
	if(b == 0) return 1;
	if(b == 1) return a;
	ll x = mulmod(a, a, p);
	if(b&1) return mulmod(power(x, b/2, p), a, p);
	return power(x, b/2, p)%p;
}

ll fastexp(ll base, int expo){ // iterativo
    // expo eh visto como sum(2^i * e_i), onde e_i eh o iesimo bit de e
    // queremos base^(expo) = base^(sum(2^i * e_i))
    // base elevada a um somatorio de termos eh um produtorio da base elev. a cada
    // um desses termos: prod(base^((2^i*e_i))) = prod((base^(2^i))^e_i)
    ll ans = 1;
    while(expo > 0){
        if(expo%2) ans = ans * base; // ans = mulmod(ans, base, mod)
        expo >>= 1;
        base = base * base; // base = mulmod(base, base, mod)
    }
    return ans;
}

ll inverso( ll a, ll pmod ){
    // a^(m-1) ≡ 1 (mod m), m primo
    // a^(-1) ≡ a^(m-2) (mod m)
    // o inverso de a eh a^(m-2)
    return fastexp( a, pmod - 2 );
}

void foo(){
	r[1] = 1;
for (int i=2; i<m; ++i)
	r[i] = (m - (m/i) * r[m%i] % m) % m;
}

