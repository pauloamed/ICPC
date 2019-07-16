#include<bits/stdc++.h>
using namespace std;

typedef double T; // mudar para o tipo a ser usado
struct pv{
    T x,y;

    // operacoes binarias
    pv operator+(pv p){ return {x+p.x, y+p.y};} // soma
    pv operator-(pv p){ return {x-p.x, y-p.y};} // subtracao
    pv operator*(T k){ return {p.x*k, p.y*k};} // multiplicacao por constante
    T dot(pv v){ return x*v.x + y*v.y;} // produto escalar
    pv cross(pv v){return {x*v.y - y*v.x};} // produto vetorial

    // relacoes binarias
    bool operator==(pv p){ return (x == p.x) && (y == p.y);} // igualdade / checar se precisa do eps
    bool operator!=(pv p){ return !(*this==p);} // dif

    // angulo
    double angle_pe(pv v){ // angulo usando a definicao de produto escalar
        double cosa = max(min(dot(v) / norml2() / v.norml2(), 1.0), -1.0);
        return acos(cosa);
    }
    double angle_pv(pv v){ // angulo usando a definicao de produto escalar
        double sena = max(min(cross(v) / norml2() / v.norml2(), 1.0), -1.0);
        return asin(cosa);
    }

    // comparacao entre pontos, pra ordenacao

    // orientacao
    // se ret < 0: sentido horario
    // se ret < 0: sentido anti horario
    // se ret == 0; colineares
    T orient(pv a, pv b){ return (a-(*this)).cross(b-(*this)); }

    // normas (operacoes unarias)
    T sq(void){return x*x+y*y;} //
    T norml0(){ return (x!=0)+(y!=0);} // quantos elementos nao nulos
    T norml1(){ return abs(x)+abs(y);} // distancia de manhattan
    double norml2(){ return sqrt(sq());} // norma euclidiana
    T normlinf(){ return max(abs(x),abs(y));} // norma infinita

    // transformacoes
    // rotaciona o vetor em a radianos
    pt rotate(double a){ return {x*cos(a) - y*sin(a), x*sin(a) + y*cos(a)}; }

    // dentro de ...
    bool inAngle(pv a, pv b, pv c){
        // checa se o ponto ta dentro do angulo def por a,b,c
        if(a.orient(b,c) == 0) printf("COLINEARES\n"); // da ruim se forem colineares
        if(a.orient(b,c) < 0) swap(b,c); // resumir pra um caso
        return (a.orient(b,p) >= 0) && (a.orient(c,p) <= 0); // se ta dentro
    }
}


// POLAR SORT
// PONTO NO SEGMENTO
bool ponto_no_segmento(par ponto, par inicio_seg, par fim_seg){
    bool colineares = prod_vet(menos(fim_seg, inicio_seg), menos(ponto, inicio_seg)) == 0;
    bool dentro_limite_x = ponto.x >= min(inicio_seg.x, fim_seg.x) && ponto.x <= max(inicio_seg.x, fim_seg.x);
    bool dentro_limite_y = ponto.y >= min(inicio_seg.y, fim_seg.y) && ponto.y <= max(inicio_seg.y, fim_seg.y);

    return colineares && dentro_limite_x && dentro_limite_y;
}

// INTERSECAO SE SEGMENTOS
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
