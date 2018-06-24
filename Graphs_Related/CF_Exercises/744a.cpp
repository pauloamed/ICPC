#include<bits/stdc++.h>
using namespace std;

vector<int> v[1001];
int jatem[1001], vpork[1001];
int pa[1001];

void marcar(int x, int k){
  jatem[x] = k;
  vpork[k]++;

  for(int i = 0; i < v[x].size(); i++){
    if(jatem[v[x][i]] == -1)
        marcar(v[x][i], k);
  }
}

int main(){
  int n,e,k,x,y;

  scanf("%d %d %d", &n, &e, &k);

  //init
  for(int i = 0; i <= n; i++){
    vpork[i] = 0;
    jatem[i] = -1;
  }

  //read
  for(int i = 0; i < k; i++){
    scanf("%d", &x);
    jatem[x] = x;
    v[0].push_back(x);
  }

  //read
  for(int i = 0; i < e; i++){
    scanf("%d %d", &x, &y);
    v[x].push_back(y);
    v[y].push_back(x);
  }


  //arestas e vertices por componente
  int tot_arestas = 0;
  int max_v = 0;
  int v_g = 0;
  for(int i = 0; i < k; i++){
    marcar(v[0][i], v[0][i]);
    v_g += vpork[v[0][i]];
    max_v = max(max_v, vpork[v[0][i]]);
    tot_arestas += (vpork[v[0][i]]*(vpork[v[0][i]]-1))/2;
  }

  tot_arestas -= (max_v*(max_v-1))/2;
  tot_arestas += ((max_v+(n-v_g))*(max_v+(n-v_g)-1))/2;


  printf("%d\n", tot_arestas-e);





}
