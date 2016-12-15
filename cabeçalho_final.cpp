#ifndef FUNCTION_HPP
#define FUNCTION_HPP
#include <iostream>
#include "distance.hpp"

using namespace std;

void distancia_simples(void);
void bloco(void);

int main(){
    int x=1;
    do{
        cout << "[1] -> Calculo de distancia simples" << endl;
        cout << "[2] -> Calculo em bloco" << endl;
        cout << "[0] -> Sair" << endl;
        cin >> x;

        if (x == 1){
            distancia_simples();
        }
        else if(x == 2){
            distancia_bloco();
        }
        else if(x == 0){
            return 0;
        }
    }
    while(x==1 || x==2 || x==0);
    cout << "Comando Invalido" << endl;
return 0;
}
#endif
