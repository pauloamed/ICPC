#include<bits/stdc++.h>
using namespace std;

#define MAXN 10000010 // linear

// minimum prime factors of numbers. init all 0
int min_prime_fact[MAXN];
vector<int> pr;

int sieve(int n){
  for(int i = 2; i < n; ++i){
    if(min_prime_fact[i] == 0){
      min_prime_fact[i] = i;
      pr.push_back(i);
    }
    for(int j = 0; j < pr.size(); j++){
      if(i * pr[j] > n) break;
      min_prime_fact[i * pr[j]] = pr[j];
      if(pr[j] == min_prime_fact[i]) break;
    }
  }
}

// to be used for multiplicative functions
int count_exp_min_prime_fact[MAXN];
int mob[MAXN];
int phi[MAXN]; // phi multiplacative function / euler totient


// one can use min_prime_fact for factorization
// while(x != 1) x /= min_prime_fact[x]
// with count_exp_... , preprocesses primes p^k can also be used
// for enhancing performance

void sieve(int n){
  phi[1] = 1;
  mob[1] = 1;
  for(int i = 2; i < n; ++i){
    if(min_prime_fact[i] == 0){ // prime!
      phi[i] = i - 1; // def of phi
      mob[i] = -1;
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
        mob[i * pr[j]] = 0;
        // since i and i*pr[j] have the same min count fact (pr[j])
        // (but i has already some pr[j] as factors)
        count_exp_min_prime_fact[i * pr[j]] = count_exp_min_prime_fact[i] + 1;
        break;
      }else{
        // i and pr[j] are coprime. thus, i * pr[j] has only one pr[j] factor
        mob[i * pr[j]] = mob[i] * mob[pr[j]];
        phi[i * pr[j]] = phi[i] * phi[pr[j]];
        count_exp_min_prime_fact[i * pr[j]] = 1;
      }
    }
  }
}

int mult(int x, int n){
  return max(0, n) / x;
}

long long mult_range(int x, int a, int b){
  return mult(x, b) - mult(x, a - 1);
}

int main(){
  sieve(10000010);
  int a, b, c, d; cin >> a >> b >> c >> d;
  long long ans = 0;
  for(int i = 1; i <= max(b,d); ++i){
    ans += mob[i] * mult_range(i, a, b) * mult_range(i, c, d);
  }
  cout << ans << endl;
}
