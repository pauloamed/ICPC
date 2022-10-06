#include<bits/stdc++.h>
using namespace std;

vector<int> compute_p(string &s){
  int n = s.size();
  vector<int> p(n, 0);
  int pref = 0, suf = 1;
  while(suf < n){
    if(s[pref] == s[suf]) p[suf] = ++pref;
    else if(pref != 0){ pref = p[pref - 1]; continue; }
    suf++;
  }
  return p;
}

/*
pattern search: dada uma string texto T e um padrao P, achar as ocorrencias de P
em T em O(len(T))

KMP: pode ser usado pra computar qnts vezes uma substr(0...i) se reprete em s

prefix func: t[i]: tamanho do maior prefixo proprio que tambem eh sufixo em s[0...i]

se temos que s[i+1] = s[t[i]], temos que t[i+1] = t[i] + 1 (acumulo de acertos)
caso contrario, queremos achar o maior j < t[i] para realizar novamente a comparacao s[i+1] == s[...],
ou seja, queremos achar o maior j < t[i] tal que s[0:j] = s[i-j+1:i]

para isso bastava decrementar o j iterativamente, mas podemos agilizar o processo utilizando
a tabela t[] (note que mesmo descrementando o j, precisariamos comparar as strings):
sendo k = t[i], temos que s[0:k-1] = s[i-k:i]. ou seja, temos no "comeco" da
string uma substring (prefixo) de tamanho k igual a outra substring (sufixo de s[:i]) de tamanho k

se essa substring S em questao ela mesma tiver um prefixo proprio igual a algum sufixo proprio, o 
tamanho l dessa substring em comum sera o valor j procurado (s[0:l] = s[k-l+1: k] -> s[0:l] = s[i-l+1:i]).

acontece que a comparacao tambem pode falhar para esse valor, e temos entao que ir reduzindo o valor de j
até a comparação dar certo

complexidade:
    i incrementa += 1 no n vezes
    j increvemnta += 1 no max n vezes (nao ate n) mas pode decrementar seu valor (n = 2n)
    
construcao da tabela: O(len(P))
query: O(len(T))
*/

vector<int> kmp(string pat, string txt){
    int t[pat.size()]; // cria tabela
    preprocess(pat, t); // preprocessamento compute_p

    vector<int> ans; // vetor com indices com match

    int pat_i = 0, txt_i = 0;
    while (txt_i < txt.size()){
        if(pat[pat_i] == txt[txt_i]){
            if(pat_i == pat.size()-1){
                ans.push_back(txt_i-pat_i);
                pat_i = t[pat.size()-1];
            }else pat_i++;
            txt_i++;
        }else{
            if(pat_i != 0) pat_i = t[pat_i-1];
            else txt_i++;
        }
    }
    return ans;
}

//cp-algorithms.com
void computeAutomaton(string s, vector<vector<int>>& aut , int pi[]) {
    s += '#';
    int n = s.size();
    aut.assign(n, vector<int>(26, 0)); 
    // estado 0 eh o inicial. estado i eh o estado de sucesso pra o prefixo s[0...i-1]
    aut[0][s[0] - 'a'] = 1; // crio a conexao da primeira letra
    for (int i = 1; i < n; i++) { // para da um dos n estados (1...n-1)
        for (int c = 'a'; c <= 'z'; c++) { // para cada char
            // se deu match, marco que posso ir pro proximo estado
            if(c == s[i]) aut[i][c - 'a'] = i + 1; 
            else aut[i][c - 'a'] = aut[pi[i-1]][c - 'a']; 
            // se nao deu match, considero o estado pi[i-1]. esse estado representa
            // o prefixo P, que pela definicao de pi, é o maior prefixo que eh sufixo
            // de s[0...i-1]. olhando o que esse estado fez quando c apareceu é equivalente
            // a considerar que esse estado atual deu erro e eu reli todo esse sufixo que eh prefixo
            // chegando ao estado pi[i-1]
        }
    }
}
