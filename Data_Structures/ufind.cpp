struct DSU{
  int numComponents;
  int sizes[MAXN]; // vetor com tamanhos
  int parents[MAXN]; // vetor com pai de cada no
  stack<pair<int,int>> lastPar, lastSize;
  vector<int> checkpoints;

  DSU(int n){
    checkpoints.push_back(0);
    numComponents = n;
      for(int i = 0; i < n; ++i){
          sizes[i] = 1; // tamanho inicial
          parents[i] = i; // valor padrao: cada um eh seu pai
      }
  }

  int find(int current){
      int newRoot = current; // variavel para guardar nova raiz
      while(newRoot != parents[newRoot]) // enquanto nao encontro no raiz
          newRoot = parents[newRoot]; // subo na arvore
      return newRoot; // retornamo a raiz da arvore
  }

  void onion(int a, int b){
      a = find(a); b = find(b); // unimos uma raiz a outra

      if(a == b) return; // se for a mesma raiz, nao tenho o que unir

      // uniao por tamanho
      if(sizes[a] < sizes[b]) swap(a,b); // quero unir "b" a "a"

      checkpoints.back()++;
      lastSize.push({a, sizes[a]});
      lastPar.push({b, parents[b]});

      sizes[a] += sizes[b]; // atualizando tamanho de "a"
      parents[b] = a; // pai de "b" eh "a"
      numComponents--;
  }

  void check(){
    checkpoints.push_back(0);
  }

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
