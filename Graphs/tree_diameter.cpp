vector<int> v[MAXN];
int h[MAXN];

pair<int,int> calc_altura(int x){
    pair<int,int> ans;
    ans.first = 0;
    ans.second = x;

    // printf("x: %d\n", x);

    h[x] = 0;

    for(int i = 0; i < v[x].size(); ++i){
        if(h[v[x][i]] == -1){
            auto temp = calc_altura(v[x][i]);
            if(temp.first > ans.first){
                ans = temp;
            }
        }
    }

    h[x] = ++ans.first;

    return ans;
}

int diametro(int n){
    for(int i = 0; i <= n; ++i){
        h[i] = -1;
    }

    int x = calc_altura(1).second;

    for(int i = 0; i <= n; ++i){
        h[i] = -1;
    }

    int ret = calc_altura(x).first - 1;
    // printf(">> %d\n", h[1]);
    return ret;
}
