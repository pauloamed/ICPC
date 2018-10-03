#include<bits/stdc++.h>
using namespace std;

#define MAX 100005

long long bit_v[MAX];
int v[MAX];

long long query( int index ){
    long long ans(0);
    for(; index > 0; index -= index & (-index)){
        ans += bit_v[index];
    }
    return ans;
}

void update( int index, int val ){
      for(; index <= MAX; index += index & (-index)){
          bit_v[index] += val;
      }
}

void reset(){
    for(int i(0); i <= MAX - 1; ++i)
        bit_v[i] = 0;
}

int main(){
    int t;
    cin >> t;

    int n, a, b, k;
    vector<pair<int,int>> temp_v;
    vector<pair<int,int>> compr_v;
    int ans(0);
    long long x;

    for(int o(0); o < t; ++o){
        temp_v.clear();
        compr_v.clear();
        ans = 0;

        cin >> n >> k;

        for(int i(0); i < n; ++i){
            cin >> a >> b;
            temp_v.push_back(make_pair(a, b));
        }

        sort(temp_v.begin(), temp_v.end());

        for( int i(0); i < n; ++i){
            compr_v.push_back(make_pair(temp_v[i].second, i));
        }

        int offset(0);
        sort(compr_v.begin(), compr_v.end());
        for( int i(0); i < n; ++i){
            if(i > 0){
                if(compr_v[i].first == compr_v[i - 1].first){
                    if(temp_v[compr_v[i].second].first == temp_v[compr_v[i - 1].second].first){
                        offset--;
                    }
                }
            }
            v[compr_v[i].second] = i + 1 + offset;
        }

        // for( int i(0); i < n; ++i){
        //     // cout << compr_v[i].first << " " << compr_v[i].second << " / ";
        //     cout << v[i] << " ";
        // }cout << endl;

        int cont(0);
        for(int i(0); i < n; ++i){
            cont++;

            if(i == n - 1){
                x = query(v[i]) * cont;
                if( abs(((n - 1) - x) - x) >= k)
                    ans++;
            }else{
                if(v[i] == v[i + 1]){
                    continue;
                }else{
                    x = query(v[i]) * cont;
                    update(v[i], cont);
                    cont = 0;


                    // cout << ans << endl;
                    if( abs(((n - 1) - x) - x) >= k){
                        // printf(":%d\n", ans);
                        ans++;
                    }
                }
            }
        }

        cout << ans << endl;
        reset();
    }
}
