#include<bits/stdc++.h>
using namespace std;

long long fastexp( long long base, int exp){
    if( exp == 0 ) return 1;

    long long ans = fastexp( base, exp/2);
    ans *= ans;

    if( exp % 2 == 1 ){
        ans *= base;
    }

    return ans;
}

long long expo( long long base, int exp){
    if( exp == 0) return 1;

    return expo( base, exp-1) * base;
}

int main(){
    int a, b;
    scanf("%d %d", &a, &b);
    printf("fast: %lld\n", fastexp(a,b));
    printf("slow: %lld\n", expo(a,b));
}
