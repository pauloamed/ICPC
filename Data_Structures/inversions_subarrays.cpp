// Counting all inversions on all subarrays
long long inversoes_subarrays(){
    long long ans(0);
    for(int i = size; i > 0; i--){
        ans = (ans + (i * query( v[i], bit_v )));
        update( v[i], (size - i + 1), bit_v );
    }
    return ans;
}
 
