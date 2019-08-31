#include<bits/stdc++.h>
using namespace std;

#define MAXN 100000

vector<int> v[MAXN];
int degree[MAXN];

int main(){
    int n; cin >> n;
    for(int i = 0; i < n-1; ++i){
        int a, b; cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);

        degree[a]++;
        degree[b]++;
    }

    vector<int> od;
    for(int i = 0; i < n; ++i){
        if(degree[i] == 1){
            od.push_back(i);
        }
    }

    int size = n;

    vector<int> temp;
    while(size > 2){
        for(int i = 0; i < od.size(); ++i){
            degree[od[i]]--;
            size--;
            for(int j = 0; j < v[od[i]].size(); ++j){
                if(--degree[v[od[i]][j]] == 1){
                    temp.push_back(v[od[i]][j]);
                }
            }
        }
        swap(temp, od);
        temp.clear();
    }

    cout << od[0];
    if(od.size() == 2)
        cout << " " << od[1];
    cout << endl;
}
