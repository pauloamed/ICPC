#include<bits/stdc++.h>
using namespace std;

#define MAXN 110000
#define K 25

int logq[MAXN];
void pre_log(){
    logq[1] = 0;
    for (int i = 2; i < MAXN; i++)
        logq[i] = logq[i/2] + 1;
}
vector<int> vals;
int st_min[MAXN][K];
int st_max[MAXN][K];
void build(int N){
    for (int i = 0; i < N; i++){
        st_min[i][0] = vals[i];
        st_max[i][0] = vals[i];
    }

    for (int j = 1; j <= K; j++){
        for (int i = 0; i + (1 << j) <= N; i++){
            st_min[i][j] = min(st_min[i][j-1], st_min[i + (1 << (j - 1))][j - 1]);
            st_max[i][j] = max(st_max[i][j-1], st_max[i + (1 << (j - 1))][j - 1]);
        }
    }
}
int query(int l, int r){
    int j = logq[r - l + 1];
    return max(st_max[l][j], st_max[r - (1 << j) + 1][j]) - min(st_min[l][j], st_min[r - (1 << j) + 1][j]);
}

int bb(int inicio, int min_tam, int n, int s){
    int l = inicio + min_tam - 1;
    int r = n-1;
    int temp;
    int m;

    while(l <= r){
        m = (l+r)/2;
        temp = query(inicio, m);

        if(temp <= s){
            if( m == n-1 ) return m;
            if(query(inicio, m+1) > s){
                return m;
            }else{
                l = m + 1;
            }
        }else r = m - 1;
    }

    return -1;
}



int segt[3*MAXN];
int sbuild(int l, int r, int node){
    if(l == r) return segt[node] = MAXN + 10;
    int mid = (l + r)/2;
    return segt[node] = min(sbuild(l, mid, (node<<1)+1),
                            sbuild(mid+1, r, (node<<1)+2));
}

void supdate(int l, int r, int node, int i, int new_val){
    if(i < l || i > r) return;
    if(l != r){
        int mid = (l + r)/2;
        supdate(l, mid, (node<<1)+1, i, new_val);
        supdate(mid+1, r, (node<<1)+2, i, new_val);
        segt[node] = min(segt[(node<<1)+1], segt[(node<<1)+2]);
    }else{
        segt[node] = new_val;
    }
}

int squery(int l, int r, int node, int lq, int rq){
    if(rq < l || lq > r) return MAXN + 10;
    else if(l >= lq && r <= rq) return segt[node];
    else{
        int mid = (l + r)/2;
        return min(squery(l, mid, (node<<1)+1, lq, rq),
                        squery(mid+1, r, (node<<1)+2, lq, rq));
    }
}

int dp_v[MAXN];
vector<int> aux;

int main(){
    int n, s, l, x;
    cin >> n >> s >> l;
    for(int i = 0; i < n; ++i){
        scanf("%d", &x);
        vals.push_back(x);
    }

    pre_log();
    build(n);

    int temp;
    int cont = 0;

    for(int i = 0; i < n; ++i){
        if(i > n-l){
            aux.push_back(-1);
        }else{
            temp = bb(i, l, n, s);
            aux.push_back(temp);
        }
    }


    sbuild(0,n,0);
    dp_v[n] = 0;
    supdate(0,n,0,n,dp_v[n]);
    for(int i = n-1; i >= 0; --i){
        dp_v[i] = MAXN + 10;
        if(aux[i] != -1){
            // printf("%d %d %d\n", i, vals[i], aux[i]);
            // cout << squery(0,n,0,i + l, aux[i]+1) << endl;
            dp_v[i] = squery(0,n,0,i + l, aux[i]+1);
            ++dp_v[i];
        }
        supdate(0,n,0,i, dp_v[i]);
    }

    if(dp_v[0] > n){
        printf("-1\n");
    }else{
        printf("%d\n", dp_v[0]);
    }

}
