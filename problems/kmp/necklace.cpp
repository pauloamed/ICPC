#include<bits/stdc++.h>
using namespace std;

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

KMP responde, para duas strings A,B
1- tamanho do maior prefixo de A que termina em B[i]
2- tamanho do maior sufixo de A que começa em B[i]: se um sufixo S começa em T[i], esse e sufixos desses acabam em T[i]+len(S)-1
3- maior substring em comum entre A e B
4- maior substring possivelmente rotacionada entre A e B

Pra resolver 1:
- A = abcd, B = xabc
- Monte A#B: abcd#xabc
- A função pi em j=len(A)+i terá o maior prefixo de A#B (prefixo de A) que termina em j (posição i em B)
- Note que não tem vazamento de informação por conta do caracter inválido #

Pra resolver 2:
- A = yabc, B = xabc
- Monte rev(A)#rev(B): cbay#cbax
- A função pi em j=len(A)+i terá o maior prefixo de rev(A)#rev(B) (sufixo de A) que termina em j (posição i em rev(B)) 
- Como está revertido, o sufixo começa na posição espelhada a i

Pre resolver 3:
- A = abcd, B = xabc
- Monte A#B: xabcd#xabc
- Se a maior substring começar em A[0], ela vai ser achada pela função prefixo e por (1)
- Para i : [0;n-1], considere a substring A' = A[i;n-1] para compor A'#B e fazer (1)

Para resolver 4:
- A = xcdabx
- B = oabcdo
- Vamos dizer que a forma "original" da string eh "abcd". Em A ela está "dividida" em "cd"+"ab". 
- Similar em (3), podemos partir A em "xcd" e "abx" (em (3), excluimos o prefixo, aqui consideramos novamente)
- Note que "xcd" tem "cd" como sufixo e "abx" tem "ab" como prefixo.
- Vamos rodar (1) para "abx" e "oabcdo" e (2) para "xcd" e "oabcdo"
- Olhando p_1(i) temos o maior prefixo de "abx" que termina em B[i]
- Olhando p_2(i + 1) temos o maior sufixo de "xcd" que começa em B[i + 1]
- Dessa forma, em i, somando p_1(i)[2] + p_2(i + 1)[2] (= [4]), temos uma string, formada da concatenação desses pedaços ADJACENTES em A ocorrem de forma ADJACENTE e rotationada em B
*/

// criando a tabela com skips
void preprocess(string pat, vector<int> &pi){
  pi[0] = 0; // inicial eh sempre 0
  int j = 0, i = 1; // iteradores
  while (i < pat.size()){ // calcular pra todo elemento no padrao
      if(pat[i] == pat[j]){ //
          pi[i] = ++j; // sucesso!
      }else{ // (pat[i] != pat[j])
          if(j == 0){ // nao tem nenhum match ate agora
              pi[i] = 0;
          }else{ // se ja teve algum match
              j = pi[j - 1]; // vejo quantos skiparia pro passado, e
              // comparo com a letra logo apos esse skip
              continue; // nao vou andar o i
          }
      }
      i++; // ando o i
  }
}

vector<int> solve_pref_occours(string &a, string &b){
  string x = a + "#" + b;
  vector<int> pi(x.size());
  preprocess(x, pi);
  return pi;
}

vector<int> solve_suf_occours(string a, string b){
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  string x = a + "#" + b;
  vector<int> pi(x.size());
  preprocess(x, pi);
  reverse(pi.begin() + a.size() + 1, pi.end());
  return pi;
}

struct Ans{
  int tot_size, size_pref, size_suf, pos_b, pos_a;
};

Ans solve(string pref_a, string suf_a, string t, int split_a){
  // quero achar um sufixo em pref_a
  // quero achar um prefixo em suf_a
  auto a_pi_pref_a = solve_suf_occours(pref_a, t);
  a_pi_pref_a.push_back(0);
  auto b_pi_suf_a = solve_pref_occours(suf_a, t);

  // cout << pref_a << " " << suf_a << " " << t << "\n";

  // cout << "suf do pref ";for(int i = 0; i < a_pi_pref_a.size(); ++i) if(i > pref_a.size()) cout << a_pi_pref_a[i] << " "; cout << "\n";
  // cout << "pref do suf ";for(int i = 0; i < b_pi_suf_a.size(); ++i) if(i > suf_a.size())cout << b_pi_suf_a[i] << " "; cout << "\n";

  Ans ans{-1, -1, -1, -1, -1};
  for(int i = 0; i < t.size(); ++i){
    int pos_a = pref_a.size() + 1 + i;
    int pos_b = suf_a.size() + 1 + i;
    int pts = b_pi_suf_a[pos_b] + a_pi_pref_a[pos_a + 1];

    if(pts > ans.tot_size){
      ans.tot_size = pts;
      ans.size_pref = b_pi_suf_a[pos_b];
      ans.size_suf = a_pi_pref_a[pos_a + 1];
      ans.pos_a = split_a - ans.size_suf;
      ans.pos_b = i - ans.size_pref + 1;
    }

    // cout << i << " " << pos_a << " " << pos_b << " " << b_pi_suf_a[pos_b] << " " << a_pi_pref_a[pos_a + 1] << "\n";
  }
  return ans;
}

int main(){
  string a, b; cin >> a >> b;
  a = "#" + a;

  Ans ans{-1, -1, -1, -1, -1};
  for(int pref_size = 1; pref_size < a.size(); ++pref_size){
    int suf_size = a.size() - pref_size;
    string pref = a.substr(0, pref_size);
    string suf = a.substr(pref_size, suf_size);
    auto x = solve(pref, suf, b, pref_size - 1);
    if(x.tot_size > ans.tot_size) ans = x;
  }

  int n = a.size();
  reverse(a.begin(), a.end());
  for(int pref_size = 0; pref_size < a.size(); ++pref_size){
    int suf_size = a.size() - pref_size;
    string pref = a.substr(0, pref_size);
    string suf = a.substr(pref_size, suf_size);
    auto x = solve(pref, suf, b, pref_size);
    if(x.tot_size > ans.tot_size){
      ans = x;
      ans.pos_a = n - 2 - (ans.pos_a + x.tot_size - 1);
    }
  }
  cout << ans.tot_size << "\n";
  cout << ans.pos_a << " " << ans.pos_b << "\n";
  // cout << ans.second.first << " " << ans.second.second << "\n";
}