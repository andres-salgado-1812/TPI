using namespace std;
#include <iostream>
#include <tuple>
#include <vector>
#include "definiciones.h"
#include "auxiliares.cpp"
#include "auxiliaresPropias.cpp"

bool contenidoEnCelda(tuple<tiempo, gps> medicion, celda cel){
  float lat_med = obtenerLatitud(obtenerPosicion(medicion));
  float long_med = obtenerLongitud(obtenerPosicion(medicion));
  float lat_esqSup_cel = obtenerLatitud(obtenerEsquinaSup(cel));
  float long_esqSup_cel = obtenerLongitud(obtenerEsquinaSup(cel));
  float lat_esqInf_cel = obtenerLatitud(obtenerEsquinaInf(cel));
  float long_esqInf_cel = obtenerLongitud(obtenerEsquinaInf(cel));
  return ((long_esqSup_cel <= long_med) && (long_med < long_esqInf_cel));
  // return ((long_esqSup_cel <= long_med) && (long_med <= long_esqInf_cel) &&
  //         (lat_esqInf_cel <= lat_med) && (lat_med <= lat_esqSup_cel));
}

vector<nombre> nombresViajeEnGrilla(viaje v, grilla g){
  viaje v_ord = ordenarViaje(v);
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

int main() {
  const gps p = puntoGps(-20, 55.3);
  const gps p1 = puntoGps(5.3, 15.3);
  const gps p2 = puntoGps(10.3, 10.3);
  const gps p3 = puntoGps(-2.3, 10.3);
  const gps p4 = puntoGps(19.5, 19.5);
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
  gps esq1 = puntoGps(20, 20);
  gps esq2 = puntoGps(-20, -20);
  int n1 = 4;
  int m1 = 4;
  grilla g = construirGrilla(n1, m1, esq1, esq2);
  imprimirGrilla(g);
  viaje v_ord = ordenarViaje(v);
  //imprimirViaje(v_ord);
  // for (int i = 0; i < v_ord.size(); i++){
  //   cout << obtenerTiempo(v_ord[i]) << endl;
  //   cout << obtenerLatitud(obtenerPosicion(v_ord[i])) << endl;
  //   cout << obtenerLongitud(obtenerPosicion(v_ord[i])) << endl;
  // }
  vector<nombre> vNom = nombresViajeEnGrilla(v, g);
  cout << vNom.size() << endl;
  for (int i = 0; i < vNom.size(); i++) {
    cout << get<0>(vNom[i]) << ", " << get<0>(vNom[i]) << " ";
  }
}
