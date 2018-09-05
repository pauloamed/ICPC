#include<bits/stdc++.h>
using namespace std;

#define num int
#define par pair<num,num>
#define _mp make_pair
#define x first
#define y second

num prod_vet(par a, par b){
    return a.x * b.y - b.x * a.y;
}

par menos(par a, par b){
    return _mp(a.x - b.x, a.y - b.y);
}

bool ponto_no_segmento(par ponto, par inicio_seg, par fim_seg){
    bool colineares = prod_vet(menos(fim_seg, inicio_seg), menos(ponto, inicio_seg)) == 0;
    bool dentro_limite_x = ponto.x >= min(inicio_seg.x, fim_seg.x) && ponto.x <= max(inicio_seg.x, fim_seg.x);
    bool dentro_limite_y = ponto.y >= min(inicio_seg.y, fim_seg.y) && ponto.y <= max(inicio_seg.y, fim_seg.y);

    return colineares && dentro_limite_x && dentro_limite_x;
}

bool intersec_segm(par s1p1, par s1p2, par s2p1, par s2p2){
    int d1 = prod_vet(menos(s1p1, s2p1), menos(s2p2, s2p1));
    int d2 = prod_vet(menos(s1p2, s2p1), menos(s2p2, s2p1));
    int d3 = prod_vet(menos(s2p1, s1p1), menos(s1p2, s1p1));
    int d4 = prod_vet(menos(s2p2, s1p1), menos(s1p2, s1p1));

    if(((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
       ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
        return true;
    else if(d1 == 0 && ponto_no_segmento(s1p1, s2p1, s2p2))
        return true;
    else if(d2 == 0 && ponto_no_segmento(s1p2, s2p1, s2p2))
        return true;
    else if(d3 == 0 && ponto_no_segmento(s2p1, s1p1, s1p2))
        return true;
    else if(d4 == 0 && ponto_no_segmento(s2p2, s1p1, s1p2))
        return true;
    else
        return false;
}

int main(){

}
