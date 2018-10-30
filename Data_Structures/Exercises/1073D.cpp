#include<bits/stdc++.h>
using namespace std;

#define MAXN 300100
#define int long long

int bit_v[MAXN];

int query( int index ){
    int ans(0);
    // index -= index & (-index)
    // index menos o bit menos significativo
    for( index++; index > 0; index -= index & (-index)){
        ans += bit_v[index];
    }
    return ans;
}

void update( int index, int val ){
      for( index++; index < MAXN; index += index & (-index)){
          bit_v[index] += val;
      }
}

int find( int val){
    int ret(0);

    // Acha o ultimo valor q eh igual a VAL
    for(int i = (int) (log2(MAXN)); i >= 0; --i){
        if(!((ret|(1<<i) < MAXN) && (ret|(1<<i) >= 0))){
            continue;
        }

        if(bit_v[ret|(1<<i)] <= val){
            ret |= (1<<i);
            val -= bit_v[ret];
        }
    }

    return ret;
}


main(){
    int n, t;
    cin >> n >> t;

    int v[n];

    for(int i = 0; i < n; ++i){
        scanf("%lld", &v[i]);
        update(i, v[i]);
    }
    int temp, temp2;

    int cont = 0;
    int lojas_ok = n;
    while(lojas_ok > 0){
        while(query(n+1) > t && lojas_ok > 0){
            update(find(t), -v[find(t)]);
            lojas_ok--;
        }
        temp2 = query(n+1);
        if(temp2 == 0) break;
        temp = t / temp2;
        t -= temp * temp2;
        cont += temp * lojas_ok;
    }
    cout << cont << endl;
}
