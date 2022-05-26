#include<bits/stdc++.h>
using namespace std;

typedef long long T; // mudar para o tipo a ser usado

int sgn(T val){
    return val > 0 ? 1 : (val == 0 ? 0 : -1);
}

struct pv{
    T x,y;

    // operacoes binarias
    pv operator+(pv p){ return {x+p.x, y+p.y};} // soma
    pv operator-(pv p){ return {x-p.x, y-p.y};} // subtracao
    pv operator*(T k){ return {x*k, y*k};} // multiplicacao por constante
    pv operator/(T k){ return {x/k, y/k};} // divisao por constante

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

    // orientacao dos pontos na ordem THIS->A->B
    // se ret < 0: sentido horario
    // se ret > 0: sentido anti horario
    // se ret == 0; colineares
    T orient(pv a, pv b){ return (a-(*this)).cross(b-(*this)); }

    // normas (operacoes unarias)
    T sq(){return x*x+y*y;} //
    T norml0(){ return (x!=0)+(y!=0);} // quantos elementos nao nulos
    T norml1(){ return abs(x)+abs(y);} // distancia de manhattan
    double norml2(){ return sqrt(sq());} // norma euclidiana
    T normlinf(){ return max(abs(x),abs(y));} // norma infinita

    // transformacoes
    // rotaciona o vetor em a radianos
    // pv rotate(double a){ return {((double) x)*cos(a) - y*sin(a), (T) x*sin(a) + y*cos(a)}; }
    pv perp(){ return {this->y, -this->x}; } // gira 90 graus no sentido horario

    // dentro de ...
};

bool inAngle(pv a, pv b, pv c, pv p){
    // checa se o ponto ta dentro do angulo def por a,b,c
    if(a.orient(b,c) == 0) printf("COLINEARES\n"); // da ruim se forem colineares
    if(a.orient(b,c) < 0) swap(b,c); // resumir pra um caso
    return (a.orient(b,p) >= 0) && (a.orient(c,p) <= 0); // se ta dentro
}

bool operator <(const pv & l, const pv & r){
    return l.x < r.x || (l.x == r.x && l.y < r.y);
}

bool pointInTriangle(pv a, pv b, pv c, pv point){
    T a1 = abs(a.cross(b, c)); // area of ABC triangle
    // (area of APB) + (area of BPC) + (area of CPA) must be equal to area of ABC
    T a2 = abs(point.cross(a, b)) + abs(point.cross(b, c)) + abs(point.cross(c, a));
    return ((a1 - a2) == 0);
}

bool pointInDisk(pv a, pv b, pv c){
    // checks if point c is inside of minimum enclosing disk from a and b
    if((a == c) || (b == c)) return true;
    return (a-c).dot(b-c) <= 0;
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

    // generates edges of polygon
    vector<pv> seq;
    for(int i = 0; i < n-1; i++) seq.push_back(points[i + 1] - points[0]);
    return seq;
}

// polygon must be clockwise or counter-clockwise oriented
double polygonArea(vector<pv> &v){ // v is the list of edges (use prepare)
	T ans = 0;
	int n = (int)v.size();
	for(int i = 0; i < n; i++){
		ans += v[i].cross(v[(i+1)%n]);
	}
	return ((double) abs(ans))/2.0;
}

bool polygonOrientation(vector<pv> &v){ // v is the list of edges (use prepare)
    return polygonArea(v) > 0;
}

bool polygonIsConvex(vector<pv> &v){
    int state = 0;
    int n = (int) v.size();
    for(int i = 0; i < v.size(); ++i){
        int q = v[i].orient(v[(i+1)%n], v[(i+2)%n]);
        if(state == 0) state = q;
        else if(state != q && q != 0) return false;
    }
    return true;
}

// 0: fora
// 1: borda
// 2: dentro
int pointInConvexPolygon(vector<pv> &seq, pv leftmost, pv point){
    point = point - leftmost;
    int n = (int) seq.size();

    // checking if point is outside of polygon by looking at p_(n-1)p_0p_1 triangle
    if(seq[0].cross(point) != 0 && sgn(seq[0].cross(point)) != sgn(seq[0].cross(seq[n - 1]))) return 0;
    if(seq[n - 1].cross(point) != 0 && sgn(seq[n - 1].cross(point)) != sgn(seq[n - 1].cross(seq[0]))) return 0;
    for(auto x : {0ll, n-1}){
      if(seq[x].cross(point) == 0){
        int a = seq[x].sq();
        int b = point.sq();
        if(b <= a) return 1;
        else return 0;
      }
    }

    // retrieves last (l) non negative cross product (first negative is l + 1)
    // point must be between l and l+1
    int l = 0, r = n - 1;
    while(r - l > 1){
        int mid = (l + r)/2;
        int pos = mid;
        if(seq[pos].cross(point) >= 0) l = mid; // change >= to <= depending on polygon orientation
        else r = mid;
    }

    int pos = l;
    if(pointInSegment(seq[pos], seq[pos + 1], point)) return 1;
    else if(pointInTriangle(seq[pos], seq[pos + 1], {0, 0}, point)) return 2;
    else return 0;
}

vector<pv> graham_scan(vector<pv>& pts){
  int n = pts.size(), pivot_id = 0;
  for(int i = 1; i < n; ++i){
    if(pts[i].y > pts[pivot_id].y) continue;
    else if(pts[i].y < pts[pivot_id].y) pivot_id = i;
    else if(pts[i].x < pts[pivot_id].x) pivot_id = i;
  }

  swap(pts[0], pts[pivot_id]);
  pv pivot = pts[0];
  sort(pts.begin() + 1, pts.end(), [pivot](pv &a, pv &b) -> bool{
    int temp = pivot.orient(a, b);
    if(temp != 0) return temp > 0;
    return (a - pivot).sq() < (b - pivot).sq(); // colinear?
  });

  int i = 0;
  vector<pv> ans; ans.push_back(pivot);
  for(i = 1; ans.size() < 2 && i < n; ++i){
    if(pts[i] != pts[i - 1]) ans.push_back(pts[i]);
  }

  for(; i < n; ++i){
    while(ans.size() >= 2){
      if(ans[ans.size() - 2].orient(pts[i], ans.back()) >= 0) ans.pop_back();
      else break;
    }
    ans.push_back(pts[i]);
  }

  while(ans.size() > 2){
    if(ans[ans.size() - 2].orient(pts[0], ans.back()) >= 0) ans.pop_back();
    else break;
  }
  return ans;
}
