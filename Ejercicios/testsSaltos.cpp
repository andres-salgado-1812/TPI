//esto deberia dar un salto
const gps p1 = puntoGps(.5, .5);
const gps p2 = puntoGps(1.5, 1.5);
const gps p3 = puntoGps(.5, 1.5);
const gps p4 = puntoGps(.5, .5);
viaje v = {
           medicion(1, p1),
           medicion(2, p2),
           medicion(3, p3),
           medicion(4, p4),
          };
//esto deberia dar 3 saltos
const gps p5 = puntoGps(.5, .5);
const gps p6 = puntoGps(2.5, 1.5);
const gps p7 = puntoGps(.5, 2.5);
const gps p8 = puntoGps(2.5, .5);
viaje v1 = {
           medicion(1, p5),
           medicion(2, p6),
           medicion(3, p7),
           medicion(4, p8),
          };
gps esq1 = puntoGps(3, 0);
gps esq2 = puntoGps(0, 3);
int n1 = 3;
int m1 = 3;
grilla g = construirGrilla(n1, m1, esq1, esq2);
//imprimirGrilla(g);
//esperamos un salto
int salto = cantidadDeSaltos(v, g);
cout << salto << endl; //da un solo salto, es correcto
//esperamos tres saltos
int saltos = cantidadDeSaltos(v1, g);
cout << saltos << endl; //da un solo salto, es incorrecto
