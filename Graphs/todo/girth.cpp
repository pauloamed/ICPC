#include<bits/stdc++.h>
using namespace std;

#define MAXN 1000
#define pii pair<int,int>

vector<int> v[MAXN];
int lvl[MAXN];

int main(){
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; ++i){
        int a, b; cin >> a >> b; a--; b--;
        v[a].push_back(b);
        v[b].push_back(a);
    }

    int ans = MAXN;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            lvl[j] = 0;
        }

        queue<pii> q;
        q.push({i, -1});
        int x, last;
        while(!q.empty()){
            x = q.front().first;
            last = q.front().second;

            q.pop();

            for(int j = 0; j < v[x].size(); ++j){
                if(!lvl[v[x][j]]){
                    lvl[v[x][j]] = lvl[x] + 1;
                    q.push({v[x][j], x});
                }else{
                    if(v[x][j] != last){
                        // printf("::%d %d\n", x, v[x][i]);
                        ans = min(ans, lvl[x] + lvl[v[x][j]] + 1);
                        while(!q.empty()) q.pop();
                        break;
                    }
                }
            }
        }
    }

    cout << ans << endl;

}
