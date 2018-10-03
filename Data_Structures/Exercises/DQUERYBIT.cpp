#include<bits/stdc++.h>
using namespace std;

#define MAXN 30005
#define int long long

int v[MAXN];
int bit_v[MAXN];
int last_seen[1000001];

int query( int index ){
    int ans(0);
    // index -= index & (-index)
    // index menos o bit menos significativo
    for(index++ ; index > 0; index -= index & (-index)){
        ans += bit_v[index];
    }
    return ans;
}

void update( int index, int val ){
      for(index++ ; index <= MAXN; index += index & (-index)){
          bit_v[index] += val;
      }
}

void print( int in, int fim){
    for(int i = in; i <= fim; ++i){
        printf("%lld ", query(i) - query(i-1));
    }printf("\n");
}

main(){
    int N, a, b, Q;
    scanf("%lld", &N);

    for(int i = 0; i < N; ++i){
        scanf("%lld", &v[i]);
        last_seen[v[i]] = -1;
    }

    scanf("%lld", &Q);
    vector<pair<pair<int,int>, int>> qs;
    int ans[Q];
    for(int i = 0; i < Q; ++i){
        scanf("%lld %lld", &a, &b);
        qs.push_back(make_pair(make_pair(a-1,b-1), i));
    }
    sort(qs.begin(), qs.end());

    int l_atual = N;
    for(int i = Q-1; i >= 0; --i){
        while(l_atual > qs[i].first.first){
            l_atual--;

            if(last_seen[v[l_atual]] != -1){
                update(last_seen[v[l_atual]], -1);
            }

            last_seen[v[l_atual]] = l_atual;
            update(l_atual, 1);
        }

        // print(0, N-1);

        ans[qs[i].second] = query(qs[i].first.second) - query(qs[i].first.first-1);
    }
    for(int i = 0; i < Q; ++i){
        printf("%lld\n", ans[i]);
    }






}
