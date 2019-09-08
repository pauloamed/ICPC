#include<bits/stdc++.h>
using namespace std;

int print(int A[], int l, int r){
    printf("Current (sub)array: ");
    for(int i = l; i <= r; ++i){
        printf("%d ", A[i]);
    }
    printf("\n");
}

int _partition(int A[], int l, int r, int j){
    // particionar em relacao a val
    // retornar posicao de val
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

int random_partition(int A[], int l, int r){
    int x = rand() % (r - l + 1);
    return _partition(A, l, r, l + x);
}

int randomized_select(int A[], int l, int r, int i){
    // printf("Searching for the %d-th element\n", i);
    // print(A, l, r);


    if(l == r){
        return A[l];
    }else{
        int m = random_partition(A, l, r);
        int k = m - l + 1;

        if(i == k){
            return A[m];
        }else if(i < k){
            return randomized_select(A, l, m - 1, i);
        }else{
            return randomized_select(A, m + 1, r, i - k);
        }
    }
}

int main(){
    printf("Enter the array size: ");
    // int n; cin >> n;
    int n = 100;
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
        printf("%d-th order statistic of A = %d\n", i, randomized_select(A, 1, n, i));
    }
}
