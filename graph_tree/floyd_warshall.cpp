#include<bits/stdc++.h>
using namespace std;

#define MAXN 100

/*
Floyd warshall - Caminho minimo de todos pra todos em O(n^3)

*/

void floydwarshall(size_t n){
    // caminhos de i ate j, passando por k, tentam ser atualizados
    for (size_t k = 0; k < n; k++){
        for (size_t i = 0; i < n; i++){
            for (size_t j = 0; j < n; j++){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

bool v[MAXN][MAXN];

/*
Warshall - Fechamento transitivo em O(n^3)
*/

void warshall(int n){
  for(int i = 0; i < n; ++i){ // i ta no meio
    for(int j = 0; j < n; ++j){ // j eh o inicio
      for(int k = 0; k < n; ++k){ // k eh o final
         // se j->i e i->k, entao j->k
        to[j][k] |= (to[j][i] && to[i][k]);
      }
    }
  }
}
