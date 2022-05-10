#include<bits/stdc++.h>
using namespace std;

// funcao que retorna #raizes e modifica out com as raizes
// a gnt quer evitar (-b+sqrt(delta)) por conta do erro relativo
// se ambos forem de magnitude 10^8, eles tem um erro relativo associado
// que, sera mantido num numero de magnitude 10^0 (o que nao queremos)
int quadRoots(double a, double b, pair<double,double> &out){
    if(a == 0) return -1; // se nao for quadratica
    double delta = b*b - 4*a*c; // delta
    if(delta < 0) return 0; // se delta for negativo, n tem raiz real
    // dependendo do sinal de b, usamos a formula alternativa (que evita)
    // o problema descrito em cada um dos dois casos
    if(b >= 0){
        out.first = (-b-sqrt(delta))/(2*a); // dois neg ficando neg
        out.second = (2*c)/(-b-sqrt(delta)); // dois neg ficando neg
    }else{
        out.first = (2*c)/(-b+sqrt(delta));  // dois pos ficando pos
        out.second = (-b+sqrt(delta))/(2*a);  // dois pos ficando pos
    }
    return 1 + (disc > 0);
}
