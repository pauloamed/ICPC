#include<bits/stdc++.h>
using namespace std;

string rstack = "";

pair<int,int> select(int A[], int l, int r, int i);

int print(int A[], int l, int r){
    cout << rstack;
    printf("Current (sub)array: ");
    for(int i = l; i <= r; ++i){
        printf("%d ", A[i]);
    }
    printf("\n");
}

int _partition(int A[], int l, int r, int j){
    // particionar em relacao a val
    // retornar posicao de val

    /*
    THETA(n)
    */

    swap(A[r], A[j]);
    j = r--;

    int ll = l;

    for(; l <= r; ++l){
        if(A[l] < A[j])
            swap(A[l], A[ll++]);
    }
    swap(A[ll], A[j]);

    return ll;
}

int find_x(int A[], int l, int r){
    int num_parts = (int) ceil((r-l)/5.0); // O(1)

    int B[num_parts + 1]; // THETA(n/5)

    int i = l;
    int k = 1;
    while(i <= r){
        if(r - i + 1 >= 5){
            sort(A+i, A+i+5); // O(1), 5log5 <= 15
            B[k] = A[i+2];

            i += 5;
        }else{
            sort(A+i, A+r);  // O(1), 4log4 <= 8
            B[k] = A[i+(r - i + 1)/2];

            i = r + 1;
        }
        k++;
    }

    rstack.push_back('\t');
    int ix = select(B, 1, num_parts, (num_parts/2) + 1).second;
    rstack.pop_back();

    return ix;
}

pair<int,int> select(int A[], int l, int r, int i){
    // cout << rstack;
    // printf("Searching for the %d-th element\n", i);
    // print(A, l, r);


    if(l == r){
        return make_pair(A[l], l);
    }else{
        int m = find_x(A, l, r);
        m = _partition(A, l, r, m);
        int k = m - l + 1;

        if(i == k){
            return make_pair(A[m], m);
        }else if(i < k){
            return select(A, l, m - 1, i);
        }else{
            return select(A, m + 1, r, i - k);
        }
    }
}

int main(){
    printf("Enter the array size: ");
    int n; cin >> n;
    int A[n+1];

    unordered_set<int> s;

    for(int i = 1; i <= n; ++i){
        int x = rand() % (1000);
        while(s.count(x)){
            x = rand() % (1000);
        }
        s.insert(x);
        A[i] = x;
    }

    printf("Genereted array: ");
    for(int i = 1; i <= n; ++i){
        printf("%d ", A[i]);
    }
    printf("\n");

    ////////////////////////////////////////////////////////////////////////////
    ////////////////                 COMECA AQUI                ////////////////
    ////////////////////////////////////////////////////////////////////////////


    for(int i = 1; i <= n; ++i){
        printf("\n");
        printf("%d-th order statistic of A = %d\n", i, select(A, 1, n, i));
    }
}
