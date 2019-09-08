// extracted from geeks for geeks
// tests primality of given number
bool millerTest(ll d, ll n) { 
    ll a = 2 + rand() % (n - 4); 
    ll x = power(a, d, n); 
  
    if (x == 1  || x == n-1) 
       return true; 
  
    while (d != n-1) { 
        x = mulmod(x, x, n);
        d *= 2; 
        if (x == 1)      return false; 
        if (x == n-1)    return true; 
    } 
    return false; 
} 

// probabilistic, uses millerTest, use k = 100
// runs in O(k*log^3(n))
// returns true if n is prime
bool isPrime(ll n, int k){
    if (n <= 1 || n == 4)  return false; 
    if (n <= 3) return true; 
	if (n%2 == 0) return false;

    ll d = n - 1; 
    while (d % 2 == 0) d /= 2; 
  
    for (int i = 0; i < k; i++) 
         if (!millerTest(d, n)) return false; 
  
	return true;
}
