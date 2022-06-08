using namespace std;
#include <iostream>
#include <tuple>
#include "auxiliares.cpp"
#include "definiciones.h"

//dunno why this work, cuando ni le estoy pasando enteros ni defini
//la resta y suma entre tuplas... but allright i guess
// void swap(int &a, int &b){
//   a = a + b;
//   b = a - b;
//   a = a - b;
// }
//que esto funcione tiene mas sentido
void swap(tuple<tiempo, gps> &a, tuple<tiempo, gps> &b){
  tuple<tiempo, gps> c = a;
  a = b;
  b = c;
}

viaje ordenarViaje(viaje v){
  for (int i = 0; i < v.size() - 1; i++) {
    for (int j = i + 1; j < v.size(); j++) {
      if (obtenerTiempo(v[j]) < obtenerTiempo(v[i])) {
        swap(v[i], v[j]);
      }
    }
  }
  return v;
}

int cant_apariciones(viaje v, tuple<tiempo, gps> elem) {
  int contador = 0;
  for (int i = 0; i < v.size(); i++) {
    if (v[i] == elem) {
      contador++;
    }
  }
  return contador;
}
bool mismas_cant_apariciones(viaje v, viaje v1) {
  for (int i = 0; i < v.size(); i++) {
    if (cant_apariciones(v, v[i]) != cant_apariciones(v1, v[i])) {
      return false;
    }
  }
  return true;
}

bool mismoViaje(viaje v, viaje v_ord){
  return ((v.size() == v_ord.size()) && (mismas_cant_apariciones(v, v_ord)));
}
bool ordenadoPorTiempo(viaje v) {
  for (int i = 0; i < v.size() - 1; i++) {
    if (v[i] > v[i + 1]) {
      return false;
    }
  }
  return true;
}
bool esViajeOrdenadoPorTiempo(viaje v, viaje v_ord){
  return ((mismoViaje(v, v_ord)) && (ordenadoPorTiempo(v_ord)));
}
distancia distanciaTotal (viaje v){
    viaje v_ord = ordenarViaje(v);
    if (esViajeOrdenadoPorTiempo(v, v_ord)) {
      distancia result = 0;
      for (int i = 1 ; i < v_ord.size(); i++){
          result += distEnKM(obtenerPosicion(v_ord[i]) , obtenerPosicion(v_ord[i-1]));
      }
      return result;
    }
}


int main(){
  const gps p = puntoGps(52.3, 55.3);
  const gps p1 = puntoGps(5.3, 15.3);
  const gps p2 = puntoGps(0.3, 22.3);
  const gps p3 = puntoGps(-2.3, 10.3);
  const gps p4 = puntoGps(528.3, 525.3);
  viaje v = {
             medicion(10, p),
             medicion(2, p1),
             medicion(-11, p2),
             medicion(10, p3),
             medicion(1, p4),
            };
  viaje v1 = {
             medicion(1, p),
             medicion(2, p1),
             medicion(-11, p2),
             medicion(10, p3),
             medicion(1, p4),
            };
  viaje v_ord = ordenarViaje(v);
  for (int i = 0; i < v_ord.size(); i++){
    cout << obtenerTiempo(v_ord[i]) << endl;
    cout << obtenerLatitud(obtenerPosicion(v_ord[i])) << endl;
    cout << obtenerLongitud(obtenerPosicion(v_ord[i])) << endl;
  }
  cout << cant_apariciones(v, medicion(10, p)) << endl;
  cout << mismas_cant_apariciones(v, v_ord) << endl;
  cout << mismoViaje(v, v_ord) << endl;
  cout << distanciaTotal(v) << endl;
}
