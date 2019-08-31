#include <bits/stdc++.h>
using namespace std;

/*
https://rosettacode.org/wiki/Polynomial_long_division

In algebra, polynomial long division is an algorithm for dividing a polynomial
by another polynomial of the same or lower degree.



*/

int main() {
    // polinomio / divisor = quociente
    // polinomio % divisor = resto
    // p/d = q, p%d = r
    vector<double> p, d, q;
    size_t dp, dd, dq; // graus dos polinomios = tamanho dos vetores

    cin >> dp >> dd; // lendo grau do original e do divisor
    dq = dp - dd; // inicializando grau do quociente e do resto

    size_t bdp = dp; // backup do grau do polinomio

    p.resize(dp+1);
    d.resize(dp+1);
    q.resize(dq+1);


    for ( i = 0; i <= dp; i++ ) cin >> p[i]; // lendo coeficientes do original
    for ( i = 0; i <= dd; i++ ) cin >> d[i]; // lendo coeficientes do divisor

    // cout << "-- Procedure --" << endl << endl;

    while(dp >= dd){
        // d equals D shifted right
        d.assign(d.size(), 0);

        // para cada coeficiente do divisor
        for(size_t i = 0; i <= dD; i++) d[i+dN-dD] = D[i];

        dd = dN;

        // Print( 'd', d );

        // calculating one element of q
        q[dN-dD] = N[dN]/d[dd];

        // Print( 'q', q );

        // d equals d * q[dN-dD]
        for(size_t i = 0 ; i < dq + 1 ; i++ )
        d[i] = d[i] * q[dN-dD];

        // Print( 'd', d );

        // N equals N - d
        for(size_t i = 0 ; i < dN + 1 ; i++ )
        N[i] = N[i] - d[i];
        dN--;

        // Print( 'N', N );
        // cout << "-----------------------" << endl << endl;

    }

    for(int i = 0; i < DN; ++i) cout << q[i] << " "; cout << endl;
    for(int i = 0; i < DN; ++i) cout << r[i] << " "; cout << endl;


    // Print( 'r', r );
    // Print( 'q', q );
}
