pair<int,int> trc(vector<pair<int,int>> &v){
    int n = 1;
    for(int i = 0; i < (int) v.size(); ++i) n *= v[i].second;

    vector<int> ms(v.size());
    for(int i = 0; i < (int) ms.size(); ++i) ms[i] = n / v[i].second;

    vector<int> msi(v.size());
    for(int i = 0; i < (int) msi.size(); ++i) msi[i] = inverso(ms[i], v[i].second);

    vector<int> cs(v.size());
    for(int i = 0; i < (int) cs.size(); ++i) cs[i] = ms[i] * msi[i];

    int ans = 0;
    for(int i = 0; i < (int) v.size(); ++i){
        ans = (ans + (v[i].first * cs[i])) % n;
    }

    return {ans, n};
}
