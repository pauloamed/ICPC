#define MAXN 10000000 // linear

// minimum prime factors of numbers. init all 0
int min_prime_fact[MAXN];
vector<int> pr; // list of prime numbers

// one can use min_prime_fact for factorization
// while(x != 1) x /= min_prime_fact[x]

void sieve(int n){

    for(int i = 2; i <= n; ++i){
        if(min_prime_fact[i] == 0){ // prime!
            min_prime_fact[i] = i; // itself
            pr.push_back(i);
        }
        // for all primes less than or eq i, fill their product by i into min_prime_fact
        for(int j = 0; j < pr.size(); j++){
            if(pr[j] > min_prime_fact[i]) break; //
            if(i * pr[j] > n) break; // out of range
            min_prime_fact[i * pr[j]] = pr[j];
        }
    }
}
