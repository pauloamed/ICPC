#include<bits/stdc++.h>
using namespace std;

#define MAX 1000005

long long bit_v[2][MAX];
vector<int> v;
map<int,int> vals;

long long query( int qual, int index ){
    long long ans(0);
    for(; index > 0; index -= index & (-index)){
        ans += bit_v[qual][index];
    }
    return ans;
}

void update( int qual, int index, int val ){
      for(; index <= MAX; index += index & (-index)){
          bit_v[qual][index] += val;
      }
}

int main(){
    int n, x;
    cin >> n;

    vector<pair<int,int>> temp_v;
    for(int i(0); i < n; ++i){
        cin >> x;
        temp_v.push_back(make_pair(x, i));
        v.push_back(x);
    }
    sort(temp_v.begin(), temp_v.end());
    for( int i(0); i < temp_v.size(); ++i){
        v[temp_v[i].second] = i + 1;
        vals[temp_v[i].second] = 1;
    }

    long long temp;
    long long ans;
    for(int k(0); k < 2; ++k){
        ans = 0;
        for(int i(n-1); i >= 0; --i){
            // if( vals[v[i]] == 0 )
            //     continue;

            temp = query(k, v[i]);
            update(k, v[i], vals[v[i]]);
            vals[v[i]] = temp;

            ans += temp;
            // cout << temp << " ";
        }
        // printf("\n");
    }

    cout << ans << endl;
}
