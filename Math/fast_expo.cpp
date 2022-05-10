// recursive fast_exp
int fastexp(int base, int expo){
	if(expo == 0) return 1;
	else if(expo == 1) return a % MOD;
	int x = (base * base) % MOD;
	if(expo & 1) return (fastexp(x, expo / 2) * base) % MOD;
	return fastexp(x, expo / 2);
}

// expo = SUM(2^i * expo_i), expo_i: ith bit of expo
// base^expo = base^(SUM(2^i * expo_i)) = PROD base^(2^i*expo_i)
// we will iterate through base^(2^i) and use this value only if expo_i is on
int fastexp(int base, int expo){
  int ans = 1; // identity
  while(expo > 0){
    if(expo & 1) ans = ans * base;
    expo >>= 1;
    base = base * base;
  }
  return ans;
}

// a^(m-1) ≡ 1 (mod m), m prime
// a^(-1) ≡ a^(m-2) (mod m)
// a inverse is a^(m-2)
int inverse(int a){
  return fastexp(a, MOD - 2);
}

// compute all modular inverses, m prime
void compute_invs(){
  inv[1] = 1;
  for(int i = 2; i < m; ++i)
    inv[i] = m - (m / i) * inv[m % i] % m;
}

// modular multiplication
// a*b = SUM_i((a * 2^i) * b_i)
// goes through b_i (b bits) while doubling a (a * 2^i)
int mulmod(int a, int b, int c){ 
  a %= c;
  int ans = 0;
  while(b > 0){
    if(b & 1) ans = (ans + a) % c;
    a = (a * 2) % c;
    b >>= 1;
  }
  return ans % c;
}
