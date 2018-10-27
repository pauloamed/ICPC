#include<bits/stdc++.h>
using namespace std;

#define MAXN 200100
#define int long long

int bit_v[2][MAXN];

int query( int qual, int index ){
    int ans(0);
    // index -= index & (-index)
    // index menos o bit menos significativo
    for( ; index > 0; index -= index & (-index)){
        ans += bit_v[qual][index];
    }
    return ans;
}

void update( int qual, int index, int val ){
      for( ; index <= MAXN; index += index & (-index)){
          bit_v[qual][index] += val;
      }
}

main(){
    int n, x;
    cin >> n;

    int temp, ans = 0;

    vector<int> v;
    vector<int> vals;
    for(int i = 0; i < n; ++i){
        cin >> x;
        v.push_back(x);
        vals.push_back(x);
    }

    sort(vals.begin(), vals.end());
    map<int,int> compr;
    // vector<int> id2vals;
    int offset(0);
    for(int i = 0; i < vals.size(); ++i){
        if(i>0 && vals[i] == vals[i-1]){
            offset++;
        }else{
            compr[vals[i]] = i - offset + 1;
            // id2vals.push_back(vals[i]);
        }
    }


    vector<int> anss;
    for(int i = n-1; i >= 0; --i){
        // valor comprimido nao mantem v[i]=v[j]+1
        // nao mantem x*v[i]
        // e nao ta dando certo
        temp = compr[v[i]];
        ans = 0;


        // cout << ans << " ";
        ans += query(0,MAXN) - query(1,MAXN)*v[i];

        ans -= (query(0, temp)-query(0,temp-1)) - (query(1,temp)-query(1,temp-1))*v[i];
        // cout << ans << " ";

        if(compr.count(v[i]-1)){
            ans -= (query(0, temp-1)-query(0,temp-2)) - (query(1,temp-1)-query(1,temp-2))*v[i];
        }

        // cout << ans << " ";

        if(compr.count(v[i]+1)){
            ans -= (query(0, temp+1)-query(0,temp)) - (query(1,temp+1)-query(1,temp))*v[i];;
        }

        anss.push_back(ans);

        update(0, temp, v[i]);
        update(1, temp, 1);
        // cout << ans << endl;
    }

    long double resp = 0;
    for(int i = 0; i < n; ++i){
        resp += anss[i];
    }

    cout.precision(0);
    cout << fixed << resp << endl;
}
