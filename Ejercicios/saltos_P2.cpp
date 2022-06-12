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
int cantidadDeSaltos(viaje v, grilla g){
  vector<nombre> nombres = nombresViajeEnGrilla(v, g);
  int contador = 0;
  for (int i = 0; i < nombres.size() - 1; i++) {
    if (haySalto(nombres[i], nombres[i+1])){
      contador++;
    }
  }
  return contador;
}

int main() {
  const gps p = puntoGps(.5, 1.5);
  const gps p1 = puntoGps(.6, 1.6);
  const gps p2 = puntoGps(.8, .3);
  const gps p3 = puntoGps(1.5, .3);
  const gps p4 = puntoGps(1, 1);
  viaje v = {
             medicion(1, p),
             medicion(2, p1),
             medicion(3, p2),
             medicion(4, p3),
             medicion(5, p4),
            };
  viaje v1 = {
             medicion(1, p),
             medicion(2, p1),
             medicion(-11, p2),
             medicion(10, p3),
             medicion(1, p4),
            };
  gps esq1 = puntoGps(2, 0);
  gps esq2 = puntoGps(0, 2);
  int n1 = 2;
  int m1 = 2;
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
  int asd = cantidadDeSaltos(v, g);
  cout << asd << endl;
}
