#include<bits/stdc++.h>
using namespace std;

int vv_cont;
int v_min[2001];
int v_cont[2001];

int sc;

vector<int> s;
vector<int> v[2001];

void trajan(int x){
  s.push_back(x);
  v_cont[x] = vv_cont++;
  v_min[x] = v_cont[x];

  for(int i = 0; i < v[x].size(); i++){
    if(v_cont[v[x][i]] == -1)
      trajan(v[x][i]);

    v_min[x] = min(v_min[x], v_min[v[x][i]]);
  }

  if(v_min[x] == v_cont[x]){
    sc++;
  }
}

int main(){
    int n,m,a,b,c;

    for(int i = 0; i <= 2000; i++){
      v_min[i] = -1;
      v_cont[i] = -1;
    }

    while(1){
      scanf("%d %d", &n,&m);

      if(n == 0)
        return 0;

      sc = 0;

      for(int i = 0; i < m; i++){
        scanf("%d %d %d", &a,&b,&c);
        v[a].push_back(b);
        if(c == 2)
          v[b].push_back(a);

      }

      int k;
      for(k = 1; k <= n; k++){
        vv_cont = 0;
        if(v_cont[k] == -1){
          if(sc == 0)
            trajan(k);
          else
            break;
        }

        if(k == n)
          k++;
      }

      if(k <= n || sc > 1)
        printf("0\n");
      else
        printf("1\n");



      for(int i = 1; i <= n; i++){
        v_min[i] = -1;
        v_cont[i] = -1;
        v[i].clear();
      }

   }
}
