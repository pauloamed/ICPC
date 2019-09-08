#include<bits/stdc++.h>
using namespace std;

#define INF 10000000.0
#define Margem 1e-9

#define T long long

vector<pair<T,T>> v_x;
vector<pair<T,T>> v_y;

bool compareY(const pair<T,T> &a, const pair<T,T> &b){
    return a.second < b.second;
}

double dist(const pair<T,T> &p1, const pair<T,T> &p2){
    return hypot(p1.first-p2.first, p1.second-p2.second);
}

pair<pair<pair<T,T>,pair<T,T>>, double> solve(int l, int r, vector<int> &v){
    if(r - l <= 0) return make_pair(make_pair(make_pair(0LL,0LL), make_pair(0LL,0LL)), INF);
    if(r - l == 1) return make_pair(make_pair(v_x[l], v_x[r]), dist(v_x[l], v_x[r]));

    int m = (l + r) / 2;

    // O(N)
    vector<int> yl_temp, yr_temp;
    if(r - l == v_x.size() - 1){
        for(int i(0); i < v_y.size(); ++i){
            if(v_y[i] <= v_x[m])
                yl_temp.push_back(i);
            else yr_temp.push_back(i);
        }
    }else{
        for(int i(0); i < v.size(); ++i){
            if(v_y[v[i]] <= v_x[m])
                yl_temp.push_back(v[i]);
            else yr_temp.push_back(v[i]);
        }
    }

    pair<pair<pair<T,T>,pair<T,T>>, double> q1 = solve(l, m, yl_temp);
    pair<pair<pair<T,T>,pair<T,T>>, double> ans = solve(m + 1, r, yr_temp);


    if(q1.second < ans.second) ans = q1;
    pair<pair<T,T>,pair<T,T>> par = ans.first;
    double d = ans.second;

    // O(N)
    vector<int> y_linha;
    if(r - l == v_x.size() - 1){
        for(int i(0); i < v_y.size(); ++i){
            if(fabs(v_y[i].first - v_x[m].first) <= d + Margem)
                y_linha.push_back(i);
        }
    }else{
        for(int i(0); i < v.size(); ++i){
            if(fabs(v_y[v[i]].first - v_x[m].first) <= d + Margem)
                y_linha.push_back(v[i]);
        }
    }

    // O(N)
    for(int i(0); i < y_linha.size(); ++i){
        for(int j(i+1); j < min((int) y_linha.size(), i + 8); ++j){
            if(dist(v_y[y_linha[i]], v_y[y_linha[j]]) < d){
                d = dist(v_y[y_linha[i]], v_y[y_linha[j]]);
                par = {v_y[y_linha[i]], v_y[y_linha[j]]};
                ans = make_pair(par, d);
            }
        }
    }

    return ans;
}
