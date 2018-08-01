// a^(m-1) ≡ 1 (mod m), m primo
// a^(-1) ≡ a^(m-2) (mod m)

// o inverso de a eh a^(m-2), m primo

#include<bits/stdc++.h>
using namespace std;

long long primo;

long long fastexp( long long base, int exp){
    if( exp == 0 ) return 1;

    long long ans = fastexp( base, exp/2);
    ans = (ans * ans) % primo;

    if( exp % 2 == 1 ){
        ans = (ans * base) % primo;
    }
    return ans;
}

long long inverso( long long a ){
    return fastexp( a, primo - 2 );
}

int main(){
    int a;
    scanf("%lld %d", &primo, &a);
    printf("%lld\n", inverso(a));
}
