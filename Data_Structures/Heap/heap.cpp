#include<bits/stdc++.h>
using namespace std;

int size = 0;
int v[100];

void descer_recur(int i){
    int j = i*2;

    if(j > size) return;
    if(j + 1 <= size && v[j+1] > v[j]) j++;
    if(v[i] < v[j]) swap(v[i], v[j]);
    else return;
    descer_recur(j);
}

void descer_itr(int i){
    int j;
    while(true){
        j=2*i;
        if(j > size) break;
        if(j+1 <= size && v[j+1] > v[j]) j++;
        if(v[j] > v[i]) swap(v[j],v[i]);
        else break;
        i = j;
    }
}

void remover_recur(){
    if(size==0)return;
    swap(v[1],v[size--]);
    descer_recur(1);
}

void remover_itr(){
    if(size==0)return;
    swap(v[1],v[size--]);
    descer_itr(1);
}

void subir_itr(int i){
    int j;
    while(true){
        j = i/2;
        if(j == 0) return;
        if(v[i] > v[j]) swap(v[i],v[j]);
        else return;
        i = j;
    }
}

void subir_recur(int i){
    if(i == 1) return;
    int j = i/2;
    if(v[i] > v[j]) swap(v[i], v[j]);
    else return;
    subir_recur(j);
}

void inserir_itr(int val){
    v[++size] = val;
    subir_itr(size);
}

void inserir_recur(int val){
    v[++size] = val;
    subir_recur(size);
}

void print(){
    for(int i=1; i <= size; ++i){
        printf("%d ", v[i]);
    }printf("\n");
}

bool eh_heap_max(int atual){
    if(atual > size) return true;
    int aux = atual*2;
    if(aux <= size && v[aux] > v[atual]) return false;
    aux++;
    if(aux <= size && v[aux] > v[atual]) return false;

    return min(eh_heap_max(aux), eh_heap_max(aux-1));
}

int main(){
    inserir_recur(5);
    inserir_recur(6);
    inserir_recur(7);

    print();
    if(eh_heap_max(1)) printf("Ok\n");
    else printf("Not ok\n");

    inserir_recur(8);
    inserir_recur(9);
    inserir_itr(10);

    print();
    if(eh_heap_max(1)) printf("Ok\n");
    else printf("Not ok\n");

    inserir_itr(1);
    inserir_itr(2);
    inserir_itr(95);

    print();
    if(eh_heap_max(1)) printf("Ok\n");
    else printf("Not ok\n");

    // remover_itr();
    remover_recur();
    // remover_itr();

    print();
    if(eh_heap_max(1)) printf("Ok\n");
    else printf("Not ok\n");

    remover_recur();
    remover_itr();
    remover_recur();

    print();
    if(eh_heap_max(1)) printf("Ok\n");
    else printf("Not ok\n");

    inserir_itr(100);
    remover_recur();
    inserir_recur(101);

    print();
    if(eh_heap_max(1)) printf("Ok\n");
    else printf("Not ok\n");

    inserir_recur(110);
    remover_itr();
    inserir_itr(191);

    print();
    if(eh_heap_max(1)) printf("Ok\n");
    else printf("Not ok\n");
}
