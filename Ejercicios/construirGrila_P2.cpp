using namespace std;
#include <iostream>
#include <tuple>
#include <vector>
#include "auxiliares.cpp"
#include "definiciones.h"

gps obtenerEsquinaSup(celda c){
  return get<0>(c);
}
gps obtenerEsquinaInf(celda c){
  return get<1>(c);
}
nombre obtenerNombre(celda c){
  return get<2>(c);
}

grilla construirGrilla(int n, int m, gps esq1, gps esq2) {
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

void imprimirGrilla(grilla g) {
  for (int i = 0; i < g.size(); i++) {
    float latSup = obtenerLatitud(obtenerEsquinaSup(g[i]));
    float longSup = obtenerLongitud(obtenerEsquinaSup(g[i]));
    float latInf = obtenerLatitud(obtenerEsquinaInf(g[i]));
    float longInf = obtenerLongitud(obtenerEsquinaInf(g[i]));
    int n = get<0>(obtenerNombre(g[i]));
    int m = get<1>(obtenerNombre(g[i]));
    cout << "seq<(" << latSup << ", " << longSup << "), " <<
    "(" << latInf << ", " << longInf << "), " << "(" << n <<
    ", "<< m << ")>" << endl;
  }
}

int main(){
  gps esq1 = puntoGps(2,0);
  gps esq2 = puntoGps(0,2);
  int n1 = 2;
  int m1 = 2;
  grilla g = construirGrilla(n1, m1, esq1, esq2);
  imprimirGrilla(g);
}
