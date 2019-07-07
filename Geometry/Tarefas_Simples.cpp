#include<bits/stdc++.h>
using namespace std;

#define num int
#define par pair<num,num>
#define _mp make_pair
#define x first
#define y second

double tamanho(par a){
    return hypot(a.x, b.x);
}

num prod_esc(par a, par b){
    return a.x * b.x + a.y * b.y;
}

num prod_vet(par a, par b){
    return a.x * b.y - b.x * a.y;
}

par menos(par a, par b){
    return _mp(a.x - b.x, a.y - b.y);
}

par mais(par a, par b){
    return _mp(a.x + b.x, a.y + b.y);
}

double dist(par a, par b){
    return hypot(a.x - b.x, a.y - b.y);
}

bool ponto_no_segmento(par ponto, par inicio_seg, par fim_seg){
    bool colineares = prod_vet(menos(fim_seg, inicio_seg), menos(ponto, inicio_seg)) == 0;
    bool dentro_limite_x = ponto.x >= min(inicio_seg.x, fim_seg.x) && ponto.x <= max(inicio_seg.x, fim_seg.x);
    bool dentro_limite_y = ponto.y >= min(inicio_seg.y, fim_seg.y) && ponto.y <= max(inicio_seg.y, fim_seg.y);
}

int main(){
    par a = _mp(1,2);
    par b = _mp(0,0);

    cout << prod_esc(a,b) << endl;
    cout << prod_vet(a,b) << endl;
    cout << dist(a,b) << endl;
}
