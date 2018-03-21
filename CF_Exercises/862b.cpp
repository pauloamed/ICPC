#include<bits/stdc++.h>
using namespace std;

int cont[2];
bool jafoi[100001];
vector<int> v[100001];
void profundidade(int x, int flag){
  cont[flag]++;
  jafoi[x] = true;

  for(int i = 0; i < v[x].size(); i++){
    if(!jafoi[v[x][i]])
      profundidade(v[x][i], (flag+1)%2);
  }

}

int main(){
  int n,a,b;
  cont[0] = 0;
  cont[1] = 0;
  scanf("%d", &n);

  for(int i = 0; i < n-1; i++){
    jafoi[i+1] = false;
    scanf("%d %d", &a, &b);
    v[a].push_back(b);
    v[b].push_back(a);
  }jafoi[n] = false;

  profundidade(1,0);

  long long ok = 1;
  ok *= cont[0];
  ok *= cont[1];
  ok -= n-1;
  printf("%lld\n", ok);
}
