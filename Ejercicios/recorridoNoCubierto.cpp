#include "auxiliares.h"
#include <iostream>

using namespace std;

bool cubierto(viaje v0, distancia u, gps p){
    for (int i = 0; i < v0.size(); i++){
        if ((distEnKM(obtenerPosicion(v0[i]), p)*1000) < u){
            return true;
        }
    }
    return false;
}


vector<gps> recorridoNoCubierto(viaje v, recorrido r, distancia u) {
    vector<gps> resp;
    for (int i = 0; i < r.size(); i++){
        if (!cubierto(v, u, (r[i])) ) {
            resp.push_back(r[i]);
        }
    }
    // codigo

    return resp;
}

const gps P = puntoGps(-31.465027, -64.212973);
const recorrido R = {P,
                     desviarPunto(P, 1000, 0),
                     desviarPunto(P, 2000, 0),
                     desviarPunto(P, 3000, 0),
                     desviarPunto(P, 4000, 0),
                     desviarPunto(P, 5000, 0),
                     desviarPunto(P, 6000, 0),
                     desviarPunto(P, 7000, 0),
                     desviarPunto(P, 8000, 0),
                     desviarPunto(P, 9000, 0),
};

const recorrido RRulos = {P,
                          desviarPunto(P, 1000, 0),
                          desviarPunto(P, 2000, 0),
                          desviarPunto(P, 3000, 0),
                          desviarPunto(P, 4000, 0),
                          desviarPunto(P, 5000, 0),
                          desviarPunto(P, 5000, 100),
                          desviarPunto(P, 4000, 100),
                          desviarPunto(P, 3000, 100),
                          desviarPunto(P, 2000, 100),
                          desviarPunto(P, 1000, 100),
                          desviarPunto(P, 0, 0)
};

int main(){
    viaje v = {};
    vector<int> desvios(R.size(), 0);
    desvios[0] = 390;
    desvios[1] = 30;
    desvios[2] = -190;
    desvios[3] = -390;

    for(int i = 0; i < R.size(); i++){
        v.push_back(medicion(i, desviarPunto(R[i], 0, desvios[i])));
    }

    vector<gps> res = recorridoNoCubierto(v, R, 100);

    cout << res.size() << endl;
    return 0;
}


