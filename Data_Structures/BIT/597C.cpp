#include<bits/stdc++.h>
using namespace std;

long long bit_v[10][100005];
vector<int> v, v_temp;

map<int, long long> mapa;

long long query( int qual, int index ){
    long long ans(0);
    for( ; index > 0; index -= index & (-index)){
        ans += bit_v[qual][index];
    }
    return ans;
}

void update( int qual, int index, long long val ){
      for( ; index <= 100001; index += index & (-index)){
          bit_v[qual][index] += val;
      }
}

long long inversoes( int qual ){
    long long ans(0), temp;

    // printf("---\n");
    for(int i = v.size() - 1; i >= 0; --i){

        temp =  query( qual, 100001) - query( qual, v[i] );
        update( qual, v[i], mapa[v[i]] );

        // printf("%d %lld\n", v[i], temp);

        mapa[v[i]] = temp;

        if( temp != 0 )
            v_temp.push_back(v[i]);

        ans += temp;
    }
    std::reverse(v_temp.begin(), v_temp.end());
    v = v_temp;
    v_temp.clear();

    return ans;
}


int main(){
    int size, x, k;
    scanf("%d %d", &size, &k);
    for(int i = 0; i < size; ++i){
        scanf("%d", &x);
        mapa[x] = 1;
        v.push_back(x);
    }

    if( k == 0 ){
        printf("%d\n", size);
        return 0;
    }else{
        long long ans;
        for(int i(0); i < k; ++i){
            ans = inversoes( i );
        }
        cout << ans << endl;
    }

}
