#define MAXN 10000000 // linear

// minimum prime factors of numbers. init all 0
int min_prime_fact[MAXN];

// to be used for multiplicative functions
// such functions f(n) = f(a)f(b) when gcd(a,b)=1 (a.k.a coprimes)
// the behaviour of these functions for p^k is their singularity
// once one defines f(p^k), the factorization of n = p^k*q^l*...
// yields f(n) = f(p^k)*f(q^l)*..., since all primes are coprimes
int count_exp_min_prime_fact[MAXN];


int phi[MAXN]; // phi multiplacative function / euler totient

vector<int> pr; // list of prime numbers

// one can use min_prime_fact for factorization
// while(x != 1) x /= min_prime_fact[x]
// with count_exp_... , preprocesses primes p^k can also be used
// for enhancing performance

void sieve(int n){
    phi[1] = 1;
    for(int i = 2; i <= n; ++i){
        if(min_prime_fact[i] == 0){ // prime!
            phi[i] = i - 1; // def of phi
            min_prime_fact[i] = i; // itself
            count_exp_min_prime_fact[i] = 1; // itself
            pr.push_back(i);
        }
        // for all primes less than or eq i, fill their product by i into min_prime_fact
        for(int j = 0; j < pr.size(); j++){
            if(i * pr[j] > n) break; // out of range
            min_prime_fact[i * pr[j]] = pr[j];
            if(pr[j] == min_prime_fact[i]){
              phi[i * pr[j]] = phi[i] * pr[j];

              // since i and i*pr[j] have the same min count fact (pr[j])
              // (but i has already some pr[j] as factors)
              count_exp_min_prime_fact[i * pr[j]] = count_exp_min_prime_fact[i] + 1;
              break;
            }else{
              // i and pr[j] are coprime. thus, i * pr[j] has only one pr[j] factor
              count_exp_min_prime_fact[i * pr[j]] = 1;
              phi[i * pr[j]] = phi[i] * phi[pr[j]];
            }
        }
    }
}
