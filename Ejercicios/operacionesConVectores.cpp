using namespace std;
#include <iostream>
#include <tuple>
#include <vector>
#include "auxiliares.cpp"
#include "definiciones.h"

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

int main(){
  gps p = make_tuple(1, 1);
  gps q = make_tuple(2, 2);
  float v_med = .5;
  //cout << obtenerLatitud(v3) << endl;
  //cout << obtenerLongitud(v3) << endl;
  //gps v4 = multiplicarPorEscalar(v1, 0.5);
  gps pq = restarGPS(q, p);
  gps pq_versor = multiplicarPorEscalar(pq, (1 / norma(pq)));
  gps pq_versor_escalado = multiplicarPorEscalar(pq_versor, v_med);
  gps r = sumarGPS(q, pq_versor_escalado);
  cout << obtenerLatitud(r) << endl;
  cout << obtenerLongitud(r) << endl;



}
