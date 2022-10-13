struct BIT{
  int n; vector<int> v;
  BIT(int m = 0):n(m + 2), v(vector<int>(n)){}

  int query(int i){ int ans = 0;
    for(i++; i > 0; i -= i & (-i))
      ans += v[i];
    return ans;
  }

  void update(int i, int val){
    for(i++; i < n; i += i & (-i)) 
      v[i] += val;
  }
};


  // point query i < l doesnt has val
  // point query l <= i <= r has val
  // point query r < i has val and -val
  // [l;r]
  void range_update(int l, int r, int val){
    update(l, val);
    update(r + 1, -val);
  }

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
