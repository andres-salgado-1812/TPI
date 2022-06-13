#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

vector<viaje> f = {{
                   medicion(1.5,puntoGps(2.5, 2.89996)),
                   medicion(1.7,puntoGps(2.5, 2.89997)),
                   medicion(1.9,puntoGps(2.5, 2.89998))},
                   {
                    medicion(2.5,puntoGps(2.5, 2.89996)),
                    medicion(2.6,puntoGps(2.5, 2.89997)),
                    medicion(2.7,puntoGps(2.5, 2.89998))},
                   {
                    medicion(0.5,puntoGps(2.5, 2.89996)),
                    medicion(0.6,puntoGps(2.5, 2.89997)),
                    medicion(0.7,puntoGps(2.5, 2.89998))},
                   };
vector<viaje> f2 = {};

vector<viaje> f3 = {{
                           medicion(40.2,puntoGps(2.5, 2.89996)),
                           medicion(43.1,puntoGps(2.5, 2.89997)),
                           medicion(47,puntoGps(2.5, 2.89998))},
                   {
                           medicion(58,puntoGps(2.5, 2.89996)),
                           medicion(60,puntoGps(2.5, 2.89997)),
                           medicion(60.3,puntoGps(2.5, 2.89998))},
};

TEST(flotaTotalTEST, todosAntesDeFranja){
    EXPECT_EQ(flota(f,3.0,5.0),0);
}

TEST(flotaTotalTEST, AlgunosAdentro){
    EXPECT_EQ(flota(f, 1.8,2.55),2);
}

TEST(flotaTotalTEST, FlotaVacia){
    EXPECT_EQ(flota(f2, 2,3), 0);
}
TEST(flotaTotalTEST, TodosDentro){
    EXPECT_EQ(flota(f3, 30,60.4),2);
}
