struct BIT{
  int n; vector<int> v;
  BIT(int m):n(m + 1), v(vector<int>(m + 1)){}

  int query(int i){ int ans = 0; // neutral
    for(i++; i > 0; i -= i & (-i)){
      ans += v[i];
    }
    return ans;
  }

  void update(int i, int val){
    for(i++; i < n; i += i & (-i)) 
      v[i] += val;
  }
};

/*
 - bit menos significativo de x (bmi(a)) = a & (-a)
 - x eh pai de y se (y + bmi(y) = x )
 - x guarda seu valor somado aos valores dos filhos
 - para resgatar o valor ate x
    - criamos um acumulado que comeca com o valor de [menor descendente de x;x]
    - pulamos para
        - pulamos para o nó de ((menor descendente de x) - 1)
        - sabemos que o nó de ((menor descendente de x) - 1) eh irmao a esq de x
        - o irmao a esq de x pode ser acessado retirando seu bit menos significativo
        - irm_esq_x = x - bmi(x)
*/
int bit[MAXN];
//////////////////////////////////////////////////////////////////////////////////
//              Query numa range e Update num ponto especifico                  //
//////////////////////////////////////////////////////////////////////////////////

int query( int index ){
    int ans(0); // acumulado
    index++; // bit eh 1-indexada, tem q ser feito se index for 0-indexado
    while(index > 0){ // enquanto posso ir pra esquerda
        ans += bit[index]; // atualizando o acumulado
        index -= index & (-index); // indo pro irmao a esquerda
    }
    return ans; // ret acumulado
}

void update( int index, int val ){
    index++; // bit eh 1-indexada
    while(index <= MAXN){ // enquanto eu puder subir na BIT
        bit[index] += val; // atualizando valores dos ancestrais
        index += index & (-index); // subindo pro pai
    }
}

int find(int val){ // funcao que retorna a primeira posicao do acumulado maior que val
    // essa funcao vai tentando ativar os bits de ret enquanto percorre a BIT
    // se um bit eh ligado, eh como se tivesse entrado na subarvore induzida por ele
    // entao val eh atualizado, e o mesmo processo eh realizado para a subarvore atual

    int ret = 0; // indice de retorno
    int i = (int) log2(MAXN); // maior bit ativo possivel
    while(i >= 0){ // enquanto posso ir pra direita nos bits

        int_long? maybe_ret = (ret | (1<<i)); // novo indice se o bit for ativo
        if(maybe_ret >= MAXN){
            i--; continue; // caso ultrapasse o limite no calc do indice
        }

        if(bit[maybe_ret] <= val){ // caso eu possa adicionar esse bit
            ret = maybe_ret; // atualizo o retorno
            val -= bit[ret]; // atualizo o objetivo (val)
        }

        --i; // ando pra direita na bit
    }
    return ret + 1; // RETORNA POSICAO DA BIT, QUE EH 1 INDEXADA
}


int first_zero(){
    int ans = 0;
    if(bit[1] == 0) return 0;
    for(int i = MAXLOG-1; i >= 0; --i){
        int maybe_ans = (ans | (1<<i)); // novo indice se o bit for ativo
        if(maybe_ans >= MAXV) continue; // caso ultrapasse o limite no calc do indice
        if(bit[maybe_ans] == (1 << i)) ans = maybe_ans;
    }
    return ans;
}

//////////////////////////////////////////////////////////////////////////////////
//              Query num ponto especifico e Update numa range                  //
//////////////////////////////////////////////////////////////////////////////////

/*
 - nessa bit, eu marco com +val onde comeca um invervalo (l) e com -val onde termina (r)
    - uma query a esq de (l) nao tem val
    - uma query entre (l) e (r) tem +val e nao tem -val
    - uma query apos (r) tem (+val e -val = 0)
*/


void update(int l, int r, int val){
    if(l > r) return; // intervalo invalido de update

    // formato do intevalo: [l;r]
    r++; // aumento o intervalo em r, pra ficar aberto a direita


    l++; // bit eh 1-indexada
    while(l < MAXN){ // enquanto posso subir
        bit[l] += val; // atualizo os ancestrais (a partir de l, tem mais val)
        l += l & (-l); // subindo pro pai
    }

    r++; // bit eh 1-indexada
    while(r < MAXN){ // enquanto posso subir
        bit[r] -= val; // atualizo os ancenstrais (a partir de r, nao tem esse val)
        r += r & (-r); // subindo pro pai
    }
}

int query(int index){
    int ans(0); // acumulado
    index++; // bit eh 1-indexada
    while(index > 0){ // enquanto posso ir pra esquerda
        ans += bit_v[index]; // atualizo o acumulado
        index -= index & (-index); // ando pra esquerda
    }
    return ans; // ret acumulado
}
