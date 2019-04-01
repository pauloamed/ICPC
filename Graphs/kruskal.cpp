#include<bits/stdc++.h>
using namespace std;

#define MAXN 1000
#define pipii vector<pair<int,pair<int,int>>>

int parent[MAXN];
int size[MAXN];
pipii a;

int find(int x){
    int temp, root = x;
    while(parent[root] != root)
        root = parent[root];
    while(parent[x] != x){
        temp = parent[x];
        parent[x] = root;
        x = temp;
    }
    return root;
}

void join(int x, int y){
    x = find(x);
    y = find(y);

    if(x == y) return;
    if(size[x] > size[y]) swap(x,y);
    size[y] += size[x];
    parent[x] = y;
}

pipii kruskal(int n){
    sort(a.begin(), a.end());
    pipii ans;
    int cont = 0;
    for(int i = 0; i < a.size(); ++i){
        if(find(a[i].second.first) == find(a[i].second.second)) continue;
        join(a[i].second.first, a[i].second.second);
        ans.push_back(a[i]);
        if(ans.size() == n-1) return ans;
    }
    return pipii();
}

int main(){
    int n, m; cin >> n >> m;
    for(int i = 1; i <= n; ++i){
        parent[i] = i;
        size[i] = 1;
    }
    for(int i = 0; i < m; ++i){
        int x, y, z; cin >> x >> y >> z;
        a.push_back({z,{x,y}});
    }
    auto ans = kruskal(n);

    printf("MST:\n");
    for(int i = 0; i < ans.size(); ++i){
        printf("%d %d %d\n", ans[i].first, ans[i].second.first, ans[i].second.second);
    }
}
