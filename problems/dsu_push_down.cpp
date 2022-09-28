#include<bits/stdc++.h>
using namespace std;

#define int long long

#define MAXN 600010
#define MOD 1000000007
#define MAXLOG 20

struct DSU{
  int sizes[MAXN], parents[MAXN];

  DSU(){
    for(int i = 0; i < MAXN; ++i){
      sizes[i] = 1;
      parents[i] = i;
    }
  }

  int find(int current){
      int newRoot = current; // variavel para guardar nova raiz
      while(newRoot != parents[newRoot]) // enquanto nao encontro no raiz
          newRoot = parents[newRoot]; // subo na arvore

      // compressao de caminho (*) REMOVER SE FOR ROLLBACK
      int next; // backup do pai
      while(parents[current] != newRoot){ // enquanto nao acho a nova raiz
          next = parents[current]; // faco o backup do pai
          parents[current] = newRoot; // digo que o pai eh a raiz achada (*)
      }
      return newRoot; // retornamo a raiz da arvore
  }

  void onion(int a, int b){
      a = find(a); b = find(b); // unimos uma raiz a outra

      if(a == b) return; // se for a mesma raiz, nao tenho o que unir

      // uniao por tamanho
      if(sizes[a] < sizes[b]) swap(a,b); // quero unir "b" a "a"

      sizes[a] += sizes[b]; // atualizando tamanho de "a"
      parents[b] = a; // pai de "b" eh "a"
  }

};

DSU dsus[MAXLOG];
vector<int> partitions[MAXN];


int n;
void inline conn_ok_ok(int i, int a, int b){
  dsus[i].onion(a, b);
  dsus[i].onion(a + n, b + n);
}

void inline conn_ok_rev(int i, int a, int b){
  // assert(max(a, b) < n);
  dsus[i].onion(a, b + n);
  dsus[i].onion(a + n, b);
}

int32_t main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  int m; cin >> n >> m;
  string s; cin >> s;

  for(int i = 0 ; i < n; ++i) dsus[0].onion(i, i + n);

  for(int i = 0; i < m; ++i){
    int a, b; cin >> a >> b; a--, b--;
    int mid = (a + b) / 2;

    pair<int,int> l, r;
    if((b - a + 1) & 1){ // intervalo eh impar
      l = {a, mid - 1};
    }else{
      l = {a, mid};
    }
    r = {mid + 1, b};

    int sz = l.second - l.first + 1;

    int pot = (1 << 20);
    int logg = 20;
    while(pot){
      if(pot <= sz){
        {
          int start_left = l.first;
          int start_right = r.second - pot + 1;
          conn_ok_rev(logg, start_left, start_right);
        }
        {
          int start_left = l.second - pot + 1;
          int start_right = r.first;
          conn_ok_rev(logg, start_left, start_right);
        }
        break;
      }
      logg--;
      pot /= 2;
    }
  }

  int pot = (1 << (MAXLOG - 1));
  for(int i = MAXLOG - 1; i > 0; --i){
    int mpot = pot/2;

    for(int j = 0; j < 2 * n; ++j){
      int it_left_block = j;
      int it_right_block = j + mpot;
      if(it_left_block >= n) it_left_block -= n;
      if(it_right_block >= n) it_right_block -= n;

      int leader = dsus[i].find(j);
      int left_block = leader;
      int right_block = leader + mpot;
      if(left_block >= n) left_block -= n;
      if(right_block >= n) right_block -= n;

      bool a = j < n;
      bool b = leader < n;

      if(a ^ b){
        conn_ok_rev(i - 1, left_block, it_right_block);
        conn_ok_rev(i - 1, right_block, it_left_block);
      }else{
        conn_ok_ok(i - 1, left_block, it_left_block);
        conn_ok_ok(i - 1, right_block, it_right_block);
      }
    }

    pot /= 2;
  }

  for(int j = 0; j < 2 * n; ++j){
    partitions[dsus[0].find(j)].push_back(j);
  }

  int ans = 1;
  for(int i = 0; i < n; ++i){
    if(partitions[i].empty()) continue;
    int c[2] = {0, 0};
    for(auto x : partitions[i]){
      if(x >= n) x -= n;
      if(s[x] != '?') c[s[x] - '0']++;
    }
    if(min(c[0], c[1]) > 0){
      cout << 0 << "\n";
      return 0;
    }else if(max(c[0], c[1]) == 0){
      ans *= 2; if(ans >= MOD) ans -= MOD;
    }
  }
  cout << ans << "\n";
}
