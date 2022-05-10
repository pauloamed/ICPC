#include <bits/stdc++.h>
using namespace std;


/*
The following structure queries the maximum lin. func. at point X. 
The minimum can be queried by negating both slopes and biases and also the query result.
*/


#define TYPE long double // CAN ALSO BE INT

const TYPE inf = LLONG_MAX; // ATENCAO

struct Line{
	// Line equation defined as y = x * m + b
  // m: slope, b: intersect/bias
  // p: x-pos where the line stops being the maximum
	mutable TYPE m, b, p;
  mutable int id;

  // comparator to other Lines, uses slopes for comparison
  // used for ordering the container (insertion)
	bool operator <(const Line &o) const {
    if(m == o.m) return b < o.b;
    else return m < o.m;
  }

  // comparator to scalars, used in querying best line for a given value
	bool operator <(const TYPE x) const { return p < x;}

  // evals scalar for this line
  TYPE eval(TYPE x) const { return x*m + b;}

  TYPE intersect (const Line &o) const{
    // floor division (works for negative values) (eg. floor(-1/2) = -1 , c++ returns 0)
    // note that (a^b) < 0 iff a*b<0 (there is a bit indicating if x is negative)
    // if a/b < 0 and it isnt a integer, add -1 to c++ result
    TYPE x = b - o.b, y = o.m - m;
    // cout << (x/y) << "\n";
    return (x/y); // DOUBLE
    // return (x/y) - ((x^y) < 0 && x % y); // INT
  }
};


// Inheriting an order container for mantaining the line orders
// note that both comparators yield the same order, so querying using a scalar is ok
// less<> (transparent) allowing the usage of both comparators
// Lines are ordered by slope. i < j => slope(line_i) < slope(line_j)
struct DynamicCHT : multiset<Line,less<>> {

  // Insertion of y = m * x + b, may remove now unecessary lines and also
  // will update the ending position for the added line.
  // Also, the added line may be useless and wont modify the structure
  // Note that the lines from both direcitons (before and after) the recently
  // added may be removed.
	void add(TYPE m, TYPE b, int id){
    // y: iterator for the added line
    // z: iterator for the next line (in order)
		auto y = insert({m, b, inf, id}), z = next(y);
    // y << z


    // Note that the structure always mantain only one Line with slope m.
    // If the added line has same slope than the next one, it is useless.
    // By ordering, it will have a lower bias, so it will always produce
    // smaller results
    if(z != end() && y->m == z->m){ erase(y); return; }
    if(y != begin()){
      auto x = prev(y);
      if(x->m == y->m) x = erase(x);
    }

    // y: added line, z: line to the right
    // erasing now useless lines to the right
    while(true){
      // take lines A and B where B is best until R and slope(A) < slope(B)
      // if intersect(A,B) > R, A starts being a better line before B
      // (slope is better) and ends after B ends itself. I.e. B is now useless

      // if there is no z, the limit of the current line is inf
      if(z == end()){ y->p = inf; break;}

      // else z is valid and may be removed
      y->p = y->intersect(*z);
      if(y->p < z->p) break;
      else z = erase(z); // z now points to the next(z)
    }

    if(y == begin()) return; // wont remove anynone to the left

    // erasing lines to the left of the added one, using the same idea that is
    // used when removing from the right
    // take lines A, B and C, where C is the added one. we can test A against B
    // and, if needed, remove B
    // Note that begin() wont be removed, since it has smaller slope

    z = y; // z will keep the added line
    auto x = --y;
    while(true){
      // updating endpos of the line to the left of Z
    	TYPE newIntersect = x->intersect(*z);
      // cerr << newIntersect << " " << x->p << endl;
    	if(newIntersect <= x->p) x->p = newIntersect; // updating x endpos
    	else{
        // cerr << newIntersect << " " << x->p << endl;
    		// the added line is useless if it only intersects
    		// to the one to the left afther the one on the left
    		// stops being maximum
    		erase(z); break;
    	}
      if(x == begin()) break;
      y = x--; // now x << y << z
      if(x->p < y->p) break;
      else erase(y); // y is useless
    }
	}

	// Querying
	Line query(TYPE x){
    assert(!empty());
    // lower bound for (Line comparator using scalar)
    // first Line y in Set s.t. !(p(y) < x). that is, first line in which x fits it
		return *lower_bound(x);
	}
};

DynamicCHT cansaco, habilidade;

const TYPE EPS = 1e-9;

int cmp(double x, double y = 0, double tol = EPS){
	return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

int main(){
  int n; cin >> n;
  for(int i = 0; i < n; ++i){
    int h_a, h_b, c_a, c_b; cin >> h_a >> h_b >> c_a >> c_b;
    cansaco.add(-c_b, -c_a, i);
    habilidade.add(h_b, h_a, i);
  }

  map<int,pair<TYPE,TYPE>> id2seg[2];

  for(auto it = habilidade.begin(); it != habilidade.end(); it++){
    auto x = *it;
    if(x.p < 0) continue;

    TYPE l = 0;
    if(it != habilidade.begin()) l = prev(it)->p;
    // l = max(l, (TYPE)0.0);
    id2seg[0][x.id] = {l, x.p};
  }  
  
  for(auto it = cansaco.begin(); it != cansaco.end(); it++){
    auto x = *it;
    if(x.p < 0) continue;

    TYPE l = 0;
    if(it != cansaco.begin()) l = prev(it)->p;
    // l = max(l, (TYPE)0.0);
    id2seg[1][x.id] = {l, x.p};
  }  

  int ans = 0;
  for(int i = 0; i < n; ++i){
    if(!id2seg[0].count(i) || !id2seg[1].count(i)) continue;
    auto a = id2seg[0][i];
    auto b = id2seg[1][i];

    TYPE x = max(a.first, b.first);
    TYPE y = min(a.second, b.second);

    auto inter = y - x;
    if(cmp(x, y) < 0){
      ans++;
    }
      
  }

  cout << ans << "\n";
}