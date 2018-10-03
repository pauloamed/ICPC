#include<bits/stdc++.h>
using namespace std;

#define MAXN 500010
#define int long long

int conts[MAXN];
int bit_v[MAXN];

int invcompr[3*MAXN];
vector<int> vals;

int query( int index ){
    int ans(0);
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


main(){
    int n, q, a, b;
    scanf("%lld", &n);
    int v[n];

    for(int i = 0; i < n; ++i){
        scanf("%lld", &v[i]);
        vals.push_back(v[i]);
    }
    vector<pair<int,int>> qs;
    scanf("%lld", &q);

    for(int i = 0; i < q; ++i){
        scanf("%lld %lld", &a, &b);
        qs.push_back(make_pair(a,b));

        vals.push_back(a);
        vals.push_back(b);
    }

    sort(vals.begin(), vals.end());
    map<int,int> compr;
    int offset = 0;
    for(int i = 0; i < vals.size(); ++i){
        if(i>0 && vals[i] == vals[i-1]){
            offset++;
        }else{
            compr[vals[i]] = i - offset + 1;
            invcompr[i - offset + 1] = vals[i];
        }
    }

    for(int i = 0; i < n; ++i){
        conts[compr[v[i]]]++;
    }
    for(auto it(compr.begin()); it != compr.end(); ++it){
        update(it->second, (query(it->second)-query(it->second-1)) + it->first * conts[it->second]);
    }

    for(int i = 0; i < qs.size(); ++i){
        qs[i].second = compr[qs[i].second];
        qs[i].first = compr[qs[i].first];
    }
    for(int i = 0; i < qs.size(); ++i){
        printf("%lld\n", query(qs[i].second) - query(qs[i].first-1));
    }
}
