#include<bits/stdc++.h>
using namespace std;

struct neumaierSum{
    double sum = 0; // guarda o somatorio
    double c = 0; // guarda o compensador

    void operator+=(double a){ // adicionando o valor a ao acumulado

        // if(a < 0) // SOMATORIO DE REAIS NAO NEGATIVOS
        //     printf("TEM QUE SER NAO NEGATIVO POXA MAN\n");

        double t = sum + a;
        if(abs(sum) < abs(a)) swap(sum, a);
        c += (sum - t) + a;
        sum = t;
    }

    double val(){ // recuperando o valor do acumulado
        return sum + c;
    }
};
