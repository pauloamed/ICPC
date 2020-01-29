#include<bits/stdc++.h>
using namespace std;

/*
pattern search: dada uma string texto T e um padrao P, achar as ocorrencias de P
em T em O(len(T))

prefix func: t[i]: tamanho do maior prefixo proprio que tambem eh sufixo em s[0...i]

se temos que s[i+1] = s[t[i]], temos que t[i+1] = t[i] + 1 (acumulo de acertos)
caso contrario, queremos achar o maior j < t[i] para realizar novamente a comparacao s[i+1] == s[...],
ou seja, queremos achar o maior j < t[i] tal que s[0:j] = s[i-j+1:i]

para isso bastava decrementar o j iterativamente, mas podemos agilizar o processo utilizando
a tabela t[]: sendo k = t[i], temos que s[0:k-1] = s[i-k:i]. ou seja, temos no "comeco" da
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

// criando a tabela com skips
void preprocess(string pat, int t[]){
    t[0] = 0; // inicial eh sempre 0
    int j = 0, i = 1; // iteradores
    while (i < pat.size()){ // calcular pra todo elemento no padrao
        if(pat[i] == pat[j]){ //
            t[i] = ++j; // sucesso!
        }else{ // (pat[i] != pat[j])
            if(j == 0){ // nao tem nenhum match ate agora
                t[i] = 0;
            }else{ // se ja teve algum match
                j = t[j - 1]; // vejo quantos skiparia pro passado, e
                // comparo com a letra logo apos esse skip
                continue; // nao vou andar o i
            }
        }
        i++; // ando o i
    }
}

vector<int> kmp(string pat, string txt){
    int t[pat.size()]; // cria tabela
    preprocess(pat, t); // preprocessamento

    vector<int> ans; // vetor com indices com match

    int pat_i = 0, txt_i = 0; // iteradores para o padrao e o texto
    while (txt_i < txt.size()){ // percorrer todo o texto
        if(pat[pat_i] == txt[txt_i]){ // eh match
            if(pat_i == pat.size()-1){ // eh o ultimo char do pattern
                ans.push_back(txt_i-pat_i); // salvando pos onde o pattern comecou
                pat_i = t[pat.size()-1]; // sei que a string toda da certo, vejo qnt preciso voltar
            }else pat_i++; // so ando, nao eh o ultimo char do pattern
            txt_i++; // ando no texto
        }else{ // nao deu match
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

int main(){
    string pat, txt; cin >> pat >> txt;
    for(auto &a: kmp(pat, txt)) cout << a << " "; cout << endl;
}
