#define TYPE long long // ATTENTION

const TYPE inf = LLONG_MAX; // ATTENTION

// Line equation defined as y = x * m + b
// m: slope, b: intersect/bias
// p: x-pos where the line stops being the maximum
// implements two comparators, one for insertion and structre order, other for point querying
struct Line{
	mutable TYPE m, b, p;
  mutable int id;

  // Lines are ordered by slope. i < j => slope(line_i) < slope(line_j)
	bool operator <(const Line &o) const {
    if(m == o.m) return b < o.b;
    else return m < o.m;
  }

  // first Line y s.t. !(p(y) < x). that is, first line in which x fits in
	bool operator <(const TYPE x) const { return p < x;}

  TYPE eval(TYPE x) const { return x*m + b;}

  // floor division that works for negative values (eg. floor(-1/2) = -1 , vanilla c++ returns 0)
  // note that (a^b) < 0 iff a*b<0 (there is a bit indicating if x is negative)
  // if a/b < 0 and it isnt a integer, add -1 to c++ result
  TYPE intersect (const Line &o) const{
    TYPE x = b - o.b, y = o.m - m;
    // return (x/y); // DOUBLE ATTENTION
    return (x/y) - ((x^y) < 0 && x % y); // INT ATTENTION
  }
};


// Queries the maximum lin. func. at point X. 
// Minimum can be queried by negating both slopes and biases and also the query result
struct DynamicCHT : multiset<Line,less<>> {
  typedef std::multiset<Line, std::less<void>>::iterator it;

  // take lines A and B where B is best until R and slope(A) < slope(B)
  // if intersect(A,B) > R, A starts being a better line before B
  // (slope is better) and ends after B ends itself i.e. B is now useless
  void erase_right(it &y){
    auto z = next(y);
    // y: added line, z: line to the right
    // erasing now useless lines to the right
    while(true){
      if(z == end()){
        // if y is the last itr, its limit is inf
        y->p = inf; break;
      }else{
        // else z is valid and may be removed
        y->p = y->intersect(*z);
        if(y->p < z->p) break;
        else z = erase(z);
      }
    }
  }

  // erasing lines to the left of the added one, using the same idea that is
  // used when removing from the right
  // take lines A, B and C, where C is the added one. we can test A against B
  // and, if needed, remove B
  // Note that begin() wont be removed, since it has smaller slope
  void erase_left(it y){
    if(y == begin()) return; 
     // z will keep the added line
    auto z = y;
    auto x = --y;
    while(true){
      // updating endpos of the line to the left of Z
    	TYPE new_intersect = x->intersect(*z);
    	if(new_intersect > x->p){
    		// the added line is useless if it only intersects to the 
        // one to the left afther the one on the left stops being maximum
    		erase(z); break;
      }else{
        x->p = new_intersect;
        if(x == begin()) break;
        y = x--; // now x << y << z
        if(x->p < y->p) break;
        else erase(y); // y is useless
      }
    }
  }

  /*
  Insertion of y = m * x + b, may remove now unecessary lines and also
  will update the ending position for the added line.
  Also, the added line may be useless and wont modify the structure
  Note that the lines from both direcitons (before and after) the recently
  added may be removed.

  Note that the structure always mantain only one Line with slope m.
  If the added line has same slope than the next one, it is useless.
  By ordering, it will have a lower bias, so it will always produce
  smaller results
  */
	void add(TYPE m, TYPE b, int id = -1){
		auto y = insert({m, b, inf, id}), z = next(y);
    // y: iterator for the added line
    // z: iterator for the next line (in order)
    // ensuring unique slope values
    if(z != end() && y->m == z->m) erase(y);
    else{
      if(y != begin()){
        auto x = prev(y);
        if(x->m == y->m) erase(x);
      }
      erase_right(y); erase_left(y);
    }
	}

  // may also return Line or Line.id
	TYPE query(TYPE x){
    assert(!empty());
		return lower_bound(x)->eval(x);
	}
};
