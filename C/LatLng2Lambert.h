//
//  LatLng2Lambert.h
//  GPS-DFCI
//
//  Created by Patrice Trognon on 07/08/2015.
//

#ifndef __GPS_DFCI__LatLng2Lambert__
#define __GPS_DFCI__LatLng2Lambert__

#include <stdio.h>

typedef struct sLambertII {
    double       x;
    double       y;
} sLambertII, *PsLambertII;

//---
// fonction pour convertir latitude et longitude décimales dans le système WGS84 en coordonnées Lambert II étendues
// ne tient pas compte de h, hauteur au-dessus de l'éllipsoïde
// entrée : lat et lng au format WGS84 décimal
// sortie : données Lambert II étendu arrondi à 3 chiffres après la virgule
// return : sLambertII
// algorithmes de l'IGN contenus dans la note technique NT/G 80
// Conversion du code javascript écrit par Patrick EGLOFF (04/2009) http://www.egloff.eu
//---

sLambertII  latLng2Lambert(double lat, double lng) ;

#endif /* defined(__GPS_DFCI__LatLng2Lambert__) */
