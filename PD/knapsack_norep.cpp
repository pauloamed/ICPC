#include<bits/stdc++.h>
using namespace std;

#define MAXX 100
#define MAXK 10

vector<int> ks;




bool possible[MAXX];
bool solve(int x){
    possible[0] = true;
    for(int i = 1; i < ks.size(); ++i){
        for(int j = x-ks[i]; j >= 0; --j){
            possible[j+ks[i]] |= possible[j];
        }
    }
    return possible[x];
}

// bool possible[MAXX][MAXK];
// bool solve(int x){
//     possible[0][0] = true;
//     for(int i = 1; i < ks.size(); ++i){
//         for(int j = 0; j <= x; ++j){
//             possible[j][i] = possible[j][i-1];
//             if(j-ks[i]>=0)
//                 possible[j][i] |= possible[j-ks[i]][i-1];
//         }
//     }
//     return possible[ks.size()-1][x];
// }

int main(){
    int k, x; cin >> k;

    ks.push_back(0);
    for(int i = 0; i < k; ++i){
        cin >> x; ks.push_back(x);
    }
    cin >> x;
    cout << solve(x) << endl;
}
