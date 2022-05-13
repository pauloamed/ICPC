#include<bits/stdc++.h>
using namespace std;

#define MAXN 100010

struct DSU{
  int sizes[MAXN];
  int parents[MAXN];
  
  int numComponents;
  stack<pair<int,int>> lastPar, lastSize;
  vector<int> checkpoints;

  DSU(int n){
    for(int i = 0; i < n; ++i){
      sizes[i] = 1;
      parents[i] = i;
    }
    checkpoints.push_back(0);
    numComponents = n;
  }

  int find(int current){
    int newRoot = current;
    while(newRoot != parents[newRoot]) newRoot = parents[newRoot];

    // rmv if using rollback
    int next;
    while(parents[current] != newRoot){
      next = parents[current];
      parents[current] = newRoot;
    }
    return newRoot;
  }

  void onion(int a, int b){
    a = find(a); b = find(b);
    if(a == b) return;
    if(sizes[a] < sizes[b]) swap(a,b);

    checkpoints.back()++;
    lastSize.push({a, sizes[a]});
    lastPar.push({b, parents[b]});
    numComponents--;

    sizes[a] += sizes[b];
    parents[b] = a;
  }

  void check(){ checkpoints.push_back(0); }

  void rollback(){
    int x = checkpoints.back();
    numComponents += x;
    while (x--) {
      sizes[lastSize.top().first] = lastSize.top().second; lastSize.pop();
      parents[lastPar.top().first] = lastPar.top().second; lastPar.pop();
    }
    checkpoints.pop_back();
  }
};
