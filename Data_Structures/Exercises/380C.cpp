#include<bits/stdc++.h>
using namespace std;

#define MAX 1000010

typedef struct no_{
    int l, r, maior;
    no_(int l_=0, int r_=0, int maior_=0):l(l_), r(r_),maior(maior_){}
} no;

string s;
no segt[3*MAX];

no merge(no ql, no qr){
    int deu_certo = min(ql.r, qr.l);
    return no(  qr.l - deu_certo + ql.l,
                qr.r - deu_certo + ql.r,
                ql.maior + qr.maior + (deu_certo*2));
}

no build(int l, int r, int node){
    if(l == r){
        if(s[l] == '(') segt[node] = no(0,1,0);
        else segt[node] = no(1,0,0);
        return segt[node];
    }else{
        int mid = (l + r)/2;
        no ql = build(l, mid, (node<<1)+1);
        no qr = build(mid+1, r, (node<<1)+2);
        return segt[node] = merge(ql,qr);
    }
    // printf("%d %d %d\n", l, r, segt[node]);
}

no query(int l, int r, int node, int lq, int rq){
    // printf("%d %d %d %d\n", l,r,lq,rq);
    if(rq < l || lq > r) return 0;
    else if(l >= lq && r <= rq) return segt[node];
    else{
        int mid = (l + r)/2;
        no ql = query(l, mid, (node<<1)+1, lq, rq);
        no qr = query(mid+1, r, (node<<1)+2, lq, rq);
        return merge(ql,qr);
    }
}

int main(){
    cin >> s;
    int m;
    scanf("%d", &m);
    int a,b;

    build(0,s.size()-1,0);
    for(int i = 0; i < m; ++i){
        scanf("%d %d", &a, &b);
        printf("%d\n", query(0,s.size()-1,0,a-1,b-1).maior);
    }
}
