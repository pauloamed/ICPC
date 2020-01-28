// handbook of geometry, lecomte

struct line{
    pv v; T c;

    // line eq: ax + by = c
    // one can also use a direction vector (b, -a) and a scalar c

    line(pv v, T c):v(v), c(c){} // from dir vec and c
    line(T a, T b, T c): v({b,-a}), c(c){} // from equation
    line(pv a, pv b):v(a-b), c(a.cross(b)){} // from 2 dif points

    // side: a esq da reta, seguindo a orientacao do vetor, eh positivo
    // side: na reta eh 0
    // side: c.c. eh neg.
    T side(pv p){ return v.cross(p) - c;}
    double dist(pv p){ return abs(side(p))/abs(v.norml2()); } // dist to point
    double sqDist(pv p){ return (side(p)*side(p)) / (double) v.sq(); }
    line perpLineThrPoint(pv p){ return line(p, this->v.perp()); } // linha perp a atual q passa pelo ponto p
    pv ortProj(pv p){ return (p - (this->v.perp() * side(p)))/v.sq(); } // point ortogonal projection
    pv refl(pv p){ return (p - (this->v.perp() * 2 * side(p)))/v.sq(); } // point reflection

    // cmp func for sorting points through line. points dont need to lie on the line
    bool cmpProj(pt a, pt b){ return v.dot(a) < v.dot(b); }
}


bool pointInSegment(pv a, pv b, pv c){
    // checks if point c is in AB segment
    return a.orient(b,c) == 0 && pointInDisk(a,b,c);
}

bool properSegmentInSegment(pv s1a, pv s1b, pv s2a, pv s2b, pv &inter){
    int oriS1aToS2 = s2a.orient(s2b, s1a);
    int oriS1bToS2 = s2a.orient(s2b, s1b);

    int oriS2aToS1 = s1a.orient(s1b, s2a);
    int oriS2bToS1 = s1a.orient(s1b, s2b);

    if(oriS1aToS2 * oriS1bToS2 < 0){ // points of s1 are on dif sides from s2
        if(oriS2aToS1 * oriS2bToS1 < 0){ // points of s2 are on dif sides from s1
            inter = ((s1a * oriS1bToS2) - (s1b * oriS1aToS2)) / (oriS1bToS2 - oriS1aToS2); // PODE DAR OVERFLOW
            return true;
        }
    }
    return false;
}

vector<pv> segmentIntersect(pv s1a, pv s1b, pv s2a, pv s2b){
    pv inter;
    if(properSegmentInSegment(s1a, s1b, s2a, s2b, inter)) return {inter};

    vector<pv> ans;
    if(pointInSegment(s1a, s1b, s2a)) ans.push_back(s2a);
    if(pointInSegment(s1a, s1b, s2b)) ans.push_back(s2b);
    if(pointInSegment(s2a, s2b, s1a)) ans.push_back(s1a);
    if(pointInSegment(s2a, s2b, s1b)) ans.push_back(s1b);

    return ans;
}

double segPointDist(pt a, pt b, pt c){ // closest dist from AB to C
    if(a != b){ // not deg. segment
        line l(a,b);
        // if c projects between a and b
        if(l.cmpProj(a, c) && l.cmpProj(c, b)) return l.dist(c); // dist to linear proj of c
    }
    return min(abs((p - a).norml2()), abs((p - b).norml2()));
}

double segSegDist(pv s1a, pv s1b, pv s2a, pv s2b){
    pv _;
    if(properSegmentInSegment(s1a, s1b, s2a, s2b, _)) return 0;
    double ans = segPointDist(s1a, s1b, s2a);
    ans = min(segPointDist(s1a, s1b, s2b), ans);
    ans = min(segPointDist(s2a, s2b, s1a), ans);
    return min(segPointDist(s2a, s2b, s1b), ans);
}
