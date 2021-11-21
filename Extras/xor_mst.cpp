// https://codeforces.com/gym/103119/problem/C

#include<bits/stdc++.h>
using namespace std;

#define int long long
#define INF 1e14
#define MAXN 100010


struct Node{
  int size;
  array<int,2> c;
  Node(int _size = 0):
    size(_size), c({-1, -1}){}
};

struct XORTrie{
  vector<Node> nodes;
  // root: nodes[0]
  // todos numeros sao armazenados em nos terminais
  // um no terminal pode manter mais de um numero

  XORTrie(){
    nodes.push_back(Node());
  }

  bool get_bit(int x, int i){
    return (x >> i) & 1;
  }

  void add(int num, int curr_node = 0, int curr_bit = 31){
    nodes[curr_node].size++;
    if(curr_bit == -1) return;

    int b = get_bit(num, curr_bit);
    if(nodes[curr_node].c[b] == -1){
      nodes[curr_node].c[b] = nodes.size();
      nodes.push_back(Node());
    }

    add(num, nodes[curr_node].c[b], curr_bit - 1);
  }

  void rmv(int num, int curr_node = 0, int curr_bit = 31){
    nodes[curr_node].size--;
    if(curr_bit == -1) return;
    int b = get_bit(num, curr_bit);
    rmv(num, nodes[curr_node].c[b], curr_bit - 1);
  }

  int query(int num, int k, int curr_node = 0, int curr_bit = 31){
    if(curr_bit == -1) return 0; // base recursion case

    if(nodes[curr_node].size < k) return INF; // invalid query
    assert(nodes[curr_node].size > 0); // cant enter an empty node

    int b = get_bit(num, curr_bit); // target bit

    // base cases: empty nodes with size 0
    int priority_childs = 0, non_priority_childs = 0;

    // retrieving size values if present
    if(nodes[curr_node].c[b] != -1) 
      priority_childs = nodes[nodes[curr_node].c[b]].size;
    if(nodes[curr_node].c[b^1] != -1) 
      non_priority_childs = nodes[nodes[curr_node].c[b^1]].size;
    

    if(k > priority_childs){ // goes to b^1
      return ((b^1) << curr_bit) + query(
        num, 
        k - priority_childs, 
        nodes[curr_node].c[b^1], 
        curr_bit - 1
      );
    }else{ // goes to b
      return ((b) << curr_bit) + query(
        num, 
        k, 
        nodes[curr_node].c[b], 
        curr_bit - 1
      );
    }
  }

  void dfs(int curr_node = 0, int pad=0){
    for(int i = 0; i < pad; ++i) cout << " ";
    cout << curr_node << " " << nodes[curr_node].size << "\n";
    
    if(nodes[curr_node].c[0] != -1) dfs(nodes[curr_node].c[0], pad + 1);
    if(nodes[curr_node].c[1] != -1) dfs(nodes[curr_node].c[1], pad + 1);
  }
};

vector<int> v;
map<int,int> val2index;
vector<pair<int,int>> edges;

void solve(const vector<int>& curr_indexes, int curr_bit){
  if(curr_indexes.size() == 0) return;
  if(curr_bit == -1){
    // se len(curr_indexes) for maior q 1, ligo
    if(curr_indexes.size() > 1){
      for(int i = 1; i < curr_indexes.size(); ++i){
        edges.push_back({curr_indexes[i - 1], curr_indexes[i]});
      }
    }
    return;
  }
  // particionar os valores no vetor
  vector<int> part[2];
  for(auto idx : curr_indexes) part[(v[idx] >> curr_bit) & 1].push_back(idx);

  if(min(part[0].size(), part[1].size()) > 0){
    XORTrie trie;
    for(auto idx : part[0]) trie.add(v[idx]);
    
    int min_xor = INF;
    int min_idx = -1;
    for(auto idx : part[1]){
      int q = trie.query(v[idx], 1);
      int qxor = q ^ v[idx];

      if(qxor < min_xor){
        min_xor = qxor;
        min_idx = idx;
      }
    }

    int a = min_idx;
    int b = val2index[min_xor ^ v[a]];
    edges.push_back({a, b});
  }


  solve(part[0], curr_bit - 1);
  solve(part[1], curr_bit - 1);
}

vector<int> label;
vector<int> adj[MAXN];

void dfs(int x, int l, int par){
  label[x] = l;
  for(auto y : adj[x]){
    if(y == par) continue;
    dfs(y, l ^ 1, x);
  }
}


int32_t main(){
  cin.sync_with_stdio(false);
  cin.tie(NULL);

  int t; cin >> t;
  while(t--){
    
    int n; cin >> n;
    for(int i = 0; i < n; ++i){
      int x; cin >> x;
      v.push_back(x);
      val2index[x] = i;
      adj[i].clear();
    }

    vector<int> indexes; for(int i = 0; i < n; ++i) indexes.push_back(i);
    solve(indexes, 31);

    for(auto e : edges){
      adj[e.first].push_back(e.second);
      adj[e.second].push_back(e.first);
    }

    label = vector<int>(n);
    dfs(0, 0, -1);

    vector<int> c[2];
    for(int i = 0; i < n; ++i){
      c[label[i]].push_back(i);
    }

    int ans = INF;
    for(int i = 0; i < 2; ++i){
      XORTrie trie;
      for(auto idx : c[i]){
        ans = min(trie.query(v[idx], 1) ^ v[idx], ans);
        trie.add(v[idx]);
      }
    }

    cout << ans << "\n";
    for(int i = 0; i < n; ++i) cout << label[i] + 1; cout << "\n";

    edges.clear();
    v.clear();
    val2index.clear();  
  }
}