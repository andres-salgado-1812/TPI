#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

const gps P = puntoGps(-33, -34);
const double unaHora = 3600;

TEST(excesoDeVelocidadTEST, noSuperaLaVelocidad){
    viaje v = {medicion(0.0, P),
               medicion(unaHora, desviarPunto(P, 1000, 0)),
               medicion(unaHora*2, desviarPunto(P, 2000, 0))}; // 1 KM por hora.

    EXPECT_FALSE(excesoDeVelocidad(v));
}

TEST(excesoDeVelocidadTEST, superaLaVelocidad){
    viaje v = {medicion(0.0, P),
               medicion(unaHora, desviarPunto(P, 100000, 0)),
               medicion(unaHora*2, desviarPunto(P, 200000, 0))}; // 100 KM por hora.

    EXPECT_TRUE(excesoDeVelocidad(v));
}
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

TEST(excesoDeVelocidadTEST, nohayExceso){
//esperamos que no haya exceso de velocidad, pues los puntos gps estan cercanos y hay
//mucho tiempo entre uno y otro
//para este test esperamos que resulte
//excesoVelocidad(v_noExceso) = F
    EXPECT_FALSE(excesoDeVelocidad(v_noExceso));
}
TEST(excesoDeVelocidadTEST, hayExceso){
//esperamos que haya exceso de velocidad, pues los puntos gps estan lejanos y hay
//poco tiempo entre uno y otro
//para este test esperamos que resulte
//excesoVelocidad(v_exceso) = T
    EXPECT_TRUE(excesoDeVelocidad(v_exceso));
}