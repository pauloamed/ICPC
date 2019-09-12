// retirado de uma lib privada

//0-indexed (px,py <= MAXN-2)
void upd(int px, int py, int v){
    for(int x = px+1; x < MAXN; x += x&-x)
    for(int y = py+1; y < MAXN; y += y&-y)
        bit[x][y]+=v; // bit[x][y] = max(bit[x][y], v);
}
ll query(int px, int py){
    ll ret = 0; // int ret = MIN;
    for(int x = px+1; x > 0; x -= x&-x)
    for(int y = py+1; y > 0; y -= y&-y)
        ret += bit[x][y]; // ret = max(ret, bit[x][y]);
    return ret;
}
