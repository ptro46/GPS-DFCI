//
//  LatLng2UTM.h
//  GPS-DFCI
//
//  Created by Patrice Trognon on 08/08/2015.
//  Copyright (c) 2015 Patrice Trognon. All rights reserved.
//

#ifndef __GPS_DFCI__LatLng2UTM__
#define __GPS_DFCI__LatLng2UTM__

#include <stdio.h>

typedef struct sUTM {
    char    utmZ[20];
    char    utmE[20];
    char    utmN[20];
} sUTM, *PsUTM;

//---
// script de conversion lat long en UTM
// en partie inspiré de Charles L. Taylor
//
// calcul des coordonnées UTM
// entrée lat et lng en décimales, S et W en négatif
// sortie zone 32T 500000mE 4649776mN
//
// constantes pour modèle ellipsoïde WGS84
// Conversion du code javascript écrit par Patrick EGLOFF (04/2009) http://www.egloff.eu
//---

sUTM latLng2UTM(double lat, double lng) ;

#endif /* defined(__GPS_DFCI__LatLng2UTM__) */
