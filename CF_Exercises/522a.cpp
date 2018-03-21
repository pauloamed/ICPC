#include<bits/stdc++.h>
using namespace std;

map<string, int> mapa;

string minu(string s){
  string r;
  for(int i = 0; i < s.size(); i++){
    if(s.at(i) >= 'A' && s.at(i) <= 'Z'){
      r.push_back(s.at(i) - ('A' - 'a'));
    }else{
      r.push_back(s.at(i));
    }
  }

  return r;
}

int main(){
  mapa["polycarp"] = 1;

  int n, biggest = 0;
  cin >> n;
  string a,b,c,ma,mc;

  for(int i = 0; i < n; i++){
    cin >> a >> b >> c;
    ma = minu(a);
    mc = minu(c);

    mapa[ma] = mapa[mc] + 1;
    biggest = max(biggest, mapa[ma]);

  }

  cout << biggest << endl;
}
