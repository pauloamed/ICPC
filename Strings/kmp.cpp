#include<bits/stdc++.h>
using namespace std;

/*
pattern search: dada uma string texto T e um padrao P, achar as ocorrencias de P
em T em O(len(T))

quando é encontrado um erro, a gnt sabe que tudo que veio antes foi um acerto. logo
se os ultimos k acertos forem iguais aos primeiros k acertos, a gnt nao precisa checar
esses k caracteres de novo. e eu consigo ter acesso ao valor k em O(1). assim,
nosso objetivo nao eh ter que voltar toda a string do padrao para comparacao.
pra isso, a gnt cria uma tabela de prefixos, que vai guardar o tamanho do maior
prefixo proprio (pq proprio?) que da match com um sufixo proprio, ambos de uma
substrings que eh um prefixo do padrao. Logo, se uma comparacao falhar no i-esimo
caractere do padrao e eu estiver no j-esimo caractere do texto, eu pulo para o
j+1+pat[i] caractere ao inves de para o j+1

sufixo do que foi comparado (do que esta certo), nao de tudo. se ta certo, eh pq
se eu testasse de novo, iria dar match. logo, eu nao preciso testar de novo, se
eu sei que vai dar match. entao eu vejo o tamanho do maior prefixo que eh tambem
sufixo.

construcao da tabela: O(len(P))
query: O(len(T))

*/

// criando a tabela com skips
void preprocess(string pat, int t[]){
    t[0] = 0; // inicial eh sempre 0
    int j = 0, i = 1; // iteradores
    while (i < pat.size()){ // calcular pra todo elemento no padrao
        if(pat[i] == pat[j]){ //
            t[i] = ++j; // pre incrementa j e pos incrementa i
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

int main(){
    string pat, txt; cin >> pat >> txt;
    for(auto &a: kmp(pat, txt)) cout << a << " "; cout << endl;
}
