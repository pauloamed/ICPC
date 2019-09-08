#include<bits/stdc++.h>
using namespace std;

#define MAXN 10000000
#define K 25

/*
IDEMPOTENCIA: f(f(x)) = f(x)

 - Estrutura estatica
 - Estrutura para responder range queries
 - Numeros podem ser decompostos em somatorios de potencia de dois
    - Logo, intervalos tambem
    - A partir de cada numero, tenho K intervalos comecando (de tamanhos
        correspondentes a 2^i (i \in K))
 - O(NlogN) de memoria
 - O(1) para queries de funcoes idempotentes, O(logN) cc

 - A primeira dimensao corresponde a onde comeca
 - A segunda corresponde ao tamanho do intervalo
*/


///////////////////////////////////////////////////////////////////////////////
//                          PARA FUNCOES NAO IDEMPOTENTES                    //
///////////////////////////////////////////////////////////////////////////////

int st[MAXN][K]; // vetor da estrutura
int v[MAXN]; // vetor com valores

void precalc(size_t n){
    // O(N log N)
    // init st com valores do array
    for(size_t i = 0; i < n; ++i) st[i][0] = v[i];

    // preenchendo restante da st
    for(size_t i = 1; i < K; ++i){ // para cada tam de intervalo
        size_t j = 0; // comeco na pos inicial. para cada posicao.
        size_t interval_size = (1 << i); // tamanho do intervalo def pelo for externo
        while(j + interval_size <= n){ // enquanto o interv. estiver num pos valida
            size_t last_interv = i-1; // recuperando valor de i para o intervalo anterior
            size_t last_invert_size = (1 << (i-1)); // recuperando tam do interv anterior

            // calculo o intervalo atual somando as metades
            // uma comecando em j e outra em j+((2^j)/2)
            st[j][i] = st[j][last_interv] +  st[j + last_invert_size][last_interv]; // OPERACAO
            j++;
        }
    }
}


// QUERY PARA FUNCOES DE OPERACAO NAO IDEMPOTENTES
int query(size_t l, size_t r){
    // O(K) = O(logN)
    // query tbm se baseia fortemente na decomposicao binaria do intervalo
    size_t start = l; // recuperando onde comeca o intervalo
    size_t interv_size = r - l + 1; // recuperando o tamanho do intervalo

    int ret = 0; // var de retorno

    // vou percorrendo as potencias, tentando consumir o intervalo
    for(size_t i = K; i >= 0; i--){
        size_t interv_calc = (1 << j); // recupero o tamanho do intervalo atual

        // se consigo adicionar esse interv calc no tamanho restante
        if(interv_calc <= interv_size){
            ret += st[start][j]; // atualizo o retorno // OPERACAO
            interv_size -= interv_calc; // atualizo qnt falta pra completar o intervalo
            start += interv_calc; // atualizo o ponteiro para inicio do intervalo
        }
    }
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
//                          PARA FUNCOES IDEMPOTENTES                        //
///////////////////////////////////////////////////////////////////////////////

size_t vlog[MAXN+1]; // vetor aux pra precalc do log (query)

void precalc(size_t n){
    vlog[1] = 0; // precalc do log
    for(size_t i = 2; i <= MAXN; i++) vlog[i] = vlog[i/2] + 1; // precalc do log
    // O resto eh a mesma coisa que o precalc das NAO idempotentes, mas muda operacao
}


int query(size_t l, size_t r){
    // O(1)
    size_t interv_size = r - l + 1; // recuperando o tamanho do intervalo
    size_t j = log[interv_size]; // recuperando pot que def o tam do interv.
    // tamanho de intervalo que vai ser considerado ja que o log eh capado
    size_t used_interv_size = (1 << j);
    return min(st[l][j], st[r - used_interv_size + 1][j]); // ok ter sobreposicao IDEMPOTENCIA
}
