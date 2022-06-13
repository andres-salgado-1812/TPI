#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(corregirViajeTEST, faltaElUltimo){
    viaje v = {medicion(T0+0, puntoGps(-34.588910, -58.405075)),
               medicion(T0+30, puntoGps(-34.591586, -58.401064)),
               medicion(T0+494, puntoGps(-34.563746, -58.436637)),
               medicion(T0+999, puntoGps(-34.549657, -58.437327)),
               medicion(T0+92, puntoGps(-34.594553, -58.402426)),
               medicion(T0+65, puntoGps(-34.590787, -58.402222)),
               medicion(T0+230, puntoGps(-34.584572, -58.416942)),
               medicion(T0+873, puntoGps(-34.559236, -58.427499)),
               medicion(T0+675, puntoGps(-34.578941, -58.424878)),
               medicion(T0+1051, puntoGps(0, 0))};

    viaje res = {medicion(T0+0, puntoGps(-34.588910, -58.405075)),
                 medicion(T0+30, puntoGps(-34.591586, -58.401064)),
                 medicion(T0+494, puntoGps(-34.563746, -58.436637)),
                 medicion(T0+999, puntoGps(-34.549657, -58.437327)),
                 medicion(T0+92, puntoGps(-34.594553, -58.402426)),
                 medicion(T0+65, puntoGps(-34.590787, -58.402222)),
                 medicion(T0+230, puntoGps(-34.584572, -58.416942)),
                 medicion(T0+873, puntoGps(-34.559236, -58.427499)),
                 medicion(T0+675, puntoGps(-34.578941, -58.424878)),
                 medicion(T0+1051, puntoGps(-34.545704, -58.441383))};
    vector<tiempo> errores = {T0+1051};

    corregirViaje(v, errores);
    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}

TEST(corregirViajeTEST, viajeDeterminado){
    viaje v2 = {medicion(1, puntoGps(1, 1)), medicion(2, puntoGps(2, 2)) , medicion(3, puntoGps(100,200)), medicion(50, puntoGps(4,4)),
                                                     medicion(55, puntoGps(5,5))};
    viaje v2Res = {medicion(1, puntoGps(1, 1)), medicion(2, puntoGps(2, 2)) , medicion(3, puntoGps(2.1112408638,2.1112408638)), medicion(50, puntoGps(4,4)),
                                                     medicion(55, puntoGps(5,5))};
    vector<tiempo> errores = {3};


    corregirViaje(v2, errores);
    EXPECT_EQ(v2.size(),v2Res.size());
    for (int i = 0; i < v2Res.size(); ++i) {
    EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v2[i])),
            obtenerLatitud(obtenerPosicion(v2Res[i])), 0.00001);
    EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v2[i])),
            obtenerLongitud(obtenerPosicion(v2Res[i])), 0.00001);
    EXPECT_EQ(obtenerTiempo(v2[i]),obtenerTiempo(v2Res[i]));
}
}


TEST(corregirViajeTEST, viajeDeterminado2){
viaje v3 = {medicion(1, puntoGps(1, 1)), medicion(2, puntoGps(2, 2)) , medicion(3, puntoGps(3,3)), medicion(4, puntoGps(100,50)),
            medicion(5, puntoGps(5,5))};
viaje v3Res = {medicion(1, puntoGps(1, 1)), medicion(2, puntoGps(2, 2)) , medicion(3, puntoGps(3,3)), medicion(4, puntoGps(3.1111226081848145,3.1111226081848145)),
               medicion(5, puntoGps(5,5))};
vector<tiempo> errores = {4};


corregirViaje(v3, errores);
EXPECT_EQ(v3.size(),v3Res.size());
for (int i = 0; i < v3Res.size(); ++i) {
EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v3[i])),
        obtenerLatitud(obtenerPosicion(v3Res[i])), 0.00001);
EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v3[i])),
        obtenerLongitud(obtenerPosicion(v3Res[i])), 0.00001);
EXPECT_EQ(obtenerTiempo(v3[i]),obtenerTiempo(v3Res[i]));
}
}