int dist(pair<int,int> a, pair<int,int> b){
    int da = (a.x - b.x);
    int db = (a.y - b.y);
    return da * da + db * db;
}

int prod_vet(pair<int,int> a, pair<int,int> b){
    return a.x * b.y - b.x * a.y;
}

pair<int,int> menos(pair<int,int> a, pair<int,int> b){
    return {a.x - b.x, a.y - b.y};
}


pair<int,int> center;
bool half(const pair<int,int> &a) { // 1 e 2 quadrantes
    pair<int,int> p = menos(a, center);
    assert(p.x != 0 || p.y != 0); // the argument of (0,0) is undefined
    return p.y > 0 || (p.y == 0 && p.x < 0);
}

bool cmp(const pair<int,int> &a, const pair<int,int> &b){
    if(half(a) == half(b)){
        int temp = prod_vet(menos(a, center), menos(b, center));
        if(temp == 0) return dist(a, center) < dist(b, center);
        return temp > 0;
    }else{
        return half(a) < half(b);
    }
}


int32_t main(){
    int n; cin >> n;

    int x, y; cin >> x >> y;
    center = {x, y};
    vector<pair<int,int>> pontos(n);
    for(int i = 0; i < n; ++i){
        cin >> pontos[i].x >> pontos[i].y;
    }
    sort(pontos.begin(), pontos.end(), cmp);

    int l = 0, r = 0;
    while(l < pontos.size()){
        while(true){
            int nextR = (r + 1) % pontos.size();
            int x = prod_vet(menos(pontos[l].first, center), menos(pontos[nextR].first, center));
            if(nextR == l || x < 0) break;
            r = nextR;
        }
        if(r == l)r++;
        l++;
    }
}
