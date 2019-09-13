bool mosort(pair<pair<int,int>,int> A, pair<pair<int,int>,int> B){
    if (A.first.first / S != B.first.first / S)
        return (A.first.first / S) < (B.first.first / S);
    return A.first.second > B.first.second;
}

sort(qs, qs+Q, mosort);
