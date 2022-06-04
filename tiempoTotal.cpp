using namespace std;
#include <iostream>
#include <tuple>

int long_tupla(tuple tupla) {
  return tuple_size<decltype(tupla)>::value;
}

int main(){
  //ESPECIFICACION
  //proc tiempoTotal(in v : Viaje, out t : Tiempo)
  //dado un viaje valido, determina el tiempo total que tardo el colectivo.
  //Este valor debe ser calculado como el tiempo transcurrido desde el primer
  //punto registrado y hasta el ultimo
  //NOTA: Los viajes NO estan ordenados, solo los recorridos
  tuple <float, string, int> cosa = make_tuple(3.8, "asd", 2);
  cout << "aasd" << endl;
  for (int i = 0; i < tuple_size<decltype(cosa)>::value; i++) {
    cout << i << endl;
  }
  for (int i = 0; i < long_tupla(cosa); i++) {
    cout << i << endl;
  }
}
