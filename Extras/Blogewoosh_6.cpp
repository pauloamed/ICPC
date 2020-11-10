/*
https://codeforces.com/contest/1101/problem/F
https://codeforces.com/blog/entry/62602
vetor de tamanho M, achar o valor maximo dele com queries do tipo query(i, v) : (a[i] <= v)?

dica de lukkka
*/


#include<bits/stdc++.h>
using namespace std;

#define int long long
#define tupla tuple<int,int,int,int>
#define MAXVAL 1e18

random_device rd;
mt19937 g(rd());

vector<int> cities;
bool pred(tupla &truck, int tank){
    if(tank == -1) return false;
    int startingCity = get<0>(truck) - 1;
    int finishingCity = get<1>(truck) - 1;
    int fuelConsumption = get<2>(truck);
    int possibleRefuelings = get<3>(truck);

    int currTank = tank;
    for(int i = startingCity; i < finishingCity; ++i){
        int distance = cities[i + 1] - cities[i];
        int totCons = distance * fuelConsumption;

        if(totCons > currTank){
            if(possibleRefuelings > 0) possibleRefuelings--;
            else return false;
            currTank = tank;
            if(totCons > currTank) return false;
        }
        currTank -= totCons;
    }
    return true;
}

int findNewCurrAns(tupla &truck){
    // busca binaria
    int ans = 0;
    int pot2 = (1LL << 60);

    while(pot2){
        if(pot2 <= MAXVAL - ans){
            int maybeAns = ans + pot2;
            if(!pred(truck, maybeAns)) ans = maybeAns;
        }
        pot2 /= 2;
    }
    return ans + 1;
}

int32_t main(){
    int n, m; scanf("%lld %lld", &n, &m);

    cities = vector<int>(n);
    for(auto &x : cities) scanf("%lld", &x);
    sort(cities.begin(), cities.end());

    vector<tupla> trucks;
    for(int i = 0; i < m; ++i){
        int s, f, c, r;
        scanf("%lld %lld %lld %lld", &s, &f, &c, &r);
        trucks.push_back(make_tuple(s, f, c, r));
    }
    shuffle(trucks.begin(), trucks.end(), g);

    int currAns = -1;
    for(int i = 0; i < m; ++i){
        if(pred(trucks[i], currAns)){
            // se passa com currAns no tanque
            continue;
        }else{
            // se nao consegue passar com currAns no tanque
            currAns = findNewCurrAns(trucks[i]);
        }
    }
    printf("%lld\n", currAns);
}
