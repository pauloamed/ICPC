// n should be composite, otherwise, it'll loop for ever
// expected to run within O(n^1/4) time complexity
// needs fast_expo.cpp
// returns prime divisor of a composite number n
ll PollardRho(ll n) { 
    srand (time(NULL)); 
    if (n==1) return n; 
    if (n % 2 == 0) return 2; 
    ll x = (rand()%(n-2))+2; 
    ll y = x; 
    ll c = (rand()%(n-1))+1; 
    ll d = 1;   
  
    while (d==1){ 
        x = (power(x, 2, n) + c + n)%n; 
        y = (power(y, 2, n) + c + n)%n; 
        y = (power(y, 2, n) + c + n)%n; 
        d = __gcd(abs(x-y), n); 
        if (d==n) return PollardRho(n); 
    } 
  
    return d; 
}
