#include <bits/stdc++.h>
#define MAXN 1010
#define x first
#define y second
#define QT_FOLHAS 1010
using namespace std;

int segt[3*QT_FOLHAS][3*QT_FOLHAS];

void build(int mynode, int l, int r, int node){
    if(l == r){ segt[mynode][node] = 0; return;} // atribuicao inicial
    int mid = (l + r)/2; // mid
    build(mynode, l, mid, (node<<1)+1); // calc build da subarv esq
    build(mynode, mid+1, r, (node<<1)+2);  // calc build da subarv dir
    
}

void build2d(int l, int r, int node){
    if(l == r){ build(node, 0, QT_FOLHAS-1, 0); return;} // atribuicao inicial
    int mid = (l + r)/2; // mid
    build2d(l, mid, (node<<1)+1); // calc build da subarv esq
    build2d(mid+1, r, (node<<1)+2);  // calc build da subarv dir
}

void update(int mynode, int l, int r, int node, int i, int val){
    if(i < l || i > r) return; // se fora do intervalo
    if(l < r){ // nao eh uma folha ainda
        int mid = (l + r)/2; // mid
        update(mynode, l, mid, (node<<1)+1, i, val); // update da subarv esq
        update(mynode, mid+1, r, (node<<1)+2, i, val); // update da subarv dir
        segt[mynode][node] = max(segt[mynode][(node<<1)+1], segt[mynode][(node<<1)+2]);
    }
    else segt[mynode][node] = val; // ta dentro, atualizo no OPERACAO
}

int query(int mynode, int l, int r, int node, int lq, int rq){
    if(rq < l || lq > r) // se tiver fora do intervalo definido pelo no
        return 0; // retorna elemento neutro
    else if(l >= lq && r <= rq) {// se tiver incluso no intervalo def pelo no
        return segt[mynode][node]; // retorna valor no no
    }
    else{
        int mid = (l + r)/2; // mid
        int left_query = query(mynode, l, mid, (node<<1)+1, lq, rq); // faz query da esq
        int right_query = query(mynode, mid+1, r, (node<<1)+2, lq, rq); // query da dir
        return max(left_query, right_query); // MERGE
    }
}

void update2d(int l, int r, int node, int i, int iimp, int val){
    if(i < l || i > r) return; // se fora do intervalo
    if(l < r){ // nao eh uma folha ainda
        int mid = (l + r)/2; // mid
        update2d(l, mid, (node<<1)+1, i, iimp, val); // update da subarv esq
        update2d(mid+1, r, (node<<1)+2, i, iimp, val); // update da subarv dir
        update(node, 0, QT_FOLHAS-1, 0, iimp, val);
    }
    else update(node, 0, QT_FOLHAS-1, 0, iimp, val); // ta dentro, atualizo no OPERACAO
}

int query2d(int l, int r, int node, int lq, int rq, int limp, int rimp){
    if(rq < l || lq > r) // se tiver fora do intervalo definido pelo no
        return 0; // retorna elemento neutro
    else if(l >= lq && r <= rq) {// se tiver incluso no intervalo def pelo no
    	return query(node, 0, QT_FOLHAS-1, 0, limp, rimp);
    }
    else{
        int mid = (l + r)/2; // mid
        int left_query = query2d(l, mid, (node<<1)+1, lq, rq, limp, rimp); // faz query da esq
        int right_query = query2d(mid+1, r, (node<<1)+2, lq, rq, limp, rimp); // query da dir
         
        return max(left_query, right_query); // MERGE
    }
}
/*
void modify(int p, int pimp, int value) {  // set value at position p
	for (segt[p += QT_FOLHAS]->update(pimp, value); p > 1; p >>= 1) 
		segt[p>>1]->update(pimp, max(segt[p]->getMax(pimp, pimp), segt[p^1]->getMax(pimp, pimp)));
}

int query_(int l, int r, int limp, int rimp) {  // sum on interval [l, r)
	int res = 0;
	for (l += QT_FOLHAS, r += QT_FOLHAS; l < r; l >>= 1, r >>= 1) {
		if (l&1) res = max(res, segt[l++]->getMax(limp, rimp));
		if (r&1) res = max(res, segt[--r]->getMax(limp, rimp));
	}
	return res;
}
*/

int main(){
	int t;
	cin >> t;
	int ii = 1;
	while(ii <= t){
		//build2d(0,QT_FOLHAS-1,0);
		memset(segt, 0, sizeof segt);
		int n;
		cin >> n;
		int ans = 0;
		for(int i = 0; i < n; i++){
			int a, b;
			cin >> a >> b;
			int k = query2d(0, QT_FOLHAS-1, 0, 0, a, 0, b);
			update2d(0, QT_FOLHAS-1, 0, a, b, k+1);
			ans = max(ans, k+1);
		}
		cout << ans << endl;
		ii++;
	}
}
