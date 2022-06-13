ttuple<tiempo, gps> generarMedicion(tiempo tiempoDelError , gps p, gps q, float v_med, gps desde){
    gps pq = restarGPS(q, p);
    gps pq_versor = multiplicarPorEscalar(pq, (1 / norma(pq)));
    gps pq_versor_escalado = multiplicarPorEscalar(pq_versor, v_med);
    gps r = sumarGPS(desde, pq_versor_escalado);
    tuple<tiempo,gps> medicionCorregida = make_tuple(tiempoDelError, r);
    return medicionCorregida;
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
    double v_media = ((distEnKM(obtenerPosicion(puntoCorrecto1), obtenerPosicion(puntoCorrecto2)))/1000)/(abs(obtenerTiempo(puntoCorrecto2)- obtenerTiempo(puntoCorrecto1)));
    //generarMedicion(obtenerTiempo(v[k]), obtenerPosicion(v[k]), obtenerPosicion(puntoCorrecto1), obtenerPosicion(puntoCorrecto2));
    if (obtenerTiempo(v[k]) < obtenerTiempo(puntoCorrecto1) && obtenerTiempo(v[k]) < obtenerTiempo(puntoCorrecto2)){
        v[k] =  generarMedicion(obtenerTiempo(v[k]), obtenerPosicion(puntoCorrecto2) , obtenerPosicion(puntoCorrecto1), v_media, obtenerPosicion(puntoCorrecto2));
    }
    else if (obtenerTiempo(v[k]) > obtenerTiempo(puntoCorrecto1) && obtenerTiempo(v[k]) < obtenerTiempo(puntoCorrecto2)){
        v[k] = generarMedicion(obtenerTiempo(v[k]),obtenerPosicion(puntoCorrecto1) , obtenerPosicion(puntoCorrecto2), v_media, obtenerPosicion(puntoCorrecto1));
    }
    else if (obtenerTiempo(v[k]) > obtenerTiempo(puntoCorrecto1) && obtenerTiempo(v[k]) > obtenerTiempo(puntoCorrecto2)){
        v[k] = generarMedicion(obtenerTiempo(v[k]),obtenerPosicion(puntoCorrecto2) , obtenerPosicion(puntoCorrecto1), v_media, obtenerPosicion(puntoCorrecto1));
    }
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
