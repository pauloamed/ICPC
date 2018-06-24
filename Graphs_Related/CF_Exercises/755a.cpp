#include<bits/stdc++.h>
using namespace std;

bool ehprimo[3000];

int main(){

for(int i = 0; i<3000; i++)
  ehprimo[i] = true;
ehprimo[1] = false;

for(int i = 2; i <= 1000; i++){
  for(int j = 2; j <= 1000; j++){
    if(i*j > 3000)
      break;

    ehprimo[i*j] = false;
  }
}

int n;
cin >> n;
for(int i = 1; ; i++){
  if((i*n)+1 >= 3000)
    break;
  if(!ehprimo[(i*n)+1]){
    printf("%d\n", i);
    return 0;
  }
}


return 0;
}
