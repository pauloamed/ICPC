#include<bits/stdc++.h>
using namespace std;

#define MAXN 100005

long long bit_v[MAXN];

long long query( int index ){
    int ans(0);
    // index -= index & (-index)
    // index menos o bit menos significativo
    for( index++ ; index > 0; index -= index & (-index)){
        ans += bit_v[index];
    }
    return ans;
}

void update( int index, int val ){
      for( index++; index <= MAXN; index += index & (-index)){
          bit_v[index] += val;
      }
}

int main(){
    int n;
    cin >> n;
    int x;
    vector<int> v, vals;
    for(int i(0); i < n; ++i){
        scanf("%d", &x);
        v.push_back(x);
        vals.push_back(x);
    }

    sort(vals.begin(), vals.end());
    map<int,int> compr;
    int offset = 0;
    for(int i = 0; i < vals.size(); ++i){
        if(i>0 && vals[i] == vals[i-1]){
            offset++;
        }else{
            compr[vals[i]] = i - offset;
        }
    }
    for(int i(0); i < n; ++i){
        v[i] = compr[v[i]];
    }

    pair<int,int> conts[n];
    long long temp;
    for(int i = n-1; i >= 0; --i){
        temp = query(v[i]-1);
        if(temp == 0){
            conts[v[i]].second++;
        }else{
            conts[v[i]].first++;
        }
        if(query(v[i])-temp == 0){
            update(v[i],1);
        }
    }


    long long ans = 0;
    long long accu = 0;
    for(int i(0); i < compr.size(); ++i){
        cout << i << " " << conts[i].first << " " << conts[i].second << endl;
        ans += conts[i].second + max(0ll,accu-1ll) * (conts[i].second);
        cout << ans << endl;
        if(conts[i].first > 0){
            accu++;
            ans += conts[i].first + accu * (conts[i].first);
        }
        cout << ans << endl;
    }
    cout << ans << endl;
}
