#include "auxiliares.h"
#include <iostream>
#include <fstream>
#include <iomanip>

//CODIGO DEL ANTERIOR PUNTO !! --> ORDENAR VIAJE
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

//FIN DEL CODIGO DEL ANTERIOR PUNTO

double velocidad(tuple<tiempo, gps> medicion1,tuple<tiempo, gps> medicion2){
    distancia distanciaEntreV = distEnKM(obtenerPosicion(medicion1), obtenerPosicion(medicion2));
    tiempo tiempoEntreV = (obtenerTiempo(medicion2) - obtenerTiempo(medicion1))/3600;
    return distanciaEntreV/tiempoEntreV;
}


bool excesoDeVelocidad(viaje v) {
    ordenarViaje(v);
    bool resp = false;
    // codigo
    for (int i = 1; i < v.size(); i++){
        if (velocidad(v[i-1], v[i]) > 80 ){
            return true;
        }
    }
    return resp;
}


using namespace std;

int main(){
    const gps P = puntoGps(-33, -34);
    const double unaHora = 3600;

    viaje v = {medicion(0.0, P),
               medicion(unaHora, desviarPunto(P, 100000, 0)),
               medicion(unaHora*2, desviarPunto(P, 200000, 0))}; // 100 KM por hora.

    cout << excesoDeVelocidad(v) << endl;

    return 0;
}