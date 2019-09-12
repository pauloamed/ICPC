#include <bits/stdc++.h>
#define x first
#define y second
#define BUFSIZE 13151597
#define QT_FOLHAS 101010
using namespace std;

struct node;
node *newNode();

struct node {
    node *left, *right;
    int lv, rv, maxi;
    node() : left(NULL), right(NULL), val(0) {}
    inline void init(int l, int r) {
        lv = l;
        rv = r;
    }
    inline void maybe_extend() {
        if (!left) {
            int m = (lv + rv) / 2;
            left = newNode();
            right = newNode();
            left->init(lv, m);
            right->init(m + 1, rv);
        }
    }
    int query(int l, int r) { // query on [l, r]
        if (r < lv || rv < l) return 0;
        if (l <= lv && rv <= r) return maxi;      
        maybe_extend();
        return max(left->query(l,r), right->query(l,r));
    }
    void update(int p, int newVal) { // update on [l, r]
        if (lv == rv) { maxi = newVal; return; } // if it is a leaf
	    maybe_extend();
	    if(p <= left->rv) left->update(p, newVal);
	    else right->update(p, newVal);
	    val = max(left->val, right->val);
    }
};
node *newNode() {
    static int bufSize = BUFSIZE;
    static node buf[(int) BUFSIZE];
    assert(bufSize);
    return &buf[--bufSize];
}
