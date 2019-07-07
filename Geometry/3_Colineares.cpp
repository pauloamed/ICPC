#include<bits/stdc++.h>
using namespace std;

#define num int
#define par pair<num,num>
#define _mp make_pair
#define x first
#define y second

num prod_vet(par a, par b){
    return a.x * b.y - b.x * a.y;
}

par menos(par a, par b){
    return _mp(a.x - b.x, a.y - b.y);
}

double dist(par a, par b){
    return hypot(a.x - b.x, a.y - b.y);
}

par c;
bool compare(const par &a, const par &b){
    int temp = prod_vet(menos(a,c), menos(b,c));
    if(temp == 0) return dist(a,c) < dist(b,c);
    else return temp > 0;
}

int main(){
    int N, a, b;
    cin >> N;

    vector<par> v1;
    vector<par> v2;
    for(int i(0); i < N; ++i){
        cin >> a >> b;
        v1.push_back(_mp(a,b));
        v2.push_back(_mp(a,b));
    }

    for(int i(0); i < N; ++i){
        c = v1[i];
        sort(v2.begin(), v2.end(), compare);
        for(int j(0); j < N - 1; ++j){
            if(c == v2[j] || c == v2[j+1]) continue;

            if(prod_vet(menos(v2[j], c), menos(v2[j+1], c)) == 0){
                printf("3 pontos colineares achados\n");
                cout << v1[i].x << " " << v1[i].y << endl;
                cout << v2[j].x << " " << v2[j].y << endl;
                cout << v2[j+1].x << " " << v2[j+1].y << endl;
                return 0;
            }
        }
    }
}
