#include<bits/stdc++.h>
using namespace std;

// estrutura pra fazer somatorio de reais nao negativos com melhor precisao
struct stableSum{
    int counter = 0; // indica quantos elementos ja foram inseridos
    vector<double> v; // vai guardar os valores adicionados. parece com aquele jogo
    // de ir juntando as potencias de 2. sempre que eu posso juntar dois de mesmo tamanho
    // (pot de 2) junto.
    // tamanho de v = quantidade de bits ativos em counter
    vector<double> pref{0}; // vai conter os prefixos de v

    void operator+=(double a){ // adicionando o valor a ao acumulado

        if(a < 0) // SOMATORIO DE REAIS NAO NEGATIVOS
            printf("TEM QUE SER NAO NEGATIVO POXA MAN\n");

        int s = ++counter; // recupera quantos valores foram agora adicionados
        // olhe pra representacao binaria de counter. como 1 com counter.
        // esse while faz exatamente essa soma

        while(s % 2 == 0){ // se eu puder juntar, junto
            a += v.back(); // junto com o ultimo (de mesmo tamanho)
            v.pop_back(); // tiro o ultimo (que acabou de se juntar com a)
            pref.pop_back(); // back de pref agora ta invalido, pq o ultimo de v saiu
            s /= 2; // olhando esse while como a soma, to fazendo o shift da casa das
            // unidades, que eh nula (pq ocorreu a soma com 1 nessa casa)
        }
        v.push_back(a); // parando de modificar v, salvo o valor q tava sendo acumulado
        pref.push_back(pref.back() + a); // atualizo o pref
    }

    double val(){ // recuperando o valor do acumulado
        return pref.back();
    }
};
