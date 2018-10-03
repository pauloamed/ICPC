#include<bits/stdc++.h>
using namespace std;

int bit_v[1000005];

long long query( int index ){
    long long ans(0);
    // index -= index & (-index)
    // index menos o bit menos significativo
    for( index++; index > 0; index -= index & (-index)){
        ans += bit_v[index];
    }
    return ans;
}

void update( int index, int val ){
      for( index++; index <= 1000005; index += index & (-index)){
          bit_v[index] += val;
      }
}

void reset( void ){
    for( int i(0); i <= 1000005; ++i)
        bit_v[i] = 0;
}


int main(){
    int vetor[100001];
    int T, N, MAX;
    cin >> T;
    for( int i(0); i < T; ++i){
        cin >> N;

        MAX = -1;
        for(int j(0); j < N; ++j){
            scanf("%d", &vetor[j]);
            MAX = max(MAX, vetor[j]);
        }

        long long ans(0);
        for(int j(N-1); j >= 0; --j){
            ans += vetor[j] * (query(MAX) - query(vetor[j]));
            update( vetor[j], 1);
            // printf("%lld ", ans);
        }
        // printf("\n");
        cout << ans << endl;

        reset();
    }
}
