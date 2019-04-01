#include<bits/stdc++.h>
using namespace std;

#define MAXN 1000
#define MAXV 1000000
#define pii pair<int,int>

int parent[MAXN];
vector<pii> v[MAXN];
int key[MAXN];
set<pii> s;

vector<pii> prim(int n){
    vector<pii> ans;
    s.insert({0,0}); key[0] = parent[0] = 0;
    for(int i = 1; i < n; ++i)
        s.insert({MAXV, i});        // nlogn

    int x, y, val;
    while(ans.size() != n-1){ // n

        x = s.begin()->second;
        s.erase(s.find({key[x], x})); // logn

        if(x!=parent[x])
            ans.push_back({x, parent[x]});

        for(int i = 0; i < v[x].size(); ++i){ //n
            y = v[x][i].first;
            val = v[x][i].second;
            auto temp = s.find({key[y], y}); //logn
            if(key[y] > val && temp != s.end()){
                s.erase(temp);
                s.insert({val, y});
                key[y] = val;
                parent[y] = x;
            }
        }
    }
    return ans;
}

int main(){
    int n, m; cin >> n >> m;

    for(int i = 0; i < n; ++i) key[i] = MAXV;

    for(int i = 0; i < m; ++i){
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        v[a].push_back({b, c});
        v[b].push_back({a, c});
    }

    auto ans = prim(n);

    printf("MST:\n");
    for( auto &e : ans){
        printf("%d %d\n", e.first+1, e.second+1);
    }
    printf("\n");


}
