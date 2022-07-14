// https://codeforces.com/contest/1202/problem/E
#include<bits/stdc++.h>
using namespace std;

// in this implementation, aho is only a trie w/ suffix links, not an automaton with all transtions computed
// usage is similar to KMP (not KMP-automaton)
// 1: add strings // N = sum of theirs lengths, O(N*log(SIGMA))
// 2: compute suffix links // O(N*log(SIGMA))
// 3: process input string T, computing visited nodes // O(|T|*log(SIGMA))
// 4: query suffix link tree and compute whats needed. dont be afraid to use sack // at least O(N)
template<int N>
struct AhoCorasick{
  
  // trie transition, avoiding allocating too much memory and using the alphabet size
  // cost: log(SIGMA), we assume thats negligible.
  // (A, B): goes to B using A
  map<int,int> to[N]; 

  // next node to be added to the trie
  int next_node = 1;
  const int ROOT = 0;

  // marker for accepted nodes (complete string nodes)
  // nodes in which there will be queries in dfs/sack
  int acc[N]; // ATTENTION: may change depending on application

  void add(const string &s){
    int curr = ROOT;
    for(auto c : s){
      if(to[curr].count(c) == 0) curr = to[curr][c] = next_node++;
      else curr = to[curr][c];
    }
    acc[curr]++; // ATTENTION
  }


  // preffix function on trie nodes. suffix_link[x] points to greatest proper prefsufix of x
  int sl[N];
  
  // reversed edges of sl (DFS/sack). note that if, when processing T, we visit a
  // node X in the sl subtree of a accepted node Y, we are on a accepted string position
  vector<int> sl_tree[N]; 

  // similar to calculation of preffix function
  void compute_suffix_links(){ 
    const int P = -1;
    sl[ROOT] = P;
    queue<int> q; q.push(ROOT);
    while(q.size()){
      int x = q.front(); q.pop();
      for(auto [c, child] : to[x]){
        // trying to match a prefsufix, starts with parents suffixlink
        int child_sl = sl[x]; 
        while(child_sl != P){
          if(to[child_sl].count(c)) break;
          else child_sl = sl[child_sl];
        }
        if(child_sl == P){
          // couldnt match a prefsufix+c
          sl[child] = ROOT; 
        }else{
          // found match (prefsufix+c)
          sl[child] = to[child_sl][c]; 
        } 
        
        q.push(child);
        sl_tree[sl[child]].push_back(child);
      }
    }
    sl[ROOT] = ROOT;
  }


  // marker for visited nodes when processing T string
  set<int> vis[N]; // ATTENTION
  void process(string &t){ // ATTENTION (args)
    int curr = ROOT;
    for(int i = 0; i < t.size(); ++i){ char c = t[i];
      while(true){
        if(to[curr].count(c)){ curr = to[curr][c]; break; }
        else if(curr == ROOT) break;
        else curr = sl[curr];
      }
      vis[curr].insert(i); // ATTENTION
    }
  }


  map<int,int> ans;
  void solve(int x, int curr_on = 0){ // ATTENTION
    curr_on += acc[x];
    for(auto y : sl_tree[x]){
      solve(y, curr_on);
    }

    for(auto y : vis[x]){
      ans[y] += curr_on;
    }
  }
};

const int MAXN = 200100;
AhoCorasick<MAXN> aho_end, aho_start;

int main(){
  string s; cin >> s;
  string rs = s; reverse(rs.begin(), rs.end());
  int m = s.size();

  
  int n; cin >> n;
  for(int i = 0; i < n; ++i){
    string t; cin >> t;
    aho_end.add(t);
    reverse(t.begin(), t.end()); aho_start.add(t);
  }

  aho_end.compute_suffix_links();
  aho_start.compute_suffix_links();

  aho_end.process(s);
  aho_start.process(rs);

  aho_end.solve(aho_end.ROOT);
  aho_start.solve(aho_start.ROOT);

  long long ans = 0;
  for(int i = 0; i < m - 1; ++i){
    int orig_pos = i;
    int rev_pos = (m - 1 - (i + 1));
    ans += (1LL * aho_end.ans[orig_pos] * aho_start.ans[rev_pos]);
  }
  cout << ans << endl;
}
