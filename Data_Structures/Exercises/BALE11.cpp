#include<bits/stdc++.h>
using namespace std;

int bit_v[100001];

int v[100001];

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
      for( ; index <= 100000; index += index & (-index)){
          bit_v[index] += val;
      }
}

int main(){
    int N;
    cin >> N;

    for(int i(0); i < N; ++i){
        scanf("%d", &v[i]);
    }

    long long ans(0);
    for(int i(N); i > 0; --i){
        ans += query(v[i - 1]);
        update(v[i - 1], 1);
    }
    cout << ans << endl;
}
