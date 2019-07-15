#include<bits/stdc++.h>
using namespace std;

// algoritmo para achar subarray contiguo de maior soma
// se for double, use as estruturas na pasta de geometria
int kadane(vector<int> &v){
    // eh uma PD de 1 estado

    int best = INT_MIN; // vai guardar o melhor resultado
    int current = 0; // vai guardar o resultado atual

    for (int i = 0; i < v.size(); i++){ // pra cada elemento
        current += v[i]; // adiciono elemento atual no acumulado
        best = max(best, current); // tento atualizar a melhor resposta
        current = max(current, 0); // se o acumulador eh negativo, desconsidero
    }
    return best; // retorna a melhor
}
