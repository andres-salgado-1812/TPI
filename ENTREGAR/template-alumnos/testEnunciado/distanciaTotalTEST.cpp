#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(distanciaTotalTEST, viajeDesordenado){
    gps p1 = puntoGps(-33, -34);
    gps p2 = desviarPunto(p1, 2000, 0);
    gps p3 = desviarPunto(p2, 2000, 0);

    viaje v = {medicion(1.6, p2),
               medicion(1.5, p1),
               medicion(1.7, p3)};

    EXPECT_NEAR(distanciaTotal(v), 4.0, 0.01);
}

TEST(distanciaTotalTEST, viajeCorto){
gps p1 = puntoGps(-43, 23);
gps p2 = desviarPunto(p1, 5000, 0);
gps p3 = desviarPunto(p2, 5000, 0);

viaje v = {medicion(5, p2),
           medicion(8, p1),
           medicion(14, p3)};

EXPECT_NEAR(distanciaTotal(v), 14.999999999776, 0.01);
}



TEST(distanciaTotalTEST, viajeDesordenado2){
gps p1 = puntoGps(0, 0);
gps p2 = desviarPunto(p1, 4000, 1000);


viaje v = {medicion(1.3, p2),
           medicion(1.1, p1)};

EXPECT_NEAR(distanciaTotal(v), 4.123, 0.01);
}