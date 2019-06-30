#include<bits/stdc++.h>
using namespace std;

#define MAXN 100000

vector<int> v[MAXN];
int control[MAXN];

bool hasCycle(int x, int pai){

    control[x] = 2;
    for(int i = 0; i < v[x].size(); ++i){
        printf(">> %d %d\n", v[x][i], control[v[x][i]]);
        if(control[v[x][i]] == 0){
            if(hasCycle(v[x][i], x)) return true;
        }else if(v[x][i] != pai && control[v[x][i]] == 2){
            return true;
        }
    }
    control[x] = 1;

    return false;
}

int main(){
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }

    hasCycle(0, -1)? printf("Has cycle\n") : printf("Has no cycle\n");
}
