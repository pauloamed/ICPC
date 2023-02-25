#include <bits/stdc++.h>
#define MAXN ((int) 1e5)
using namespace std;
typedef pair<int, int> pii;

int n, K;
long long ans;

vector<int> e[MAXN + 10], v[MAXN + 10];
int rt[MAXN + 10], sz[MAXN + 10], chL[MAXN + 10], chR[MAXN + 10], prio[MAXN + 10];
long long keyo[MAXN + 10], lc[MAXN + 10], ld[MAXN + 10];

// 下推 lazy tag
void down(int id) {
    if (lc[id] == 0 && ld[id] == 0) return;
    long long t = lc[id] + (sz[chL[id]] + 1) * ld[id];
    keyo[id] += t;
    if (chL[id]) lc[chL[id]] += lc[id], ld[chL[id]] += ld[id];
    if (chR[id]) lc[chR[id]] += t, ld[chR[id]] += ld[id];
    lc[id] = ld[id] = 0;
}

// 求平衡树第 pos 大的值
long long query(int id, int pos) {
    assert(id);
    down(id);
    int t = sz[chL[id]] + 1;
    if (t == pos) return keyo[id];
    else if (t > pos) return query(chL[id], pos);
    else return query(chR[id], pos - t);
}

void update(int id) {
    sz[id] = sz[chL[id]] + sz[chR[id]] + 1;
}

// 无旋 treap split
pii split(int id, long long key) {
    down(id);
    if (!id) return pii(0, 0);
    if (keyo[id] <= key) {
        pii p = split(chR[id], key);
        chR[id] = p.first;
        update(id);
        return pii(id, p.second);
    } else {
        pii p = split(chL[id], key);
        chL[id] = p.second;
        update(id);
        return pii(p.first, id);
    }
}

// 无旋 treap merge
int merge(int x, int y) {
    down(x); down(y);
    if (!x && !y) return 0;
    else if (x && !y) return x;
    else if (!x && y) return y;

    if (prio[x] <= prio[y]) {
        chR[x] = merge(chR[x], y);
        update(x);
        return x;
    } else {
        chL[y] = merge(x, chL[y]);
        update(y);
        return y;
    }
}

// 启发式合并平衡树
int mix(int x, int y) {
    if (sz[x] > sz[y]) swap(x, y);
    while (x) {
        long long key = query(x, 1);
        pii p = split(x, key);
        x = p.second;
        pii q = split(y, key);
        y = merge(merge(q.first, p.first), q.second);
    }
    return y;
}

// 树 dp
void dfs(int sn, int fa) {
    rt[sn] = sn; sz[sn] = 1; prio[sn] = rand();
    for (int i = 0; i < e[sn].size(); i++) {
        int fn = e[sn][i];
        if (fn == fa) continue;
        dfs(fn, sn);
        lc[rt[fn]] -= 1LL * v[sn][i] * (K + 1);
        ld[rt[fn]] += 2LL * v[sn][i];
        rt[sn] = mix(rt[sn], rt[fn]);
    }
}

/*
vector<int> merge(vector<int> a, vector<int> b){
  vector<int> c = {0};
  int ia = 1, ib = 1;
  while(ia < a.size() || ib < b.size()) {
    if(ia == a.size()) c.push_back(b[ib++]);
    else if(ib == b.size()) c.push_back(a[ia++]);
    else{
      if(a[ia] > b[ib]) c.push_back(a[ia++]);
      else c.push_back(b[ib++]);
    }
  }
  return c;
}
 
vector<int> dp(int x, int p){
  vector<int> dp_x = {0, 0};
  for(auto [y, ec] : v[x]) if(y != p) {
    auto dp_y = dp(y, x);
    for(int j = 1; j < dp_y.size(); ++j) {
      dp_y[j] += ec * (k + 1) - 2 * ec * j;
    }
    dp_x = merge(dp_x, dp_y);
 
  }
  return dp_x;
}
*/

int main() {
    srand(time(0));
    scanf("%d%d", &n, &K);
    for (int i = 1; i < n; i++) {
        int x, y, z; scanf("%d%d%d", &x, &y, &z);
        e[x].push_back(y); v[x].push_back(z);
        e[y].push_back(x); v[y].push_back(z);
    }

    dfs(1, 0);
    for (int i = 1; i <= K; i++) ans -= query(rt[1], i);
    printf("%lld\n", ans);
    return 0;
}
