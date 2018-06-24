#include<bits/stdc++.h>
using namespace std;

#define Nmax 100

set<int> folhas;
bool visited[101];
vector<int>v[101];
int qntsv[101];

int main(){
  int n,a,b;
  printf("Tree to Prufer will find P(t), the Prufer sequence correspondent\nto your tree (it's a bijective relation)\n");
  printf("Type v, the number of vertices at your tree\n");
  scanf("%d", &n);

  for(int i = 0; i < n; i++){
    visited[i] = false;
    qntsv[i] = 0;
  }

  printf("Type the n-1 edges\n");
  for(int i = 0; i < n-1; i++){
    scanf("%d %d", &a, &b);
    v[a].push_back(b);
    v[b].push_back(a);
    qntsv[a]++;
    qntsv[b]++;
  }
  for(int i = 0; i < n; i++){
    if(qntsv[i] == 1)
      folhas.insert(i);
  }

  int vt,cont=0;
  set<int> ::iterator it;
  vector<int> seq;

  while(cont < n-2){
    it = folhas.end();
    vt = *(--it);
    folhas.erase(it);
    visited[vt] = true;

    for(int i = 0; i < v[vt].size(); i++){
      if(!visited[v[vt][i]]){
        seq.push_back(v[vt][i]);
        if(--qntsv[v[vt][i]] == 1)
          folhas.insert(v[vt][i]);
      }
    }
    cont++;
  }

  printf("The correspondent sequence to the tree is:\n");
  for(int i = 0; i < n-2; i++){
    printf("%d ", seq[i]);
  }printf("\n");

}
