#include<bits/stdc++.h>
using namespace std;

#define mod 1000000007

struct matriz{
    long long a11, a12, a21, a22;

    matriz(long long p_a11, long long p_a12, long long p_a21, long long p_a22){
        a11 = p_a11;
        a12 = p_a12;
        a21 = p_a21;
        a22 = p_a22;
    }

    matriz mult_por(matriz b){
        long long a11b11 = (a11 * b.a11) % mod;
        long long a12b21 = (a12 * b.a21) % mod;
        long long a11b12 = (a11 * b.a12) % mod;
        long long a12b22 = (a12 * b.a22) % mod;
        long long a21b11 = (a21 * b.a11) % mod;
        long long a21b12 = (a21 * b.a12) % mod;
        long long a22b21 = (a22 * b.a21) % mod;
        long long a22b22 = (a22 * b.a22) % mod;
        return matriz((a11b11 + a12b21)%mod,
                      (a11b12 + a12b22)%mod,
                      (a21b11 + a22b21)%mod,
                      (a21b12 + a22b22)%mod);
    }
};

matriz fast_expo(matriz base, long long expo){
    matriz ans = matriz(1,0,0,1);
    while(expo > 0){
        if(expo%2) ans = ans.mult_por(base);
        expo >>= 1;
        base = base.mult_por(base);
    }
    return ans;
}

int main(){
    long long x; cin >> x;
    matriz base(1,0,0,1);
    base = fast_expo(base, x);
    cout << base.a11 << endl;
}
