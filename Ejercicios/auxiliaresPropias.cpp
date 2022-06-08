void swap(tuple<tiempo, gps> &a, tuple<tiempo, gps> &b){
  tuple<tiempo, gps> c = a;
  a = b;
  b = c;
}

viaje ordenarViaje(viaje v){
  for (int i = 0; i < v.size() - 1; i++) {
    for (int j = i + 1; j < v.size(); j++) {
      if (obtenerTiempo(v[j]) < obtenerTiempo(v[i])) {
        swap(v[i], v[j]);
      }
    }
  }
  return v;
}

grilla construirGrilla(int n, int m, gps esq1, gps esq2) {
  float base = (obtenerLongitud(esq2) - obtenerLongitud(esq1)) / m;
  float altura = (obtenerLatitud(esq1) - obtenerLatitud(esq2)) / n;
  grilla g;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      float latSup = obtenerLatitud(esq1) - altura * (i - 1);
      float longSup = obtenerLongitud(esq1) + base * (j - 1);
      float latInf = obtenerLatitud(esq1) - altura * (i);
      float longInf = obtenerLongitud(esq1) + base * (j);
      gps esqSup = puntoGps(latSup, longSup);
      gps esqInf = puntoGps(latInf, longInf);
      nombre nom = make_tuple(i, j);
      celda c = make_tuple(esqSup, esqInf, nom);
      g.push_back(c);
    }
  }
  return g;
}

gps obtenerEsquinaSup(celda c){
  return get<0>(c);
}
gps obtenerEsquinaInf(celda c){
  return get<1>(c);
}
nombre obtenerNombre(celda c){
  return get<2>(c);
}

void imprimirViaje(viaje v){
  cout << "viaje: seq<";
  for (int i = 0; i < v.size(); i++){
    tiempo t = obtenerTiempo(v[i]);
    float lati = obtenerLatitud(obtenerPosicion(v[i]));
    float longi = obtenerLongitud(obtenerPosicion(v[i]));
    cout << "(" << t << ", " << lati << ", " << longi << "), ";
  }
  cout << ">";
}

void imprimirGrilla(grilla g) {
  cout << "grilla: ";
  for (int i = 0; i < g.size(); i++) {
    float latSup = obtenerLatitud(obtenerEsquinaSup(g[i]));
    float longSup = obtenerLongitud(obtenerEsquinaSup(g[i]));
    float latInf = obtenerLatitud(obtenerEsquinaInf(g[i]));
    float longInf = obtenerLongitud(obtenerEsquinaInf(g[i]));
    int n = get<0>(obtenerNombre(g[i]));
    int m = get<1>(obtenerNombre(g[i]));
    cout << "seq<(" << latSup << ", " << longSup << "), " <<
    "(" << latInf << ", " << longInf << ")> ,";
  }
  cout << ">" << endl;
}
