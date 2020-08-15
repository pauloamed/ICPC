// CODIGO PRA MAX
// PRA MIN TEM QUE TESTAR AINDA
// A LINHA 19 DEVE MUDAR PRA <= E NAO SEI SE A ORDENACAO PRECISA MUDAR DE CRITERIO

// TESTADO NA QUESTAO SACANA: https://codeforces.com/contest/1366/problem/F

vector<pair<int,int>> ch;
vector<pair<int,int>> lines;


double intersection(pair<int,int> a, pair<int,int> b){
    // interseciton between lines a and b
    int num = b.second - a.second;
    int den = a.first - b.first;
    return num / (den * 1.0);
}

void maybeAdd(int i){
    while(ch.size()){
        if(ch.size() == 1){
            if(lines[i].second >= lines[ch[0].second].second) ch.pop_back();
            else break;
        }else{
            int penultimateLineIndex = ch[((int) ch.size()) - 2].second;
            int newIntersect = ceil(intersection(lines[penultimateLineIndex], lines[i]));
            if(newIntersect <= ch.back().first) ch.pop_back();
            else break;
        }
    }
    if(ch.empty()) ch.push_back({0, i});
    else{
        double intersec = intersection(lines[ch.back().second], lines[i]);
        ch.push_back({ceil(intersec), i});
    }
}

void buildCHT(){
    sort(lines.begin(), lines.end());

    vector<pair<int,int>> filteredLines;
    filteredLines.push_back(lines[0]);
    for(int i = 1; i < lines.size(); ++i){
        if(lines[i].first == filteredLines.back().first){
            if(lines[i].second >= filteredLines.back().second){
                filteredLines.pop_back();
                filteredLines.push_back(lines[i]);
            }
        }else{
            filteredLines.push_back(lines[i]);
        }
    }
    swap(lines, filteredLines);

    for(int i = 0; i < lines.size(); ++i){
        maybeAdd(i);
    }
}


int getLineId(int x){
    // achar ultima posicao menor que x
    int ans = 0;
    int pot2 = (1 << 20);
    while(pot2){
        int maybeAns = ans + pot2;
        if(maybeAns < ch.size() && ch[maybeAns].first <= x) ans = maybeAns;
        pot2 /= 2;
    }
    return ans;
}
