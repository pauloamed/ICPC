// #include<bits/stdc++.h>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

int S;

vector<vector<int>> last_pos(30000, vector<int>(30, 0));


void preprocess(vector<int> &pat, vector<int> &pi){
  int n = pat.size();

  for(int i = 1; i < n; ++i){
    last_pos[i] = last_pos[i - 1];
    for(auto &x : last_pos[i]){
      if(x != 0) x -= 1;
    }
    last_pos[i][pat[i - 1]] = -1;
  }

  pi[0] = 0; // inicial eh sempre 0
  int j = 0, i = 1; // iteradores
  while (i < n){ // calcular pra todo elemento no padrao
    // pat[i] == par[j]
    bool ok = true;

    int my_order_in_pattern = pat[j];

    // cout << i << " " << j << " " << pat[i] << " " << pat[j] << " " << my_order_in_pattern << "\n";

    for(int s_i = 1; s_i <= S; s_i++){
      if(last_pos[j][s_i] != 0){
        int pos_s = i + last_pos[j][s_i];
        // cout << "- " << s_i << " " << pos_s << " " << pat[pos_s] << "\n";
        if(s_i < my_order_in_pattern){
          ok &= (pat[pos_s] < pat[i]);
        }else if(s_i == my_order_in_pattern){
          ok &= (pat[pos_s] == pat[i]);
        }else{ // s_i > my_order_in_pattern
          ok &= (pat[pos_s] > pat[i]);
        }
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

bool not_ascending(vector<int> &v){
  int last = -1;
  for(int i = 0; i < v.size(); ++i){
    if(v[i] == -1) continue;
    if(v[i] <= last) return true;
    last = v[i];
  }
  return false;
}


int main(){
  int n, k; cin >> n >> k >> S;
  vector<int> v, p;
  for(int i = 0; i < n; ++i){
    int x; cin >> x; v.push_back(x);
  }  for(int i = 0; i < k; ++i){
    int x; cin >> x; p.push_back(x);
  }

  vector<int> pi(k);
  preprocess(p, pi);

  // for(auto x : pi) cout << x << " "; cout << "\n";

  // pra cada posicao i eu tenho que saber quais valores ja estao ativos
  // quando eu cair nessa posicao, eu desseto todo mundo que eh diferente desses valores
  // quando chega um novo valor, eu tenho encaixar ele

  int pat_i = 0;
  int txt_i = 0;

  vector<int> curr_values(S + 1, -1);

  vector<int> ans;
  while(txt_i < n){
    // tento adicionar v[i] no padrao
    int val = v[txt_i];
    int pat_val = p[pat_i];



    bool ok = true;

    int my_order = p[pat_i];

    // cout << txt_i << " " << pat_i << " " << val << " " << pat_val << " " << my_order << "\n";

    for(int s_i = 1; s_i <= S; s_i++){
      // cout << s_i << " " << last_pos[pat_i][s_i] << ", ";
      if(last_pos[pat_i][s_i] != 0){
        int pos_s = txt_i + last_pos[pat_i][s_i];
        if(s_i < my_order){
          ok &= (v[pos_s] < val);
        }else if(s_i == my_order){
          ok &= (v[pos_s] == val);
        }else{ // s_i > my_order
          ok &= (v[pos_s] > val);
        }
      }
    }
    // cout << ok << "\n";
    // cout << "\n";
    


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
    cout << ans[i] + 1 << "\n";
  }
}