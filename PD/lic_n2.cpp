#include<bits/stdc++.h>
using namespace std;

vector<int> v, length;

int solve(int n){
    int temp, ans = 0;
    for(int i = 0; i < n; ++i){
        temp = 1;
        for(int j = 0; j < i; ++j){
            if(v[j] < v[i])
                temp = max(temp, length[j] + 1);
        }
        length.push_back(temp);
        ans = max(ans, temp);
    }
    return ans;
}

int main(){
    int n, x; cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> x; v.push_back(x);
    }

    cout << solve(n) << endl;
}
