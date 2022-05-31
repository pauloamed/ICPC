#include<bits/stdc++.h>
using namespace std;

// area: polygon area
// poly_is_ccw: whether polyhon is in cw or ccw order
// poly_is_convex: whether polygon is convex


// ConvexPoly
// build: builds convex hull
// maximize_dot: queries points which maximizes dot product 


#define deb(...) logger(#__VA_ARGS__, __VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values) {
    cout << vars << " = ";
    string delim = "";
    (..., (cout << delim << values, delim = ", "));
    cout<<endl;
}

#define T long double
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

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

T sum(vector<T> &vals){
  T sum = 0, c = 0;
  for(auto x : vals){
    T y = x - c;
    T t = sum + y;
    c = (t - sum) - y;
    sum = t;
  }
  return sum;
}

T perimeter(vector<pv> &pvs){
  vector<T> vals;
  for(int i = 0, n = pvs.size(); i < n; ++i){
    vals.push_back((pvs[i] - pvs[(i + 1) % n]).norml2());
  }
  return sum(vals);
}

// works for any polyhon (convex or not)
T area2(vector<pv> &pts){ 
	T area = 0;
	for(int i = 0, n = pts.size(); i < n; i++){
		area += pts[i].cross(pts[(i + 1) % n]);
	}
	return fabs(area);
}

// ccw (1) or cw (0)
bool poly_is_ccw(vector<pv> &edges){ 
  return area2(edges) > 0;
}

// pts: list of vertices
bool poly_is_convex(vector<pv> &pts){
  int state = 0;
  int n = pts.size();
  for(int i = 0; i < n; ++i){
    int q = pts[i].orient(pts[(i+1)%n], pts[(i+2)%n]);
    if(state == 0) state = q;
    else if(state != q && q != 0) return false;
  }
  return true;
}

struct ConvexPoly{
  vector<pv> pts;
  vector<pv> up, down;

  ConvexPoly():pts(){}
  ConvexPoly(vector<pv> &_pts):pts(_pts){}
 
  pv maximize_dot(pv q){
    auto ternary_search = [](vector<pv> &hull, pv pt){
      if(hull.size() == 1) return hull[0];
  
      int l = 0;
      int r = hull.size() - 1;
      while(r - l > 2){
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
        if (pt.dot(hull[m1]) < pt.dot(hull[m2])) l = m1;
        else r = m2;
      }
      pv ret = (hull.back().dot(pt) > hull.front().dot(pt)? hull.back() : hull.front());
      for(int i = l; i <= r; ++i) if(pt.dot(hull[i]) > pt.dot(ret)) 
        ret = hull[i];
      return ret;
    };
    auto a = ternary_search(up, q);
    auto b = ternary_search(down, q);
    return (a.dot(q) > b.dot(q)? a : b);
  }
  
  void chull(vector<pv> &a, bool include_collinear = false){
    sort(a.begin(), a.end());
    a.resize(unique(a.begin(), a.end()) - a.begin());
 
    int n = a.size();
    if(n == 1) pts = up = down = a;
    else{
      pv left = a[0], right = a.back();
 
      up.push_back(left);
      down.push_back(left);
 
      for(int i = 1; i < n; i++){
        T orient_ul = left.orient(a[i], right);
        if(i == n - 1 || orient_ul < 0 || (orient_ul == 0 && include_collinear)){
          while(up.size() >= 2){
            T orient = up[up.size() - 2].orient(up.back(), a[i]);
            if(!(orient < 0 || (orient == 0 && include_collinear))) up.pop_back();
            else break;
          }
          up.push_back(a[i]);
        }
        if(i == n - 1 || orient_ul > 0){
          while(down.size() >= 2){
            T orient = down[down.size() - 2].orient(down.back(), a[i]);
            if(!(orient > 0 || (orient == 0 && include_collinear))) down.pop_back();
            else break;
          }
          down.push_back(a[i]);
        }
      }
      
      pts.clear();
      pts.reserve(up.size() + down.size());
      for(int i = 0; i + 1 < down.size(); i++) pts.push_back(down[i]);
      for(int i = up.size() - 1; i > 0; i--) pts.push_back(up[i]);
    }
  }
   
  /*
  0: outside
  1: on a edge
  2: inside
  */
  int is_pt_in(pv pt){
    auto first_edge_geq_x = [](vector<pv> &hull, pv ptx){
      // edges from i to i + 1
      int ret = 0;
      int l = 0, r = hull.size() - 1;
      while(l <= r){
        int m = (l + r) / 2;
        if((hull[m] < ptx) || (hull[m] == ptx)){
          ret = m;
          l = m + 1;
        }else r = m - 1;
      }
      return ret;
    };

    assert(!pts.empty());
    if(pts.size() == 1){
      return pt == pts[0];
    }else if(pts.size() == 2){
      return point_in_seg(pts[0], pts[1], pt);
    }else if(pts.size() == 3){
      return point_in_tri(pts[0], pts[1], pts[2], pt);
    }else{
      int e_up = first_edge_geq_x(up, pt);
      int e_down = first_edge_geq_x(down, pt);
      {
        pv nxt_pt;
        if(e_up + 1 == up.size()) nxt_pt = down[down.size() - 2];
        else nxt_pt = up[e_up + 1];
        if(up[e_up].orient(nxt_pt, pt) > 0) return 0;
        else if(point_in_seg(up[e_up], nxt_pt, pt)) return 1;
      }
      {
        pv nxt_pt;
        if(e_down + 1 == down.size()) nxt_pt = up[up.size() - 2];
        else nxt_pt = down[e_down + 1];
        if(down[e_down].orient(nxt_pt, pt) < 0) return 0;
        else if(point_in_seg(down[e_down], nxt_pt, pt)) return 1;
      }
      return 2;
    }
  }

  ConvexPoly mink_sum(ConvexPoly &c){
    auto get_edge = [](vector<pv> &v, int i){
      return pv{v[(i + 1) % v.size()] - v[i]};
    };
    int i = 0, j = 0, n = pts.size(), m = c.pts.size();
    vector<pv> output = {pts[0] + c.pts[0]};

    while(i < n || j < m){
      pv e;
      if(i == n) e = get_edge(c.pts, j++);
      else if(j == m) e = get_edge(pts, i++);
      else{
        auto ea = get_edge(pts, i);
        auto eb = get_edge(c.pts, j);
        if(ea.cross(eb) < 0){ e = eb; j++;}
        else{ e = ea; i++; }
      }
      
      pv new_pt = output.back() + e;
      if(output.size() > 1 && output.back().orient(output[output.size() - 2], new_pt) == 0)
        output.pop_back();
      output.push_back(new_pt);
    }
    return ConvexPoly(output);
  }
};

