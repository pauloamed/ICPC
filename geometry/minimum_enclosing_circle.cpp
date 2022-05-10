#define x first
#define y second

double dist(pair<double, double> a, pair<double, double> b){
	return hypot(a.x-b.x, a.y-b.y);
}
 
void shuffle(vector<pair<double, double>> &v, int k){
	for(int i = k-1; i >= 1; i--){
		swap(v[i], v[rand()%i]);
	}
}

struct circle{
	pair<double, double> c;
	double r;
	inline bool contains(pair<double, double> p) { return dist(p, this->c) <= r; }
	circle(pair<double, double> a, pair<double, double> b) : 
		c({(a.x+b.x)/2.0, (a.y+b.y)/2.0}), 
		r(hypot(a.x-b.x, a.y-b.y)/2.0) {}
		
	circle(pair<double, double> a, pair<double, double> b, pair<double, double> c) : c({0,0}), r(0) {
		
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
	  	this->r = dist(a, {h, k});
	}
};

// minimum enclosing circle
// runs in O(n) where n is the amount of points
circle mec(vector<pair<double, double>> &v){
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
