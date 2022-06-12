//exceso de velocidad
const gps p1 = puntoGps(52.3, 52.332);
const gps p2 = puntoGps(52.3, 52.333);
const gps p3 = puntoGps(52.3, 52.334);
viaje v_noExceso = {
           medicion(1, p1),
           medicion(1000, p2),
           medicion(10000, p3),
          };
const gps p4 = puntoGps(0.3, 22.3);
const gps p5 = puntoGps(-2.3, 10.3);
const gps p6 = puntoGps(8.3, 25.3);
viaje v_exceso = {
           medicion(1, p4),
           medicion(2, p5),
           medicion(11, p6),
          };
//esperamos que no haya exceso de velocidad, pues los puntos gps estan cercanos y hay
//mucho tiempo entre uno y otro
//para este test esperamos que resulte
//excesoVelocidad(v_noExceso) = F
cout << excesoVelocidad(v_noExceso) << endl;
//esperamos que haya exceso de velocidad, pues los puntos gps estan lejanos y hay
//poco tiempo entre uno y otro
//para este test esperamos que resulte
//excesoVelocidad(v_exceso) = T
cout << excesoVelocidad(v_exceso) << endl;
