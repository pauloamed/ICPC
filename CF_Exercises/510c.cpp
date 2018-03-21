#include<bits/stdc++.h>
using namespace std;

vector<char> ret;
bool temp[27], perm[27];
vector<int> v[27];

bool loop(int x){
  if(temp[x])
    return true;
  if(perm[x])
    return false;

  if(v[x].size() > 0)
    temp[x] = true;
  for(int i = 0 ; i < v[x].size(); i++){
    if(loop(v[x][i]))
      return true;
  }
  temp[x] = false;
  perm[x] = true;
  ret.push_back(x);

  return false;
}

int main(){
  int n;
  scanf("%d", &n);

  for(int i = 0; i < 27; i++){
    perm[i] = false;
    temp[i] = false;

    if(i!=0)
      v[0].push_back(i);
  }

  string s,ls;
  int ils,is;

  cin >> s;
  s.push_back(' ');
  for(int i = 1; i < n; i++){
    ls = s;
    cin >> s;
    s.push_back(' ');
    for(int j = 0; j < s.size() && j < ls.size(); j++){
      if(s.at(j) == ls.at(j))
        continue;
      else{
        ils = ls.at(j)- 'a' +1;
        is = s.at(j) - 'a' +1;

        if(ls.at(j) == ' ')
          ils = 0;
        if(s.at(j) == ' ')
          is = 0;

        v[ils].push_back(is);
        break;
      }
    }
  }

  for(int i = 0; i < 26; i++){
    if(!perm[i]){
      if(loop(i)){
          printf("Impossible\n");
          return 0;
      }
    }
  }

  for(int i = ret.size()-1; i >= 0; i--){
    if(ret[i] != 0)
      printf("%c", ret[i]+'a'-1);
  }
  cout << endl;


  return 0;
}


//
// for(int i = 0; i < 26; i++){
//   printf("%c:", i+'a');
//
//   for(int j = 0; j < v[i].size(); j++){
//     printf(" %c", v[i][j]+'a');
//   }cout << endl;
// }
