#include<bits/stdc++.h>
using namespace std;

#define num int
#define par pair<num,num>
#define _mp make_pair
#define x first
#define y second
const int inf = 1e20;

double dist(par a, par b){
    return hypot(a.x - b.x, a.y - b.y);
}

num prod_vet(par a, par b){
    return a.x * b.y - b.x * a.y;
}

par menos(par a, par b){
    return _mp(a.x - b.x, a.y - b.y);
}

par c;
bool compare(const par &a, const par &b){
    int temp = prod_vet(menos(a,c), menos(b,c));
    if(temp == 0) return dist(a,c) < dist(b,c);
    else return temp > 0;
}

vector<par> graham_scan(vector<par>& pontos){
    int min_y = inf;
    int min_x = inf;
    par inicio;
    for(int i(0); i < pontos.size(); ++i){
        if(pontos[i].y < min_y || (pontos[i].y == min_y && pontos[i].x < min_x)){
            inicio = pontos[i];
            min_y = inicio.y;
            min_x = inicio.x;
        }
    }
    c = inicio;
    sort(pontos.begin(), pontos.end(), compare);

    vector<par> ans;
    ans.push_back(pontos[0]);
    ans.push_back(pontos[1]);
    ans.push_back(pontos[2]);
    for(int i(3); i < pontos.size(); ++i){
        while(prod_vet(menos(pontos[i], ans[ans.size()-2]), menos(ans.back(), ans[ans.size()-2])) >= 0){
            ans.pop_back();
        }
        ans.push_back(pontos[i]);
    }

    return ans;
}

int main(){
    int N, a, b;
    cin >> N;

    vector<par> v;
    for(int i(0); i < N; ++i){
        cin >> a >> b;
        v.push_back(_mp(a,b));
    }

    vector<par> convex_hull(graham_scan(v));

    for(int i(0); i < convex_hull.size(); ++i){
        cout << convex_hull[i].x << " " << convex_hull[i].y << endl;
    }
}
