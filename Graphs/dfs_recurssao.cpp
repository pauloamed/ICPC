#include<bits/stdc++.h>
using namespace std;

bool visited[100];
vector<int> v[100];
int cont;

void dfs(int x){
  visited[x] = true;

  printf("%d visited vertex: %d\n", cont++,x);

  for(int i = 0; i < v[x].size(); i++){
    if(!visited[v[x][i]])
      dfs(v[x][i]);
  }
}

int main(){
  cont = 1;
  int a,b, V;
  cout << "recursive DFS in a tree\ntype V (number of vertexes), 1 < V <= 100:\n";
  cin >> V;


  cout << "type the V-1 edges (A,B), 0 <= A,B < V\n";
  for(int i = 0; i < V-1; i++){
    cin >> a >> b;
    v[a].push_back(b);
    v[b].push_back(a);
  }

  cout << "type the  source vertex x, 0 <= x < V\n";
  cin >> a;

  dfs(a);

  for(int i = 0; i < V; i++)
    visited[i] = false;
  
  return 0;
}
