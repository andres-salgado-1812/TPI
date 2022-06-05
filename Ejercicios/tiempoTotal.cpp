
#include "auxiliares.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
const gps P = puntoGps(-33.5, -58.89996);
viaje v = {medicion(1.1, P),
           medicion(1.5, P),
           medicion(1.2, P),
           medicion(2.2, P),
           medicion(2.3, P),
           medicion(5.2, P),
           medicion(5.4, P),
           medicion(5.5, P),
           medicion(7.2, P),
           medicion(1.9, P)};



tiempo tiempoMin(viaje viaje1){
    tiempo min = obtenerTiempo(viaje1[0]);
    for (int i = 0; i < viaje1.size()-1; i++){
        if ( obtenerTiempo(viaje1[i+1]) <= min ){
            min = obtenerTiempo(viaje1[i+1]);
        }
    }
    return min;
}

tiempo tiempoMax(viaje viaje1){
    tiempo max = obtenerTiempo(viaje1[0]);
    for (int i = 0; i < viaje1.size()-1; i++){
        if ( obtenerTiempo(viaje1[i+1]) >= max ){
            max = obtenerTiempo(viaje1[i+1]);
        }
    }
    return max;
}


tiempo tiempoTotal(viaje v) {
    tiempo t;
    t = tiempoMax(v) - tiempoMin(v);
    return t;
}

using namespace std;
int main(){
    cout << tiempoMin(v) <<" || " <<  tiempoMax(v) << endl;
    cout << tiempoTotal(v) << " "<< endl;
    return 0;
}