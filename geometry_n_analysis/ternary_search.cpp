// DOMAIN IS DOUBLE
// code for max. for min, negate f
ld ternary_search(ld l, ld r) {
  const ld eps = 1e-9;
  while (r - l > eps) {
    ld m1 = l + (r - l) / 3;
    ld m2 = r - (r - l) / 3;
    ld f1 = f(m1), f2 = f(m2);
    if(f1 < f2) l = m1;
    else r = m2;
  }
  return f(l); // or l if argmax
}

// DOMAIN IS INTEGER
int ternary_search(int lo, int hi){
  while (hi - lo > 1){
    int mid = (hi + lo)>>1;
    if (f(mid) > f(mid + 1)) 
      hi = mid;
    else 
      lo = mid; 
  }
  return f(lo + 1);
}
