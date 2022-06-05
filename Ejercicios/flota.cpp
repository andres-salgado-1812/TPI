#include "auxiliares.h"
#include <iostream>

using namespace std;

//PUNTO ANTERIOR DE TIEMPOS MIN Y MAX

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

//FIN DE CODIGO





bool viajeEnFranja(viaje v, tiempo t0, tiempo tf){
    tiempo tmin = tiempoMin(v);
    tiempo tmax = tiempoMax(v);
    if ( !(tmax < t0 || tmin > tf) ){
        return true;
    }
    else{
        return false;
    }
}


int flota(vector<viaje> f, tiempo t0, tiempo tf) {
    int resp = 0;
    for (int i = 0; i < f.size(); i++){
        if (viajeEnFranja(f[i] , t0, tf)){
            resp++;
        }
    }

    return resp;
}




int main(){
    vector<viaje> f = {{
                               medicion(1.5,puntoGps(2.5, 2.89996)),
                               medicion(1.7,puntoGps(2.5, 2.89997)),
                               medicion(1.9,puntoGps(2.5, 2.89998))},
                       {
                               medicion(2.5,puntoGps(2.5, 2.89996)),
                               medicion(2.6,puntoGps(2.5, 2.89997)),
                               medicion(2.7,puntoGps(2.5, 2.89998))},
                       {
                               medicion(0.5,puntoGps(2.5, 2.89996)),
                               medicion(0.6,puntoGps(2.5, 2.89997)),
                               medicion(0.7,puntoGps(2.5, 2.89998))},
    };

    cout << flota(f, 1.8,2.55) << endl;
    return 0;
}
