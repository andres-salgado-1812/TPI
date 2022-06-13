#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;


TEST(cantidadDeSaltosTEST, todosSaltosOrdenados){
    grilla g = construirGrilla(puntoGps(0.0,0.0),desviarPunto(puntoGps(0,0), 3000, 3000), 6, 6);

    gps p1 = puntoGps(0, 0);
    gps p2 = desviarPunto(p1, 2000, 2000);
    gps p3 = desviarPunto(p1, 100, 100);

    viaje v = {medicion(1.5, p1),
               medicion(1.6, p2),
               medicion(1.7, p3)};

    EXPECT_EQ(cantidadDeSaltos(g,v),2);
}

TEST(cantidadDeSaltosTEST, casoDeterminado){
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
    grilla g2 = construirGrilla(esq1, esq2, n1, m1);

    EXPECT_EQ(cantidadDeSaltos(g2,v),2);
}