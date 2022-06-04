
#include "auxiliares.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
const gps P = puntoGps(-33.5, -58.89996);
viaje v = {medicion(2.1, P),
           medicion(1.5, P),
           medicion(1.2, P),
           medicion(2.2, P),
           medicion(2.3, P),
           medicion(5.2, P),
           medicion(5.4, P),
           medicion(5.5, P),
           medicion(7.2, P),
           medicion(1.9, P)};



int tiempoMin(viaje viaje1){
    tiempo min = obtenerTiempo(viaje1[0]);
    for (int i = 0; i < viaje1.size()-1; i++){
        if ( obtenerTiempo(viaje1[i+1]) <= min ){
            min = obtenerTiempo(viaje1[i+1]);
        }
        cout << min  << " | " << obtenerTiempo(viaje1[i+1]) << endl;
    }
    return min;
}

tiempo tiempoTotal(viaje v) {
    tiempo t;
    tiempo x = tiempoMin(v);
    return x;
}

using namespace std;
int main(){
    cout << tiempoMin(v) << endl;
    cout << "a";
    return 0;
}