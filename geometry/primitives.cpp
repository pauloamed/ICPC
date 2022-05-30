#include<bits/stdc++.h>
using namespace std;

#define deb(...) logger(#__VA_ARGS__, __VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values) {
    cout << vars << " = ";
    string delim = "";
    (..., (cout << delim << values, delim = ", "));
    cout<<endl;
}

#define T double
#define EPS 1e-7
#define INF 1e18

int sgn(T val){
  return val > 0 ? 1 : (val == 0 ? 0 : -1);
}

bool eq(T a, T b, T eps=0) {
	return abs(a - b) <= eps;
}

bool is_int(T a){
  return eq(a, (long long) a, EPS);
}

void shuffle(vector<pv> &v, int k){
	for(int i = k-1; i >= 1; i--){
		swap(v[i], v[rand()%i]);
	}
}

// point or vector
struct pv{
  T x,y;
  pv(T _x=0, T _y=0):x(_x),y(_y){}

  pv operator+(pv p){ return {x+p.x, y+p.y};}
  pv operator-(pv p){ return {x-p.x, y-p.y};}
  pv operator*(T k){ return {x*k, y*k};}
  pv operator/(T k){ return {x/k, y/k};}

  T dot(pv v){ return x*v.x + y*v.y;}
  T cross(pv v){return {x*v.y - y*v.x};}
  T cross(pv & a, pv & b) { return (a - *this).cross(b - *this); }

  bool operator==(pv &p){ return eq(x, p.x, EPS) && eq(y, p.y, EPS);}

  bool operator<(const pv &p) const{
    if(!eq(x, p.x, EPS)) return x < p.x;
    else if(!eq(y, p.y, EPS)) return y < p.y;
    else return false;
  }

  // orientation of THIS->A->B
  // <0: clockwise
  // =0: colinear
  // >0: ccw
  T orient(pv a, pv b){ 
    return (a-(*this)).cross(b-(*this)); 
  }

  T sq(){return x*x+y*y;} //
  T norml2(){ return sqrt(sq());}

  // pv rotate(double a){ return {((double) x)*cos(a) - y*sin(a), (T) x*sin(a) + y*cos(a)}; }
  pv perp(){ return {this->y, -this->x}; }
};

struct line{
  // line eq: ax + by = c
  // direction vector (b, -a) and a scalar c
  pv v; T c;
  pv pt;

  bool operator==(line &l){
    if(v.cross(l.v) == 0){
      T c_prop = c / l.c;
      return (l.v * c_prop) == v;
    }return false;
  }

  // from dir vec and c
  line(pv _v, T _c):v(_v), c(_c){
    if(v.y == 0) pt = {0, c / -v.x}; // horizontal line
    else pt = {c / v.y, 0};
  }


  // from 2 dif points
  line(pv a, pv b):v(a-b), c(a.cross(b)), pt(b){} 

  // +: at left; 0: on; -: at right
  T side(pv p){ return v.cross(p) - c;}

  // line->point dist
  T dist(pv p){ return abs(side(p))/abs(v.norml2()); }

  // line->line dist
  T dist(line l){
    pv _;
    if(inter(l, _)) return 0;
    else if(v.y == 0) return fabs(c / v.x - l.c / l.v.x);
    else return l.dist(pv{-c / v.y, 0});
  }

  // 0: dont intersect
  // 1: intersect at one point
  // 2: intersect at infinite points (same line)
  int inter(line l, pv &out) {
    if(*this==l) return 2;
    T d = v.cross(l.v);
    if (d == 0) return 0;
    out = (l.v*c - v*l.c) / d;
    return 1;
  }

  // line->point dist squared
  T sq_dist(pv p){ return (side(p)*side(p)) / v.sq(); }

  // perpendicular line from *this that contains point p
  line perp_line_on_point(pv p){ return line(p, this->v.perp()); } 

  // point ortogonal projection
  pv ort_proj(pv p){ return p - ((v.perp() * side(p))/ v.sq()); } 

  // point reflection
  pv refl(pv p){ return (p - (this->v.perp() * 2 * side(p))) / v.sq(); }

  pv get_big(T s){ return pt + v * s; }

  // cmp func for sorting points (projections) through line
  // points dont need to lie on the line
  bool cmp_proj(pv a, pv b){ 
    return v.dot(a) < v.dot(b); 
  }
};

struct circle{
	pv c; T r;
	inline bool contains(pv p) { return (p - this->c).norml2() <= r; }

	circle(pv a, pv b) : 
		c({(a.x+b.x)/2.0, (a.y+b.y)/2.0}), 
		r((a-b).norml2()/2.0) {}
		
	circle(pv a, pv b, pv c) : c({0,0}), r(0) {
		
		double x12 = a.x - b.x; 
		double x13 = a.x - c.x; 
	  
		double y12 = a.y - b.y; 
		double y13 = a.y - c.y; 
	  
		double y31 = c.y - a.y; 
		double y21 = b.y - a.y; 
	  
		double x31 = c.x - a.x; 
		double x21 = b.x - a.x; 
	  
		double sx13 = a.x*a.x - c.x*c.x;
		double sy13 = a.y*a.y - c.y*c.y;
	  
		double sx21 = b.x*b.x - a.x*a.x; 
		double sy21 = b.y*b.y - a.y*a.y;
	  
		double f = ((sx13) * (x12) 
		         + (sy13) * (x12) 
		         + (sx21) * (x13) 
		         + (sy21) * (x13)) 
		        / (2 * ((y31) * (x12) - (y21) * (x13))); 

		double g = ((sx13) * (y12) 
		         + (sy13) * (y12) 
		         + (sx21) * (y13) 
		         + (sy21) * (y13)) 
		        / (2 * ((x31) * (y12) - (x21) * (y13))); 
	  
		double h = -g; 
		double k = -f; 
    this->c = {h, k};
    this->r = (a - pv{h, k}).norml2();
	}
};

// // angulo
// double angle_pe(pv v){ // angulo usando a definicao de produto escalar
//     double cosa = max(min( (double) dot(v) / norml2() / v.norml2(), 1.0), -1.0);
//     return acos(cosa);
// }
// double angle_pv(pv v){ // angulo usando a definicao de produto vetorial
//     double sena = max(min( (double) cross(v) / norml2() / v.norml2(), 1.0), -1.0);
//     return asin(sena);
// }


////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////                  INSIDE                  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

// p inside A^BC angle
bool in_angle(pv a, pv b, pv c, pv p){
  if(a.orient(b,c) == 0) return false; // ATTENTION
  if(a.orient(b,c) < 0) swap(b,c);
  return (a.orient(b,p) >= 0) && (a.orient(c,p) <= 0);
}

// point in ABC triangle
// (area of APB) + (area of BPC) + (area of CPA) must be equal to area of ABC
bool point_in_tri(pv a, pv b, pv c, pv point){
  T a1 = abs(a.cross(b, c));
  T a2 = abs(point.cross(a, b)) + abs(point.cross(b, c)) + abs(point.cross(c, a));
  return eq(a1, a2, EPS);
}

// checks if point p is inside of minimum enclosing disk from a and b
bool point_in_disk(pv a, pv b, pv p){
  if((a == p) || (b == p)) return true;
  return (a-p).dot(b-p) <= 0;
}

// point p is in AB segment
bool point_in_seg(pv sa, pv sb, pv p){
  return sa.orient(sb,p) == 0 && point_in_disk(sa, sb, p);
}

// point p is in AB ray
bool point_in_ray(pv ra, pv rb, pv p){
  if(ra == rb) return (p == ra);
  else{
    line r(rb, ra);
    return (r.cmp_proj(ra, p) && r.side(p) == 0);
  }
}

bool seg_in_seg(pv s1a, pv s1b, pv s2a, pv s2b, pv &inter){
  T ori_s1a_s2 = s2a.orient(s2b, s1a);
  T ori_s1b_s2 = s2a.orient(s2b, s1b);

  T ori_s2a_s1 = s1a.orient(s1b, s2a);
  T ori_s2b_s1 = s1a.orient(s1b, s2b);

  // points of s1 are on dif sides from s2
  // points of s2 are on dif sides from s1
  if(ori_s1a_s2 * ori_s1b_s2 < 0 && ori_s2a_s1 * ori_s2b_s1 < 0){
    inter = ((s1a * ori_s1b_s2) - (s1b * ori_s1a_s2)) / (ori_s1b_s2 - ori_s1a_s2); // overflow
    return true;
  }
  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////                  INTERSECITON                  ////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

/*
intersection can be:
- empty: {}
- single point: {x}
- a segment: {x, y}
*/
vector<pv> seg_seg_inter(pv s1a, pv s1b, pv s2a, pv s2b){
  pv inter;
  if(seg_in_seg(s1a, s1b, s2a, s2b, inter)) return {inter};

  vector<pv> ret;
  if(point_in_seg(s1a, s1b, s2a)) ret.push_back(s2a);
  if(point_in_seg(s1a, s1b, s2b)) ret.push_back(s2b);
  if(point_in_seg(s2a, s2b, s1a)) ret.push_back(s1a);
  if(point_in_seg(s2a, s2b, s1b)) ret.push_back(s1b);

  sort(ret.begin(), ret.end());
  ret.resize(unique(ret.begin(), ret.end()) - ret.begin());

  return ret;
}

/*
intersection can be:
- empty: {}
- single point: {x}
- a segment: {x, y}
*/
vector<pv> line_seg_inter(line l, pv sa, pv sb){
  if(sa == sb){
    if(l.side(sa) == 0) return {sa};
  }else if(l.side(sa) == 0 && l.side(sb) == 0){
    return {sa, sb};
  }else{
    line s(sb, sa);
    pv si;
    if(l.inter(s, si) && s.cmp_proj(sa, si) && s.cmp_proj(si, sb)){
      return {si};
    }
  }
  return {};
}

bool line_ray_inter(line l, pv ra, pv rb, pv &inter){
  if(ra == rb){
    if(l.side(ra) == 0){ inter = ra; return true; }
    else return false;
  }else{
    line r(rb, ra);
    pv ri;
    if(l.inter(r, ri) && r.cmp_proj(ra, ri)){
      inter = ri;
      return true;
    }
    return false;
  }
}

bool ray_ray_inter(pv r1a, pv r1b, pv r2a, pv r2b, pv &inter){
  if(r1a == r1b){
    if(point_in_ray(r2a, r2b, r1a)){ inter = r1a; return true; }
  }else if(r2a == r2b){
    if(point_in_ray(r1a, r1b, r2a)){ inter = r2a; return true; }
  }else{
    line r1(r1b, r1a), r2(r2b, r2a);
    pv ri;
    if(r1.inter(r2, ri) && r1.cmp_proj(r1a, ri) && r2.cmp_proj(r2a, ri)){
      inter = ri; return true;
    }
  }
  return false;
}

/*
intersection can be:
- empty: {}
- single point: {x}
- a segment: {x, y}
*/
vector<pv> seg_ray_inter(pv sa, pv sb, pv ra, pv rb){
  if(ra == rb){
    if(point_in_seg(sa, sb, ra)) return {ra};
  }else if(sa == sb){
    if(point_in_ray(ra, rb, sa)) return {sa};
  }else{
    line r(rb, ra), s(sb, sa);
    pv i; auto inter = r.inter(s, i);
    if(inter == 2){
      if(r.cmp_proj(ra, sa) && r.cmp_proj(ra, sb)) return {sa, sb};
      else if(r.cmp_proj(ra, sa) && !r.cmp_proj(ra, sb)) return {ra, sa};
      else if(!r.cmp_proj(ra, sa) && r.cmp_proj(ra, sb)) return {ra, sb};
    }else if(inter == 1){
      if(r.cmp_proj(ra, i) && s.cmp_proj(sa, i) && s.cmp_proj(i, sb)) return {i};
    }
  }
  return {};
}

////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////                  DISTANCE                  ///////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

T seg_point_dist(pv sa, pv sb, pv p){
  if(sa == sb) return (sa - p).norml2();
  line s(sb, sa);
  if(s.cmp_proj(sa, p) && s.cmp_proj(p, sb)) return s.dist(p);
  return min(fabs((p - sa).norml2()), fabs((p - sb).norml2()));
}

T seg_seg_dist(pv s1a, pv s1b, pv s2a, pv s2b){
  pv _;
  if(seg_in_seg(s1a, s1b, s2a, s2b, _)) return 0;
  T ans = seg_point_dist(s1a, s1b, s2a);
  ans = min(seg_point_dist(s1a, s1b, s2b), ans);
  ans = min(seg_point_dist(s2a, s2b, s1a), ans);
  return min(seg_point_dist(s2a, s2b, s1b), ans);
}

T ray_point_dist(pv ra, pv rb, pv p){
  if(ra == rb) return (p - ra).norml2();
  line r(rb, ra);
  if(r.cmp_proj(ra, p)) return r.dist(p);
  return min(abs((p - ra).norml2()), abs((p - rb).norml2()));
}

T line_seg_dist(line l, pv sa, pv sb){
  if(line_seg_inter(l, sa, sb).size()) return 0;     
  return min(l.dist(sa), l.dist(sb));
}

T line_ray_dist(line l, pv ra, pv rb){
  pv _;
  if(line_ray_inter(l, ra, rb, _)) return 0;     
  return min(l.dist(ra), l.dist(rb));
}

T ray_ray_dist(pv r1a, pv r1b, pv r2a, pv r2b){
  pv _;
  if(ray_ray_inter(r1a, r1b, r2a, r2b, _)) return 0;
  else{
    T dist = 1e18;
    line r1(r1b, r1a), r2(r2b, r2a);
    pv proj_r2_on_r1 = r1.ort_proj(r2a);
    pv proj_r1_on_r2 = r2.ort_proj(r1a);
    if(r1.cmp_proj(r1a, proj_r2_on_r1)) dist = min(dist, r1.dist(r2a));
    if(r2.cmp_proj(r2a, proj_r1_on_r2)) dist = min(dist, r2.dist(r1a));
    return min(dist, (r1a - r2a).norml2());
  }
}

T seg_ray_dist(pv sa, pv sb, pv ra, pv rb){
  if(seg_ray_inter(sa, sb, ra, rb).size()) return 0;
  else{
    T dist = 1e18;
    line r(rb, ra), s(sb, sa);
    pv proj_sa_on_r = r.ort_proj(sa);
    pv proj_sb_on_r = r.ort_proj(sb);

    if(r.cmp_proj(ra, proj_sa_on_r)) dist = min(dist, r.dist(sa));
    if(r.cmp_proj(ra, proj_sb_on_r)) dist = min(dist, r.dist(sb));

    pv proj_ra_on_s = s.ort_proj(ra);
    if(s.cmp_proj(sa, proj_ra_on_s) && s.cmp_proj(proj_ra_on_s, sb)) dist = min(dist, s.dist(ra));

    dist = min(dist, (ra - sa).norml2());
    return min(dist, (ra - sb).norml2());
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// MISC ////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

// minimum enclosing circle
// runs in O(n) where n is the amount of points
circle mec(vector<pv> &v){
	shuffle(v, v.size()-1);
	circle c = circle(v[0], v[1]);
	for(int i = 2; i < (int)v.size(); i++){
		if(!c.contains(v[i])){
			shuffle(v, i);
			circle c2 = circle(v[0], v[i]);
			for(int j = 1; j < i; j++){
				if(!c2.contains(v[j])){
					shuffle(v, j);
					circle c3 = circle(v[i], v[j]);
					for(int k = 0; k < j; k++){
						if(!c3.contains(v[k])) c3 = circle(v[i], v[j], v[k]);
					}
					c2 = c3;
				}
			}
			c = c2;
		}
	}
	return c;
}


////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////