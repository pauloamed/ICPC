#include<bits/stdc++.h>
using namespace std;

#define MAXN 1000010

int look_at[MAXN][2];

void preprocess(vector<int> &pat, vector<int> &pi){
  int n = pat.size();

  pi[0] = 0; // inicial eh sempre 0
  int j = 0, i = 1; // iteradores
  while (i < n){ // calcular pra todo elemento no padrao
    // pat[i] == par[j]
    bool ok = true;

    int txt_val = pat[i];
    int pat_val = pat[j];

    for(int burro = 0; burro < 2; ++burro){
      int x = look_at[pat_val][burro];
      if(x == 0) continue;

      int pat_pred_pos = j + x;
      int pat_pred_val = pat[pat_pred_pos];
      
      int txt_pred_pos = i + x;
      int txt_pred_val = pat[txt_pred_pos];

      if(pat_pred_val < pat_val){
        ok &= txt_pred_val < txt_val;
      }else{
        ok &= txt_pred_val > txt_val;
      }
    }


    if(ok){ //
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

int main(){
  cin.tie(NULL)->sync_with_stdio(false);

  int k, n; cin >> k >> n;
  vector<int> v(n), pos(k);
  for(auto &x : pos){
    cin >> x; x--;
  }
  for(auto &x : v) cin >> x;

  vector<int> p(k);
  for(int i = 0; i < k; ++i){
    p[pos[i]] = i;
  }

  {
    set<int> active;
    for(int i = 0; i < k; ++i){
      int x = p[i];

      auto it = active.upper_bound(x);
      // above
      if(it != active.end()){
        look_at[x][0] = pos[*it] - i;
      }else look_at[x][0] = 0;

      // under
      if(it != active.begin()){
        look_at[x][1] = pos[*prev(it)] - i;
      }else look_at[x][1] = 0;

      active.insert(x);
    }
  }


  vector<int> pi(k);
  preprocess(p, pi);

  int pat_i = 0;
  int txt_i = 0;
  

  vector<int> ans;
  while(txt_i < n){
    // tento adicionar v[i] no padrao
    int txt_val = v[txt_i];
    int pat_val = p[pat_i];

    bool ok = true;

    for(int i = 0; i < 2; ++i){
      int x = look_at[pat_val][i];
      if(x == 0) continue;

      int pat_pred_pos = pat_i + x;
      int pat_pred_val = p[pat_pred_pos];
      
      int txt_pred_pos = txt_i + x;
      int txt_pred_val = v[txt_pred_pos];

      if(pat_pred_val < pat_val){
        ok &= txt_pred_val < txt_val;
      }else{
        ok &= txt_pred_val > txt_val;
      }
    }


    if(ok){
      if(pat_i + 1 == k){
        ans.push_back(txt_i - pat_i);
        pat_i = pi[k - 1];
      }else{
        pat_i++;
      }
      txt_i++;
    }else{
      if(pat_i != 0){
        pat_i = pi[pat_i-1];
      }else{ // deu falha com 0, nao tem nada para fazer
        txt_i++;
      }
    }
  }

  cout << ans.size() << "\n";
  for(int i = 0; i < ans.size(); ++i){
    cout << ans[i] + 1 << " ";
  }cout << "\n";

}