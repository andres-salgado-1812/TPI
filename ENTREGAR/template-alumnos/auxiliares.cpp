#include <algorithm>
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

const double pi = 3.14;
double radioTierra = 6378;

double obtenerLatitud(gps posicion) {
    return get<0>(posicion);
}

double obtenerLongitud(gps posicion) {
    return get<1>(posicion);
}

gps obtenerPosicion(tuple<tiempo, gps> medicion) {
    return get<1>(medicion);
}

tiempo obtenerTiempo(tuple<tiempo, gps> medicion) {
    return get<0>(medicion);
}
double distEnKM(gps posicion1, gps posicion2) {
    double latitud1 = obtenerLatitud(posicion1);
    double latitud2 = obtenerLatitud(posicion2);
    double longitud1 = obtenerLongitud(posicion1);
    double longitud2 = obtenerLongitud(posicion2);

    // obtengo la distancia
    double distanciaLatitud = (latitud2 - latitud1) * pi / 180.0;
    double distanciaLongitud = (longitud2 - longitud1) * pi / 180.0;

    // paso las latitudes a radianes
    latitud1 = (latitud1) * pi / 180.0;
    latitud2 = (latitud2) * pi / 180.0;

    // aplico la formula
    double a = pow(sin(distanciaLatitud / 2), 2) +
               pow(sin(distanciaLongitud / 2), 2) *
               cos(latitud1) * cos(latitud2);

    double c = 2 * asin(sqrt(a));
    return radioTierra * c;
}

gps desviarPunto(gps p, double desvioMtsLatitud, double desvioMtsLongitud){
    double lat = obtenerLatitud(p);
    double lon = obtenerLongitud(p);

    double dx = desvioMtsLatitud / 1000;
    double dy = desvioMtsLongitud / 1000;
    double new_latitude = lat + (dx / radioTierra) * (180 / pi);
    double new_longitude = lon + (dy / radioTierra) * (180 / pi) / cos(lat * pi / 180);
    return puntoGps(new_latitude, new_longitude);

}


gps puntoGps(double latitud, double longitud) {
    return make_tuple(latitud, longitud);
}

tuple<tiempo, gps> medicion(tiempo t, gps g) {
    return make_tuple(t, g);
}

void guardarGrillaEnArchivo(grilla g, string nombreArchivo){
    ofstream myfile;
    float esq1_lat, esq2_lat, esq1_lng, esq2_lng;
    int name_0, name_1;

    myfile.open(nombreArchivo);
    myfile << std::fixed << std::setprecision(5);
    for(int i = 0; i < g.size(); i++){
        esq1_lat = get<0>(get<0>(g[i]));
        esq1_lng = get<1>(get<0>(g[i]));

        esq2_lat = get<0>(get<1>(g[i]));
        esq2_lng = get<1>(get<1>(g[i]));

        name_0 = get<0>(get<2>(g[i]));
        name_1 = get<1>(get<2>(g[i]));

        myfile << esq1_lat << "\t"
               << esq1_lng << "\t"
               << esq2_lat << "\t"
               << esq2_lng << "\t"
               << "(" << name_0 << "," << name_1 << ")"
               << endl;

    }
    myfile.close();

}

void guardarRecorridosEnArchivo(vector<recorrido> recorridos, string nombreArchivo){
    ofstream myfile;
    float lat, lng;

    myfile.open(nombreArchivo);
    myfile << std::fixed << std::setprecision(5);
    for(int i = 0; i < recorridos.size(); i++){
        for(int k = 0; k < recorridos[i].size(); k++){
            lat= get<0>(recorridos[i][k]);
            lng= get<1>(recorridos[i][k]);

            myfile << i << "\t"
                   << lat << "\t"
                   << lng << endl;
        }
    }
    myfile.close();

}

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

double velocidad(tuple<tiempo, gps> medicion1,tuple<tiempo, gps> medicion2){
    distancia distanciaEntreV = distEnKM(obtenerPosicion(medicion1), obtenerPosicion(medicion2));
    tiempo tiempoEntreV = (obtenerTiempo(medicion2) - obtenerTiempo(medicion1))/3600;
    return distanciaEntreV/tiempoEntreV;
}

bool cubierto(viaje v0, distancia u, gps p){
    for (int i = 0; i < v0.size(); i++){
        if ((distEnKM(obtenerPosicion(v0[i]), p)*1000) < u * 1000){
            return true;
        }
    }
    return false;
}
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

gps obtenerEsquinaSup(celda c){
    return get<0>(c);
}
gps obtenerEsquinaInf(celda c){
    return get<1>(c);
}
nombre obtenerNombre(celda c){
    return get<2>(c);
}


bool contenidoEnCelda(tuple<tiempo, gps> medicion, celda cel){
    float lat_med = obtenerLatitud(obtenerPosicion(medicion));
    float long_med = obtenerLongitud(obtenerPosicion(medicion));
    float lat_esqSup_cel = obtenerLatitud(obtenerEsquinaSup(cel));
    float long_esqSup_cel = obtenerLongitud(obtenerEsquinaSup(cel));
    float lat_esqInf_cel = obtenerLatitud(obtenerEsquinaInf(cel));
    float long_esqInf_cel = obtenerLongitud(obtenerEsquinaInf(cel));
    // return ((long_esqSup_cel <= long_med) && (long_med < long_esqInf_cel));
    //cout << long_esqSup_cel << " <=" << long_med << " <= " << long_esqInf_cel << endl;
    //bool decidir = ((long_esqSup_cel <= long_med) && (long_med <= long_esqInf_cel));
    bool decidir = (long_esqSup_cel <= long_med) && (long_esqInf_cel);
    // cout << decidir << endl;
    // cout << lat_esqInf_cel << ", " << lat_med << ", " << lat_esqSup_cel << endl;
    // cout << (((long_esqSup_cel <= long_med) && (long_med <= long_esqInf_cel)) &&
    //         ((lat_esqInf_cel <= lat_med) && (lat_med <= lat_esqSup_cel))) << endl;
    return ((long_esqSup_cel <= long_med) && (long_med <= long_esqInf_cel) &&
            (lat_esqInf_cel <= lat_med) && (lat_med <= lat_esqSup_cel));

}
bool haySalto(nombre n1, nombre n2) {
    int n1_0 = get<0>(n1);
    int n1_1 = get<1>(n1);
    int n2_0 = get<0>(n2);
    int n2_1 = get<1>(n2);
    float distanciaNombres = sqrt((n1_0 - n2_0)^2 + (n1_1 - n2_1)^2);
    return (distanciaNombres > 1);
}
vector<nombre> nombresViajeEnGrilla(viaje v, grilla g){
    viaje v_ord = ordenarViaje2(v);
    vector<nombre> nombresViajeEnGrilla;
    for (int i = 0; i < v_ord.size(); i++) {
        for (int j = 0; j < g.size(); j++) {
            if (contenidoEnCelda(v_ord[i], g[j])){
                nombresViajeEnGrilla.push_back(obtenerNombre(g[j]));
            }
        }
    }
    return nombresViajeEnGrilla;
}

float norma(gps v){
    return sqrt(pow(get<0>(v), 2) + pow(get<1>(v), 2));
}
gps sumarGPS(gps p1, gps p2){
    float px = obtenerLatitud(p1) + obtenerLatitud(p2);
    float py = obtenerLongitud(p1) + obtenerLongitud(p2);
    gps res = make_tuple(px, py);
    return res;
}
gps restarGPS(gps p1, gps p2){
    float px = obtenerLatitud(p1) - obtenerLatitud(p2);
    float py = obtenerLongitud(p1) - obtenerLongitud(p2);
    gps res = make_tuple(px, py);
    return res;
}
gps multiplicarPorEscalar(gps p, float k){
    float px = obtenerLatitud(p) * k;
    float py = obtenerLongitud(p) * k;
    gps res = make_tuple(px, py);
    return res;
}


tuple<tiempo, gps> generarMedicion(tiempo tiempoDelError , gps p, gps q, float v_med, gps desde){
    gps pq = restarGPS(q, p);
    gps pq_versor = multiplicarPorEscalar(pq, (1 / norma(pq)));
    gps pq_versor_escalado = multiplicarPorEscalar(pq_versor, v_med);
    gps r = sumarGPS(desde, pq_versor_escalado);
    tuple<tiempo,gps> medicionCorregida = make_tuple(tiempoDelError, r);
    return medicionCorregida;
}


void corregirPunto(viaje& v, int k){
    tuple<tiempo, gps> puntoCorrecto1 = v[0];
    tuple<tiempo, gps> puntoCorrecto2 = v[0];
    for(int i = 0; i < v.size(); i++){
        if(abs(obtenerTiempo(v[i]) - obtenerTiempo(v[k])) < abs(obtenerTiempo(puntoCorrecto1) - obtenerTiempo(v[k])) &&
           (obtenerTiempo(v[i]) != obtenerTiempo(v[k]))){
            puntoCorrecto1 = v[i];
        }
    }
    for(int i = 0; i < v.size(); i++){
        if(abs(obtenerTiempo(v[i]) - obtenerTiempo(v[k])) < abs(obtenerTiempo(puntoCorrecto2) - obtenerTiempo(v[k])) && (obtenerTiempo(v[i]) != obtenerTiempo(puntoCorrecto1)) &&
           (obtenerTiempo(v[i]) != obtenerTiempo(v[k]))) {
            puntoCorrecto2 = v[i];
        }
    }
    double v_media = ((distEnKM(obtenerPosicion(puntoCorrecto1), obtenerPosicion(puntoCorrecto2)))/1000)/(abs(obtenerTiempo(puntoCorrecto2)- obtenerTiempo(puntoCorrecto1)));
    //generarMedicion(obtenerTiempo(v[k]), obtenerPosicion(v[k]), obtenerPosicion(puntoCorrecto1), obtenerPosicion(puntoCorrecto2));
    if (obtenerTiempo(v[k]) < obtenerTiempo(puntoCorrecto1) && obtenerTiempo(v[k]) < obtenerTiempo(puntoCorrecto2)){
        v[k] =  generarMedicion(obtenerTiempo(v[k]), obtenerPosicion(puntoCorrecto2) , obtenerPosicion(puntoCorrecto1), v_media, obtenerPosicion(puntoCorrecto2));
    }
    else if (obtenerTiempo(v[k]) > obtenerTiempo(puntoCorrecto1) && obtenerTiempo(v[k]) < obtenerTiempo(puntoCorrecto2)){
        v[k] = generarMedicion(obtenerTiempo(v[k]),obtenerPosicion(puntoCorrecto1) , obtenerPosicion(puntoCorrecto2), v_media, obtenerPosicion(puntoCorrecto1));
    }
    else if (obtenerTiempo(v[k]) > obtenerTiempo(puntoCorrecto1) && obtenerTiempo(v[k]) > obtenerTiempo(puntoCorrecto2)){
        v[k] = generarMedicion(obtenerTiempo(v[k]),obtenerPosicion(puntoCorrecto2) , obtenerPosicion(puntoCorrecto1), v_media, obtenerPosicion(puntoCorrecto1));
    }
    //CORREGIR MEDIANTE ESTOS PUNTOS
}
