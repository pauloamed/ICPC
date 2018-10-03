#include<bits/stdc++.h>
using namespace std;

#define MAXN 2001000

int bit_v[2][MAXN];

int query( int qual, int index ){
    int ans(0);
    // index -= index & (-index)
    // index menos o bit menos significativo
    for( index++; index > 0; index -= index & (-index)){
        ans += bit_v[qual][index];
    }
    return ans;
}

void update( int qual, int index, int val ){
      for( index++; index <= MAXN; index += index & (-index)){
          bit_v[qual][index] += val;
      }
}

int main(){
    int x, y, a, b;
    scanf("%d %d", &x,&y);
    int h, v;
    scanf("%d %d", &h,&v);

    vector<int> vals_p_compr;

    vector<pair<int,int>> hs;
    for(int i(0); i < h; ++i){
        scanf("%d %d", &a,&b);
        hs.push_back(make_pair(a,b));
        vals_p_compr.push_back(b);
    }

    vector<pair<int,int>> vs;
    for(int i(0); i < v; ++i){
        scanf("%d %d", &a,&b);
        vs.push_back(make_pair(a,b));
        vals_p_compr.push_back(b);
    }

    sort(vals_p_compr.begin(), vals_p_compr.end());
    map<int,int> compr;
    int offset = 0;
    for(int i(0); i < vals_p_compr.size(); ++i){
        if(i>0 && vals_p_compr[i] == vals_p_compr[i-1]){
            offset++;
        }else{
            compr[vals_p_compr[i]] = i - offset;
        }
    }

    sort(hs.begin(), hs.end());
    sort(vs.begin(), vs.end());

    long long ans = 1;
    for(int i(h-1); i >= 0; --i){
        // hs[i].first = compr[hs[i].first];
        hs[i].second = compr[hs[i].second];
        ans += query(0,hs[i].second);
        update(0,hs[i].second, 1);
    }
    ans += h;
    for(int i(v-1); i >= 0; --i){
        // vs[i].first = compr[vs[i].first];
        vs[i].second = compr[vs[i].second];
        ans += query(1,vs[i].second);
        update(1,vs[i].second, 1);
    }
    ans += v*(h+1ll);
    cout << ans << endl;

}
