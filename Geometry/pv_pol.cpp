#include<bits/stdc++.h>
using namespace std;

typedef long long T; // mudar para o tipo a ser usado
struct pv{
    T x,y;

    // operacoes binarias
    pv operator+(pv p){ return {x+p.x, y+p.y};} // soma
    pv operator-(pv p){ return {x-p.x, y-p.y};} // subtracao
    pv operator*(T k){ return {x*k, y*k};} // multiplicacao por constante
    T dot(pv v){ return x*v.x + y*v.y;} // produto escalar
    T cross(pv v){return {x*v.y - y*v.x};} // produto vetorial
    // prod vet de pontos
    T cross(pv & a, pv & b) { return (a - *this).cross(b - *this); }

    // relacoes binarias
    bool operator==(pv p){ return (x == p.x) && (y == p.y);} // igualdade / checar se precisa do eps
    bool operator!=(pv p){ return !(*this==p);} // dif

    // angulo
    double angle_pe(pv v){ // angulo usando a definicao de produto escalar
        double cosa = max(min( (double) dot(v) / norml2() / v.norml2(), 1.0), -1.0);
        return acos(cosa);
    }
    double angle_pv(pv v){ // angulo usando a definicao de produto vetorial
        double sena = max(min( (double) cross(v) / norml2() / v.norml2(), 1.0), -1.0);
        return asin(sena);
    }

    // comparacao entre pontos, pra ordenacao

    // orientacao para pontos
    // se ret < 0: sentido horario
    // se ret > 0: sentido anti horario
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
    // pv rotate(double a){ return {((double) x)*cos(a) - y*sin(a), (T) x*sin(a) + y*cos(a)}; }

    // dentro de ...
    bool inAngle(pv a, pv b, pv c, pv p){
        // checa se o ponto ta dentro do angulo def por a,b,c
        if(a.orient(b,c) == 0) printf("COLINEARES\n"); // da ruim se forem colineares
        if(a.orient(b,c) < 0) swap(b,c); // resumir pra um caso
        return (a.orient(b,p) >= 0) && (a.orient(c,p) <= 0); // se ta dentro
    }
};

bool operator <(const pv & l, const pv & r){
    return l.x < r.x || (l.x == r.x && l.y < r.y);
}

// polygon must be clockwise or anti-clockwise oriented
// will return its area
double polygonArea(vector<pv> &v){
	T ans = 0;
	int n = (int)v.size();
	for(int i = 0; i < n; i++){
		ans += v[i].cross(v[(i+1)%n]);
	}
	return ((double) abs(ans))/2.0;
}

// POLAR SORT
// TODO

int sgn(T val){
    return val > 0 ? 1 : (val == 0 ? 0 : -1);
}

bool pointInTriangle(pv a, pv b, pv c, pv point){
    T a1 = abs(a.cross(b, c)); // area of ABC triangle
    // (area of APB) + (area of BPC) + (area of CPA) must be equal to area of ABC
    T a2 = abs(point.cross(a, b)) + abs(point.cross(b, c)) + abs(point.cross(c, a));
    return ((a1 - a2) == 0);
}

vector<pv> prepare(vector<pv> points, pv &lexsmaller){ // add & to points if needed
    int n = (int) points.size();

    // fetching lex smaller point to pos
    int pos = 0;
    for(int i = 1; i < n; i++){
        if(points[i] < points[pos])
            pos = i;
    }

    lexsmaller = points[pos]; // saving lex smaller to leftmost

    // rotate vector point so it starts at pos
    rotate(points.begin(), points.begin() + pos, points.end());

    // all points in polygon become a vector starting at origin
    vector<pv> seq;
    for(int i = 0; i < n-1; i++) seq.push_back(points[i + 1] - points[0]);
    return seq;
}

bool pointInConvexPolygon(vector<pv> &seq, pv leftmost, pv point){
    point = point - leftmost;
    int n = (int) seq.size();

    // checking if point is outside of polygon by looking at p_(n-1)p_0p_1 triangle
    if(seq[0].cross(point) != 0 && sgn(seq[0].cross(point)) != sgn(seq[0].cross(seq[n - 1]))) return false;
    if(seq[n - 1].cross(point) != 0 && sgn(seq[n - 1].cross(point)) != sgn(seq[n - 1].cross(seq[0]))) return false;
    if(seq[0].cross(point) == 0) return seq[0].sq() >= point.sq();

    // retrieves last (l) non negative cross product (first negative is l + 1)
    // point must be between l and l+1
    int l = 0, r = n - 1;
    while(r - l > 1){
        int mid = (l + r)/2;
        int pos = mid;
        if(seq[pos].cross(point) >= 0) l = mid;
        else r = mid;
    }

    int pos = l;
    return pointInTriangle(seq[pos], seq[pos + 1], {0, 0}, point);
}
