tuple<tiempo, gps> generarMedicion(tiempo tiempoDelError, gps puntoErrado, gps puntoCorrectoA, gps puntoCorrectoB ){
    float puntoErrado0 = obtenerLatitud(puntoErrado);
    float a0 = obtenerLatitud(puntoCorrectoA);
    float a1 = obtenerLongitud(puntoCorrectoA);
    float b0 = obtenerLatitud(puntoCorrectoB);
    float b1 = obtenerLongitud(puntoCorrectoB);
    float puntoErrado1 = ((a1 - b1)/(a0 - b0))*puntoErrado0 + ((b1*a0 - a1*b0)/(a0 - b0));



    gps coordenadaCorregida = make_tuple(puntoErrado0, puntoErrado1);
    tuple<tiempo,gps> puntoCorregido = make_tuple(tiempoDelError, coordenadaCorregida);
    return puntoCorregido;

}
void corregirPunto(viaje& v, int k){
    tuple<tiempo, gps> puntoCorrecto1 = v[0];
    tuple<tiempo, gps> puntoCorrecto2 = v[0];
    for(int i = 0; i < v.size(); i++){
        if(abs(obtenerTiempo(v[i]) - obtenerTiempo(v[k])) < abs(obtenerTiempo(puntoCorrecto1) - obtenerTiempo(v[k])) &&
        (obtenerTiempo(v[i]) != obtenerTiempo(v[k]))){
            puntoCorrecto1 = v[i];
        }
    }
    for(int i = 0; i < v.size(); i++){
        if(abs(obtenerTiempo(v[i]) - obtenerTiempo(v[k])) < abs(obtenerTiempo(puntoCorrecto2) - obtenerTiempo(v[k])) && (obtenerTiempo(v[i]) != obtenerTiempo(puntoCorrecto1)) &&
                                                                                                                                                  (obtenerTiempo(v[i]) != obtenerTiempo(v[k]))) {
            puntoCorrecto2 = v[i];
        }
    }
    generarMedicion(obtenerTiempo(v[k]), obtenerPosicion(v[k]), obtenerPosicion(puntoCorrecto1), obtenerPosicion(puntoCorrecto2));

    //CORREGIR MEDIANTE ESTOS PUNTOS
}



void corregirViaje(viaje& v, vector<tiempo> errores){
    // codig
     for (int i = 0; i < errores.size(); i++){
        for (int k = 0; k < v.size(); i++){
            if (obtenerTiempo(v[k]) == (errores[i])){
                corregirPunto(v, k);
            }
        }
    }
    return;
}