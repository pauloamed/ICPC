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
    for(int i(0); i < pontos.size(); ++i){ // O(N)
        if(pontos[i].y < min_y || (pontos[i].y == min_y && pontos[i].x < min_x)){
            inicio = pontos[i];
            min_y = inicio.y;
            min_x = inicio.x;
        }
    }
    c = inicio;
    sort(pontos.begin(), pontos.end(), compare); // O(logN)

    int k;
    for(k=pontos.size()-2; k>=0 && prod_vet(menos(pontos[k], inicio), menos(pontos.back(), inicio)) > 0 == 0; k--){}
    reverse(pontos.begin() + k+1, pontos.end());

    vector<par> ans;
    ans.push_back(pontos[0]);
    ans.push_back(pontos[1]);
    ans.push_back(pontos[2]);
    for(int i(3); i < pontos.size(); ++i){ // O(N)
        while(prod_vet(menos(pontos[i], ans[ans.size()-2]), menos(ans.back(), ans[ans.size()-2])) > 0){
            ans.pop_back();
        }
        ans.push_back(pontos[i]);
    }

    return ans;
}

int main(){

    vector<par> v;
    vector<par> temp;
    vector<par> convex_hull;
    map<par, bool> jafoi;

    while(1){
        jafoi.clear();
        v.clear();
        convex_hull.clear();

        int N, a, b;
        cin >> N;

        if(N == 0) return 0;

        for(int i(0); i < N; ++i){
            cin >> a >> b;
            v.push_back(_mp(a,b));
        }

        int cont(0);
        while(1){
            if(v.size() >= 3){
                convex_hull = graham_scan(v);
                cont++;

                for(int i(0); i < convex_hull.size(); ++i)
                    jafoi[convex_hull[i]] = true;

                temp.clear();
                for(int i(0); i < v.size(); ++i){
                    if(jafoi.count(v[i]) == 0)
                        temp.push_back(v[i]);
                }
                v = temp;
            }

            if(v.size() < 3){
                if(cont % 2){
                    cout << "Take this onion to the lab!\n";
                }else{
                    cout << "Do not take this onion to the lab!\n";
                }
                break;
            }
        }
    }
}
