// keeping updates in the structure (1)
void solve(int L, int R, vector<int> on){
  if(L == R || on.empty()){
    for(auto q_i : on) ans[q_i] = L;
  }else{
    int mid = (L + R) / 2;

    dsu.check();
    for(int i = L; i <= mid; ++i){
      auto [a, b] = evs[i];
      dsu.onion(a, b);
    }

    vector<int> done, undone;
    for(auto q_i : on){
      auto [a, b, k] = qrs[q_i];
      int tot = dsu.sizes[dsu.find(a)];
      if(dsu.find(a) != dsu.find(b)){
        tot += dsu.sizes[dsu.find(b)];
      }
      if(tot >= k) done.push_back(q_i);
      else undone.push_back(q_i);
    }
    
    solve(mid + 1, R, undone);
    dsu.rollback();
    solve(L, mid, done);
  }
}

// updating the predicate
void solve(int L, int R, vector<int> on){
  if(L == R || on.empty()){
    for(auto q_i : on) ans[q_i] = L;
  }else{
    int mid = (L + R) / 2;

    for(int i = L; i <= mid; ++i){
      for(auto [l, r, x] : evs[i])
        bit.range_update(l, r, x);
    }

    vector<int> done, undone;
    for(auto i : on){
      int sum = 0;
      for(auto pos : cand2pos[i]){
        sum += bit.query(pos);
        if(sum >= goal[i]) break;
      }
      if(sum >= goal[i]) done.push_back(i);
      else{
        goal[i] -= sum;
        undone.push_back(i);
      }
    }

    for(int i = L; i <= mid; ++i){
      for(auto [l, r, x] : evs[i])
        bit.range_update(l, r, -x);
    }
    
    solve(L, mid, done);
    solve(mid + 1, R, undone);
  }
}

// extra dimension
void solve(int L, int R, vector<int> q_on, vector<Event> e_on){
  if(L == R || q_on.empty()){
    for(auto q_i : q_on) ans[q_i] = L;
  }else{
    int mid = (L + R) / 2;

    vector<int> q_done, q_undone;
    int last_ev = 0;
    for(auto qi : q_on){
      auto &[T, l, r, k] = qs[qi];

      // process all events before query w/ X <= mid
      while(last_ev < e_on.size()){
        if(e_on[last_ev].t > T) break; // if equal, break?
        auto [t, pos, status, val] = e_on[last_ev];
        if(val <= mid) bit.update(pos, status);
        last_ev++;
      }

      // eval query and partition into left/right
      int eval_q = bit.query(r) - bit.query(l - 1);
      if(eval_q >= k) q_done.push_back(qi);
      else{
        k -= eval_q;
        q_undone.push_back(qi);
      }
    }   

    vector<Event> e_left, e_right;
    for(int i = 0; i < e_on.size(); ++i){
      auto [t, pos, status, val] = e_on[i];

      // partition events indexed by BB search dimension
      if(val <= mid) e_left.push_back(e_on[i]);
      else e_right.push_back(e_on[i]);

      // unprocess updts in [L;mid]
      if(i < last_ev && val <= mid) bit.update(pos, -status);
    }

    solve(L, mid, q_done, e_left);
    solve(mid + 1, R, q_undone, e_right);
  }
}
