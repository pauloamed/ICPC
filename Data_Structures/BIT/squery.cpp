#include<bits/stdc++.h>
using namespace std;

#define MAX 200001

bool jafoi[200011];
int bit[27][MAX];

void update( int letra, int index, long long val ){
      for( ; index <= MAX; index += index & (-index)){
          bit[letra][index] += val;
      }
}

int find(int letra, int val){
    int ret(0);

    // (ret | (1<<i)) msm coisa que (ret + 2^i)

    for(int i = (int) (log2(MAX)); i >= 0; --i){
        if(!((ret|(1<<i) < MAX) && (ret|(1<<i) >= 0))){
            continue;
        }

        if(bit[letra][ret|(1<<i)] <= val){
            ret |= (1<<i);
            val -= bit[letra][ret];
        }
    }

    return ret + 1;
}

int main(){
    string s;
    cin >> s;

    for(int i = 0; i < s.size(); ++i){
        update(int (s[i] - 'a'), i + 1, 1 );
    }

    int n;
    int x;
    scanf("%d", &n);

    char c;
    int letra;
    for(int i = 0; i < n; ++i){
        cin >> x >> c;

        letra = (int)(c - 'a');

        int pos = find(letra, x - 1);

        update(letra, pos, -1);
        jafoi[pos-1] = true;
    }

    for(int i = 0; i < s.size(); ++i){
        if(!jafoi[i]){
            printf("%c", s[i]);
        }
    }printf("\n");


}
