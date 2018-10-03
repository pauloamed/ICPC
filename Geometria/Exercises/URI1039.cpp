#include<bits/stdc++.h>
using namespace std;

int main(){
    int r1,x1,y1,r2,x2,y2;

    while(cin >> r1 >> x1 >> y1 >> r2 >> x2 >> y2){

        double temp = hypot(x1-x2, y1-y2);

        if( temp + (double) r2 <= double(r1)){
            printf("RICO\n");
        }else{
            printf("MORTO\n");
        }
    }
}
