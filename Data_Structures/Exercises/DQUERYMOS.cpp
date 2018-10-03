#include<bits/stdc++.h>
using namespace std;

int cont[2000000];
int N, S;

bool mosort(pair<pair<int,int>,int> A, pair<pair<int,int>,int> B){
    if (A.first.first / S != B.first.first / S)
        return (A.first.first / S) < (B.first.first / S);
    return A.first.second > B.first.second;
}

int main(){
    scanf("%d", &N);
    S = (int) sqrt(N);


    int v[N+1];
    for(int i = 0; i < N; ++i){
        scanf("%d", &v[i]);
    }

    int Q;
    scanf("%d", &Q);

    int ans[Q];
    pair<pair<int,int>,int> qs[Q];
    for(int i = 0; i < Q; ++i){
        scanf("%d %d", &qs[i].first.first, &qs[i].first.second);
        qs[i].second = i;
    }

    sort(qs, qs+Q, mosort);

    int rp = -1;
    int lp = 0;

    int trp, tlp;

    int scont = 0;

    for(int i = 0; i < Q; ++i){
        tlp = qs[i].first.first-1;
        trp = qs[i].first.second-1;

        // printf("%d %d\n", tlp, trp);

        while(rp < trp){
            ++rp;
            cont[v[rp]]++;

            if(cont[v[rp]] == 1) scont++;
        }

        while(lp < tlp){
            cont[v[lp]]--;
            if(cont[v[lp]] == 0){
                scont--;
            }
            lp++;
        }

        while(lp > tlp){
            --lp;
            cont[v[lp]]++;

            if(cont[v[lp]] == 1) scont++;
        }

        while(rp > trp){
            cont[v[rp]]--;
            if(cont[v[rp]] == 0){
                scont--;
            }
            rp--;
        }
        // printf("%d %d\n", tlp, trp);
        ans[qs[i].second] = scont;

    }

    for(int i = 0; i < Q; ++i){
        printf("%d\n", ans[i]);
    }
}
