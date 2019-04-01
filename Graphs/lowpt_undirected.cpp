#include<bits/stdc++.h>
using namespace std;

#define MAXN 100000

vector<int> v[MAXN];

int lowpt[MAXN];
int lvl[MAXN];

vector<int> temp;

void dfs(int x, int last){
    temp.push_back(x);
    lvl[x] = lvl[last] + 1;
    lowpt[x] = x;
    for(int i = 0; i < v[x].size(); ++i){
        if(lvl[v[x][i]] == 0){
            dfs(v[x][i], x);
            // ve se o lowpt de algum filho eh bom
            if(lvl[lowpt[v[x][i]]] < lvl[lowpt[x]]){
                lowpt[x] = lowpt[v[x][i]];
            }

            if(lowpt[v[x][i]] == v[x][i] || lowpt[v[x][i]] == x){
                printf("Mais uma comp conexa\n");
                while(true){
                    printf("%d ", temp.back());
                    if(temp.back() == x) break;
                    temp.pop_back();
                }
                printf("\n");
            }
        // aresta de retorno, ver se eh melhor que o lowpt dos filhos
        }else if(lvl[v[x][i]] < lvl[lowpt[x]]){
                lowpt[x] = v[x][i];
        }
    }
}

int main(){
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; ++i){
        // 1 indexado
        int a, b; cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }

    dfs(1, 0);

}
