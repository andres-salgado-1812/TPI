using namespace std;
#include <iostream>
#include <tuple>
#include "definiciones.h"
#include "auxiliares.h"





int main() {
  tiempo t = 1.5;
  //cout << t << endl;
  gps gps1 = make_tuple(2,3);
  gps gps2 = make_tuple(10,30);
  gps gps3 = make_tuple(20,30);
  tuple<tiempo, gps> elem_viaje = make_tuple(t, gps1);
  tuple<tiempo, gps> elem_viaje1 = make_tuple(2.5, gps2);
  tuple<tiempo, gps> elem_viaj2 = make_tuple(3, gps3);
  //viaje v1 = vector<make_tuple(t, gps1)>;
  viaje v1 = {elem_viaje};
  //viaje v2 = vector<elem_viaje>;
  //v1[0] = elem_viaje;
  cout << get<0>(v1[0]) << endl;
  //para acceder al primer punto del gps del viaje
  cout << get<0>(get<1>(v1[0])) << endl;
  //para acceder al segundo punto del gps del viaje
  cout << get<1>(get<1>(v1[0])) << endl;
  //vector<int> v(5, 1);
  // v[0] = t;
  // v[1] = 52.5;
  // v[2] = 26.2;

}
