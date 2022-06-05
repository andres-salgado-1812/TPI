
#include "auxiliares.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void swapVal(viaje &v, int d, int h){
    tuple<tiempo, gps> c = v[d];
    v[d] = v[h];
    v[h] = c;
}

tiempo findMinPositionTime(viaje &s, int d, int h) {
    int min = d;
    for(int i=d+1; i<h; i++) {
        if (obtenerTiempo(s[i]) < obtenerTiempo(s[min])) {
            min = i;
        }
    }
    return min;
}



void ordenarViaje(viaje &v){
    for (int i = 0; i < v.size()-1 ; i++){
        int minInd = findMinPositionTime(v , i , v.size());
        swapVal( v, i, minInd);
    }
}

distancia distanciaTotal (viaje vOrd){
    ordenarViaje(vOrd);
    distancia result = 0;
    for (int i=1 ; i<vOrd.size(); i++){
        result += distEnKM(obtenerPosicion(vOrd[i]) , obtenerPosicion(vOrd[i-1]));
    }
    return result;
}


int main(){
    gps p1 = puntoGps(-33, -34);
    gps p2 = desviarPunto(p1, 2000, 0);
    gps p3 = desviarPunto(p2, 2000, 0);

    viaje v = {medicion(1.6, p2),
               medicion(1.5, p1),
               medicion(1.7, p3)};

    distancia x = distanciaTotal(v);

    cout << x << endl;
    return 0;
}