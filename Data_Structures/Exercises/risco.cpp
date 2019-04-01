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
int st[MAXN][K];

int gcd(int a, int b){
    int temp;
    if(a < b) swap(a,b);
    if(b==0) return a;
    while(a%b!= 0){
        temp = b;
        b = a % b;
        a = temp;
    }
    return b;
}

void build(int N){
    for (int i = 0; i < N; i++)
        st[i][0] = vals[i];


    for (int j = 1; j <= K; j++)
        for (int i = 0; i + (1 << j) <= N; i++)
            st[i][j] = gcd(st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
}

int query(int l, int r){
    int j = logq[r - l + 1];
    return gcd(st[l][j], st[r - (1 << j) + 1][j]);
}

int bb(int inicio, int n, int x){
    int l = inicio;
    int r = n-1;
    int temp;
    int m;

    while(l <= r){
        m = (l+r)/2;
        temp = query(inicio, m);

        if(temp <= x){
            if( m == inicio ) return m;
            if(query(inicio, m-1) > x){
                return m;
            }else{
                r = m - 1;
            }
        }else l = m + 1;
    }

    return -1;
}

int main(){
    int n, l, r, x;
    cin >> n >> l >> r;
    for(int i = 0; i < n; ++i){
        scanf("%d", &x);
        vals.push_back(x);
    }

    pre_log();
    build(n);

    int temp, temp2;
    int cont = 0;

    vector<pair<int,int>> aux;
    for(int i = 0; i < n; ++i){
        temp = vals[i];
        while(true){
            temp2 = bb(i,n,temp);
            if(temp2 == -1) break;
            temp = query(i, temp2);

            if(temp <= r){
                if(temp >= l)
                    aux.push_back({temp, temp2});
                else
                    break;
            }
            temp--;
        }
        for(int j = 0; j < aux.size(); ++j){
            if(j == 0)
                cont += (n-aux[j].second) * (r-aux[j].first+1);
            else if(j == aux.size()-1)
                cont += (n-aux[j].second) * (aux[j-1].first-l);
            else
                cont += (n-aux[j].second) * (aux[j-1].first-aux[j].first);
            // cout << aux[j].first << " " << aux[j].second << " " << endl;
        }
        aux.clear();
    }
    cout << cont << endl;
}
