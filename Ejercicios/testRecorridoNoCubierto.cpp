const gps p1 = puntoGps(52.3, 55.3);
const gps p2 = puntoGps(5.3, 15.3);
const gps p3 = puntoGps(0.3, 22.3);
const gps p4 = puntoGps(-2.3, 10.3);
const gps p5 = puntoGps(28.3, 25.3);
viaje v1 = {
           medicion(1, p1),
           medicion(2, p2),
           medicion(3, p3),
           medicion(10, p4),
           medicion(11, p5),
          };
recorrido r = {p1, p2, p3, p4, p5};
float radio = 100;
//esperamos que todos los puntos del recorrido esten cubiertos
//por este viaje
vector<gps> res = recorridoNoCubierto(v1, r, radio);
cout << res.size() << endl;  //efectivamente no hay ningun punto no cubierto
viaje v2 = {
           medicion(1, p1),
           medicion(2, p2),
           medicion(3, p3)
          };
//esperamos que dos de los puntos del recorrido NO esten cubiertos
//por este viaje
vector<gps> res1 = recorridoNoCubierto(v2, r, radio);
cout << res1.size() << endl;  //efectivamente hay dos puntos no cubiertos
