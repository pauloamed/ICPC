#include<bits/stdc++.h>
using namespace std;

#define MAXN 1000100

int N;
int v[MAXN];
long long fats[MAXN];
long long invs[MAXN];
long long bit_v[MAXN];

int query( int index ){
    int ans(0);
    // index -= index & (-index)
    // index menos o bit menos significativo
    for( ; index > 0; index -= index & (-index)){
        ans += bit_v[index];
    }
    return ans;
}

void update( int index, int val ){
      for( ; index <= MAXN; index += index & (-index)){
          bit_v[index] += val;
      }
}

void reset(){
    for(int i = 0; i < MAXN; ++i){
        bit_v[i] = 0;
    }
}

void fatsc(int N){
    if(N == 1){
        fats[N] = 1;
    }else{
        fatsc(N-1);
        fats[N] = fats[N-1] * N;
    }
}

void invsc(int N){
    if(N == 1){
        invs[N] = 0;
    }else{
        invsc(N-1);
        invs[N] = fats[N-1] * ((N-1)*N)/2 + N * invs[N-1];
    }
}

long long inversoes(){
    long long ans(0);
    for(int i = N; i > 0; i--){
        ans += query(v[i]);
        update( v[i], 1);
    }
    return ans;
}

long long inversoes_subarrays(){
    long long ans(0);
    for(int i = N; i > 0; i--){
        ans += i * query(v[i]);
        update(v[i], (N - i + 1));
    }
    return ans;
}

int main(){
    cin >> N;

    for(int i = 1; i <= N; ++i){
        scanf("%d", &v[i]);
    }

    fatsc(N);
    invsc(N);


    long double denominador = 0;
    for(int i = 1; i <= N; ++i){
        //(N-i+1) com tamanho i
        //(N-i+1)*fats[i] permutacoes com tamanho i
        denominador += (N-i+1)*fats[i];
    }
    denominador *= (N*(N+1))/2;

    long long p = inversoes();
    reset();
    long long ks = inversoes_subarrays();

    cout << p << " " << ks << endl;

    long long numerador = ((N*(N+1))/2) * p - ks;
    for(int i = 1; i <= N; ++i){
        //(N-i+1) com tamanho i
        //invs(i) eh o somatorio dos valores das inversoes em todas permutacoes
        //(N-i+1)*invs(i) eh o somatorio
        numerador += (N-i+1)*invs[i];
        cout << invs[i] << endl;
    }

    cout << numerador << endl;

    cout << numerador / (double) denominador << endl;


}
