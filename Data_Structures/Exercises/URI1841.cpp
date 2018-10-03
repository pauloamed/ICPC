#include<bits/stdc++.h>
using namespace std;

#define MAXN 100100
#define PRIMO 1000000007
#define int long long

int bit_v[MAXN];

long long fastexp( long long base, int exp){
    if( exp == 0 ) return 1;
    long long ans = fastexp( base, exp/2);
    ans = (ans * ans) % PRIMO;
    if( exp % 2 == 1 ) return (ans * base) % PRIMO;
    else return ans;
}

long long inverso( long long a ){
    return fastexp( a, PRIMO - 2 );
}

int tmod( int x ){
    return ((x % PRIMO) + PRIMO) % PRIMO;
}

int query( int index ){
    int ans(1);
    for( ; index > 0; index -= index & (-index)){
        ans = tmod(bit_v[index] * ans);
    }
    return ans;
}

void update( int index, int val ){
      for( ; index <= MAXN; index += index & (-index)){
          bit_v[index] = tmod(bit_v[index] * val);
      }
}

void set1(){
    for(int i = 0; i < MAXN - 1; ++i)
        bit_v[i] = 1;
}


main(){
    set1();
    int N, p, temp, temp2;
    vector<int> ps, vals;
    scanf("%lld", &N);

    temp = N;
    p = 2;
    while(temp > 1 && p <= sqrt(N) + 1){
        while(temp % p == 0){
            // cout << p << endl;
            ps.push_back(p);
            vals.push_back(p);

            temp /= p;
        }
        p++;
    }

    // cout << query(N) << endl;
    int cont = 0;
    while(scanf("%lld", &p) == 1){
        cont++;
        ps.push_back(p);
        vals.push_back(p);
    }

    sort(vals.begin(), vals.end());
    map<int, int> compr;
    int offset = 0;
    for(int i = 0; i < vals.size(); ++i){
        if(i > 0 && vals[i] == vals[i-1]){
            offset++;
        }else{
            compr[vals[i]] = i - offset + 1;
        }
    }

    for(int i = 0; i < ps.size(); ++i){
        ps[i] = compr[ps[i]];

        temp = query(tmod(ps[i]-1));

        if(i >= ps.size()-cont){
             printf("%lld\n", temp);
        }

        temp = tmod(query(ps[i])*inverso(temp));

        update(ps[i], inverso(temp));
        update(ps[i], tmod(temp+1));
    }
}
