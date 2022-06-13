#include "ejercicios.h"
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

/******++++**************************** EJERCICIO tiempoTotal ***********+++***********************/
/*
 Se ve que tiempo total es O(n) ya que sus funciones (NO loops anidados) tienen complejidad O(n), pero
 su suma es igual a O(n), dependen de la longitud de la lista siendo n la misma.
  */
tiempo tiempoTotal(viaje v) {
    tiempo t;
    t = tiempoMax(v) - tiempoMin(v);
    return t;
}

/************++*********************** EJERCICIO distanciaTotal ************++*********************/
/*
Se ve que es O(n^2) debido al selection sort que tiene esa complejidad
  */
distancia distanciaTotal(viaje vOrd) {
    ordenarViaje(vOrd);
    distancia result = 0;
    for (int i=1 ; i<vOrd.size(); i++){
        result += distEnKM(obtenerPosicion(vOrd[i]) , obtenerPosicion(vOrd[i-1]));
    }
    return result;
}

/*****************************+***** EJERCICIO excesoDeVelocidad **********************************/
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

/************************************ EJERCICIO recorridoCubierto *******************************/
/*
 TIene complejidad O(n x m) ya que la función cubierto, recorre viaje, que seria complejidad m,
 y esta función es un bucle anidado, a el for el cual recorre los elementos viaje, este tiene
 complejidad O(n) por lo tanto la complejidad total es O(n) * O(m) = O(n x m)
  */
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

/***************************************** EJERCICIO flota ***************************************/
int flota(vector<viaje> f, tiempo t0, tiempo tf) {
    int resp = 0;
    for (int i = 0; i < f.size(); i++){
        if (viajeEnFranja(f[i] , t0, tf)){
            resp++;
        }
    }

    return resp;
}

/************************************** EJERCICIO construirGrilla *******************************/

grilla construirGrilla(gps esq1, gps esq2, int n, int m) {
    float base = (obtenerLongitud(esq2) - obtenerLongitud(esq1)) / m;
    float altura = (obtenerLatitud(esq1) - obtenerLatitud(esq2)) / n;
    grilla g;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            float latSup = obtenerLatitud(esq1) - altura * (i - 1);
            float longSup = obtenerLongitud(esq1) + base * (j - 1);
            float latInf = obtenerLatitud(esq1) - altura * (i);
            float longInf = obtenerLongitud(esq1) + base * (j);
            gps esqSup = puntoGps(latSup, longSup);
            gps esqInf = puntoGps(latInf, longInf);
            nombre nom = make_tuple(i, j);
            celda c = make_tuple(esqSup, esqInf, nom);
            g.push_back(c);
        }
    }
    return g;
}

/************************************* EJERCICIO cantidadDeSaltos ******************************/
int cantidadDeSaltos(grilla g, viaje v) {
    vector<nombre> nombres = nombresViajeEnGrilla(v, g);
    int contador = 0;
    for (int i = 0; i < nombres.size() - 1; i++) {
        if (haySalto(nombres[i], nombres[i+1])){
            contador++;
        }
    }
    return contador;
}


/************************************* EJERCICIO corregirViaje ******************************/



void corregirViaje(viaje& v, vector<tiempo> errores){
    for (int i = 0; i < errores.size(); i++){
        for (int k = 0; k < v.size(); k++){
            if (obtenerTiempo(v[k]) == (errores[i])){
                corregirPunto(v, k);
            }
        }
    }
    return;
}
