#include<bits/stdc++.h>
using namespace std;

#define MAXN 20

vector<int> weights;
pair<int,int> pd[1<<MAXN];

bool get_bit(int x, int i){
    return (x&(1<<i));
}

int flip_bit(int x, int i){
    return (x^(1<<i));
}

int solve(int x, int limite){
    pair<int,int> temp;
    pd[0] = {1,0};
    for(int i = 1; i < (1<<x); ++i){
        pd[i] = {x+1, 0};
        for(int p = 0; p < weights.size(); ++p){
            if(get_bit(i, p)){
                temp = pd[flip_bit(i, p)];
                if(temp.second + weights[p] <= limite){
                    temp.second += weights[p];
                }else{
                    temp.first++;
                    // temp.second = weights[p];
                    temp.second = min(temp.second, weights[p]);
                }
                pd[i] = min(pd[i], temp);
            }
        }
    }
    return pd[(1<<x)-1].first;
}

int main(){
    int n, x; cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> x; weights.push_back(x);
    }
    cin >> x;
    cout << solve(n, x) << endl;

    // for(int i = 0; i < (1<<n); ++i){
    //     printf("%d: %d\n", i,pd[i].first+1);
    // }
}
