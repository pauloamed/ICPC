#include<bits/stdc++.h>
using namespace std;

#define TYPE long double // ATTENTION
const TYPE EPS = 1e-8;

bool zero(TYPE x){
  return fabs(x) <= EPS;
}

struct Vec{
	mutable TYPE x, y;
  mutable int id;

  TYPE cross(const Vec &o) const {
    return x * o.y - y * o.x;
  }

  // Comparing using vectorial product
	bool operator <(const Vec &o) const {
    return !zero(cross(o)) && cross(o) > 0;
  }

  // a < b < c
  // 0: collinear, 1: clockwise, -1: counterclockwise
  int static getOrientCase(const Vec &a, const Vec &b, const Vec &c){
    TYPE val = (b.y - a.y) * (c.x - b.x)
            - (b.x - a.x) * (c.y - b.y);
    
    if(zero(val)) return 0;
    if(val > 0) return 1;
    else return -1;
  }

  // Given a,b,c, returns true if abc is a concave curve
  // a < b < c
  bool static isConcave(const Vec &a, const Vec &b, const Vec &c){
    return getOrientCase(a, b, c) == 1;
  }

  bool isParallel(const Vec &b) const{
    return zero(cross(b));
  }

  // if a is inside b
  bool isInside(const Vec &b) const{
    if(!isParallel(b)) return false;
    return x <= b.x;
  }

  bool static insideTriangle(const Vec &a, const Vec &b, const Vec &c){
    // a < b < c
    // b inside (a,c) triangle
    return getOrientCase(a, b, c) != -1;
  }

};

struct DynamicPositiveHull : multiset<Vec,less<>> {
  typedef std::multiset<Vec, std::less<void>>::iterator it;

	void add(TYPE x, TYPE y, int id = -1){
		auto curr = insert({x, y, id});

    if(curr != begin() && next(curr) != end()){
      if(Vec::isConcave(*prev(curr), *curr, *next(curr))){
        erase(curr);
        return;
      }
    }else if(curr == begin() && next(curr) != end()){
      if(curr->x <= next(curr)->x){
        erase(curr);
        return;
      }
    }else if(next(curr) == end() && curr != begin()){
      if(curr->y <= prev(curr)->y){
        erase(curr);
        return;
      }
    }

    // erase left
    if(curr != begin()){
      auto prev_1 = prev(curr);
      while(prev_1 != begin()){
        auto prev_2 = prev(prev_1);
        if(Vec::isConcave(*prev_2, *prev_1, *curr)){
          erase(prev_1);
          prev_1 = prev_2;
        }else break;
      }

      if(prev_1 == begin() && curr->x >= prev_1->x)
        erase(prev_1);
    }

    // erase right
    if(next(curr) != end()){
      auto nxt_1 = next(curr);
      while(next(nxt_1) != end()){
        auto nxt_2 = next(nxt_1);
        if(Vec::isConcave(*curr, *nxt_1, *nxt_2)){
          nxt_1 = erase(nxt_1);
        }else break;
      }

      if(next(nxt_1) == end() && curr->y >= nxt_1->y)
        erase(nxt_1);
    }

    if(curr != begin() && next(curr) != end()){
      if(Vec::isConcave(*prev(curr), *curr, *next(curr))){
        erase(curr);
        return;
      }
    }
  }

  bool solve_begin(const Vec &v){
    Vec phantom{begin()->x, 0, -1};
    return Vec::insideTriangle(phantom, v, *begin());
  }

  bool solve_end(const Vec &v){
    Vec phantom{0, rbegin()->y, -1};
    return Vec::insideTriangle(*rbegin(), v, phantom);
  }

  bool is_in(const Vec &v){
    if(empty()) return false;
    if(v < *begin()) return solve_begin(v);

    auto x = lower_bound(v);
    if(x == end()) return solve_end(v);

    // v <= x
    if(v.isParallel(*x)) return v.isInside(*x);

    // v < x
    assert(x != begin());
    auto y = prev(x);
    
    return Vec::insideTriangle(*y, v, *x);
	}
};

DynamicPositiveHull duh;
