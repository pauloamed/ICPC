void maybe_updt_lazy(int l, int r, int node){ // differs from standart sum lp
    if(lp[node] != 0){
        segt[node] += lp[node];
        if(l!=r){
            lp[(node<<1)+1] += lp[node];
            lp[(node<<1)+2] += lp[node];
        }
        lp[node] = 0;
    }
}
 
int build(int l, int r, int node) // standart rmq build
int query(int l, int r, int node, int lq, int rq) // standart rmq query
 
void update_range(int l, int r, int node, int lu, int ru, int diff){
    maybe_updt_lazy(l,r,node); // atualiza lp
    if( lu > r || l > ru ) return; //totalmente fora, nao faz updt
    if(lu <= l && r <= ru){ // totalmente dentro, nao updt nos filhos
        segt[node] += diff;
        if(l!=r){
            lp[(node<<1)+1] += diff;
            lp[(node<<1)+2] += diff;
        }
    }else{ //parcialmente dentro, nao faz lp nos filhos
        if(l==r){
            segt[node] += diff;
        }else{
        int mid = (l + r)/2;
        update_range(l, mid, (node<<1)+1, lu, ru, diff);
        update_range(mid+1, r, (node<<1)+2, lu, ru, diff);
        segt[node] = min(segt[(node<<1)+1],segt[(node<<1)+2]);
        }
    }
}
