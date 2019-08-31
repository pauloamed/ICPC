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
// TODO

// PONTO NO POLIGONO - CUTTING RAY
// TODO
