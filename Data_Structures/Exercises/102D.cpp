#include<bits/stdc++.h>
using namespace std;

#define mod 1000000007

int main(){
    int n, m, a, b;
    cin >> n >> m;


    vector<int> vals;
    vals.push_back(n);

    vector<pair<int,int>> paradas;
    bool flag = false;
    for(int i = 0; i < m; ++i){
        cin >> a >> b;
        vals.push_back(a);
        if(a == 0) flag = true;
        vals.push_back(b);

        paradas.push_back({a,b});
    }

    sort(vals.begin(), vals.end());
    int offset = 0;
    map<int,int> compr;
    for(int i = 0; i < vals.size(); ++i){
        if(i>0 && vals[i] == vals[i-1]){
            offset++;
        }else{
            compr[vals[i]] = i - offset;
        }
    }

    vector<int> v[2*m + 10];
    for(int i = 0; i < m; ++i){
        v[compr[paradas[i].second]].push_back(compr[paradas[i].first]);
    }

    n = compr[n];
    long long sum[n+5];
    sum[0] = 0;
    sum[0+1] = (flag)? 1:0;
    for(int i = 0; i <= n; ++i){
        if(i!=0) sum[i+1] = 0;
        for(int j = 0; j < v[i].size(); ++j){
            // cout << sum[i+1] << " " << sum[i] << " " << sum[v[i][j]] << endl;
            sum[i+1] = (sum[i+1] + ((((sum[i] - sum[v[i][j]]) % mod) + mod) % mod)) % mod;
        }
        sum[i+1] = (sum[i+1] + sum[i]) % mod;
    }
    cout << (((sum[n+1]-sum[n])%mod)+mod)%mod << endl;



}
