#include<bits/stdc++.h>
using namespace std;

int main(){
  stack<int> pilha;
  vector<int> v[100];
  bool visited[100];

  int a,b, V, cont = 1;
  cout << "iterative DFS in a tree\ntype V (number of vertexes), 1 < V <= 100:\n";
  cin >> V;


  cout << "type the V-1 edges (A,B), 0 <= A,B < V\n";
  for(int i = 0; i < V-1; i++){
    cin >> a >> b;
    v[a].push_back(b);
    v[b].push_back(a);
  }

  cout << "type the  source vertex x, 0 <= x < V\n";
  cin >> a;

  //iterative dfs
  pilha.push(a);
  printf("%d visited vertex: %d\n",cont,a);
  visited[a] = true;
  pilha.pop();
  for(int i = 0; i < v[a].size(); i++){
    if(!visited[v[a][i]])
      pilha.push(v[a][i]);
  }
  while(!pilha.empty()){
    b = pilha.top();
    printf("%d visited vertex: %d\n",cont,b);
    visited[b] = true;
    pilha.pop();
    for(int i = 0; i < v[b].size(); i++){
      if(!visited[v[b][i]])
        pilha.push(v[b][i]);
    }
  }

  return 0;
}
