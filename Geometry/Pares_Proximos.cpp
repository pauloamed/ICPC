#include<bits/stdc++.h>
using namespace std;

#define INF 10000000.0
#define Margem 1e-9

vector<pair<double,double>> v_x;
vector<pair<double,double>> v_y;

bool compareY(const pair<double,double> &a, const pair<double,double> &b){
    return a.second < b.second;
}

double dist(const pair<double,double> &p1, const pair<double,double> &p2){
    return hypot(p1.first-p2.first, p1.second-p2.second);
}

double solve(int l, int r, vector<int> &v){
    if(r - l <= 0) return INF;
    if(r - l == 1) return dist(v_x[l], v_x[r]);

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

    double d = fmin(solve(l, m, yl_temp), solve(m + 1, r, yr_temp));


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
            d = fmin(d, dist(v_y[y_linha[i]], v_y[y_linha[j]]));
        }
    }

    return d;
}

int main(){
    int n;
    double a, b, ans;
    while(1){
        cin >> n;

        if(n == 0) return 0;

        for(int i(0); i < n; ++i){
            cin >> a >> b;
            v_x.push_back(make_pair(a,b));
            v_y.push_back(make_pair(a,b));
        }

        sort(v_x.begin(), v_x.end());
        sort(v_y.begin(), v_y.end(), compareY);

        vector<int> temp;
        ans = solve(0, v_x.size() - 1, temp);

        if( ans < 10000.0 + Margem)
            printf("%.4lf\n", ans);
        else
            cout << "INFINITY" << endl;

        v_x.clear();
        v_y.clear();
    }
}

//
// for(int i(0); i < n; ++i){
//     cout << v_x[i].first << " "  << v_x[i].second << " ";
// }cout << endl;
// for(int i(0); i < n; ++i){
//     cout << v_y[i].first << " " << v_y[i].second << " ";
// }cout << endl;
