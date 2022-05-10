deque<pair<int,int>> cht;

pair<double, double> intersect(pair<int,int> a, pair<int,int> b){
  double num = b.second - a.second;
  double den = a.first - b.first;
  double x = (num/den) - ((num^den) < 0 && num % den);
  return {x, a.first * x + a.second};
}

int eval(int x, int i){
  int a = cht[i].first;
  int b = cht[i].second;
  return a * x + b;
}

// If lines slopes are monotonic incresing, lines with greater slopes can 
// progressively be turned useless, given a better inserted line
void add(pair<int,int> r){
  while(cht.size() > 1){
    double a = intersect(cht[0], r).first; // intersect(cht[n-2], r).first;
    double b = intersect(cht[0], cht[1]).first; // intersect(cht[n-2], cht.back()).first;
    if(a < b) break; // a > b
    cht.pop_front(); // pop_back();
  }
  cht.push_front(r); // push_back(r);
}


// If queries are monotonic incresing, lines with lower slops will progressively
// turn useless. Same case for monotonic decreasing
int query(int x){
  int evalA = eval(x, cht.size() - 1); // eval(x, 0);
  if(cht.size() == 1) return evalA;
  else{
    int evalB = eval(x, cht.size() - 2); // eval(x, 1);
    while(evalA < evalB){ // evalA > evalB
      cht.pop_back(); // cht.pop_front();
      if(cht.size() == 1) break;
      evalA = eval(x, cht.size() - 1); // evalA = eval(x, 0);
      evalB = eval(x, cht.size() - 2); // evalB = eval(x, 1);
    }
    return eval(x, cht.size() - 1); // return eval(x, 0);
  }
}
