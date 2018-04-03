//
//  Lambert2DFCI.h
//  GPS-DFCI
//
//  Created by Patrice Trognon on 07/08/2015.
//

#ifndef __GPS_DFCI__Lambert2DFCI__
#define __GPS_DFCI__Lambert2DFCI__

#include <stdio.h>

//---
// fonction de conversion des coordonnées Lambert II étendu vers la grille DFCI
// entrée : coordonnées X et Y en système Lambert II étendu en m
// sortie : coordonnées DFCI formatée -> NB80A0.5
// return : DFCI chaîne
// Conversion du code javascript écrit par Patrick EGLOFF (04/2009) http://www.egloff.eu
//
//---
char*    lambert2DFCI(double x, double y) ;

#endif /* defined(__GPS_DFCI__Lambert2DFCI__) */
