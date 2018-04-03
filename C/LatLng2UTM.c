//
//  LatLng2UTM.c
//  GPS-DFCI
//
//  Created by Patrice Trognon on 08/08/2015.
//  Copyright (c) 2015 Patrice Trognon. All rights reserved.
//

#include "LatLng2UTM.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct sXY {
    double  x;
    double  y;
} sXY, *PsXY ;

// constantes pour modèle ellipsoïde WGS84
double sm_a = 6378137.0;
double sm_b = 6356752.314;
double sm_EccSquared = 6.69437999013e-03;
double UTMScaleFactor = 0.9996;

//---
//   internals
void    latlngToUTMXY (double lat, double lng, double zone, PsXY pxy);
double  degToRad(double deg);
char    lat2bande (double lat);
double  arcLengthOfMeridian (double phi);
double  UTMCentralMeridian (double zone);
void    mapLatlngToXY(double phi, double lambda, double lambda0, PsXY pxy);
//   internals
//---

sUTM latLng2UTM(double lat, double lng) {
    sUTM utm ;
    

    // fixe les limites du système UTM
    if (lat<-80 || lat>=84) {
        strcpy(utm.utmE,"hors UTM");
        strcpy(utm.utmN,"hors UTM");
        strcpy(utm.utmZ,"hors UTM");
        
    } else {

        // détermine fuseau
        double zone = floor ((lng + 180.0) / 6) + 1;
        
        // fuseaau spécial Ouest de la Norvège
        if (lat >= 56.0 && lat < 64.0 && lng >= 3.0 && lng < 12.0 ) {
            zone = 32;
        }
        
        // fuseaux spéciaux des îles Svalbard
        if( lat >= 72.0 && lat < 84.0 ) {
            if (lng >= 0.0  && lng <  9.0 ) {
                zone = 31;
                
            } else if ( lng >= 9.0  && lng < 21.0 ) {
                zone = 33;
                
            } else if ( lng >= 21.0 && lng < 33.0 ) {
                zone = 35;
                
            } else if ( lng >= 33.0 && lng < 42.0 ) {
                zone = 37;
                
            }
        }
        
        // détermine les distances en m depuis la référence

        sXY sXY;
        latlngToUTMXY (degToRad (lat), degToRad (lng), zone, & sXY);

        // détermine bande C à X
        char bande = lat2bande (lat);

        sprintf(utm.utmE, "%d m E",(int)sXY.x);
        sprintf(utm.utmN, "%d m N",(int)sXY.y);
        sprintf(utm.utmZ, "%d %c",(int)zone,bande);
    }
    return utm;
}

void    latlngToUTMXY (double lat, double lng, double zone, PsXY pxy) {
    mapLatlngToXY (lat, lng, UTMCentralMeridian (zone), pxy);
    
    /* Adjust easting and northing for UTM system. */
    pxy->x = pxy->x * UTMScaleFactor + 500000.0;
    pxy->y = pxy->y * UTMScaleFactor;
    if (pxy->y < 0.0) {
        pxy->y = pxy->y + 10000000.0;
    }
}

double degToRad (double deg) {
    return (deg / 180.0 * M_PI);
}


char lat2bande (double lat) {
    // détermine la bande
    // entrée lat en décimales DD.DDDDD
    // sortie bande de C à X
    
    // lettres utilisées en UTM
    char lettres[]="CDEFGHJKLMNPQRSTUVWXYZ";
    // coordonnées UTM vont de -80 (S) à + 84 (N)
    lat=lat+80;
    // détermine lettre de la bande latitude de C à X
    int position = (int)floor(lat/8);
    
    char bande = lettres[position];
    
    if ( bande > 'X' ) {
        bande='X';
    }
    
    return bande;
}

double arcLengthOfMeridian (double phi) {
    double alpha, beta, gamma, delta, epsilon, n;
    double result = 0.0;
    
    /* Precalculate n */
    n = (sm_a - sm_b) / (sm_a + sm_b);
    
    /* Precalculate alpha */
    alpha = ((sm_a + sm_b) / 2.0) * (1.0 + (pow (n, 2.0) / 4.0) + (pow (n, 4.0) / 64.0));
    
    /* Precalculate beta */
    beta = (-3.0 * n / 2.0) + (9.0 * pow (n, 3.0) / 16.0) + (-3.0 * pow (n, 5.0) / 32.0);
    
    /* Precalculate gamma */
    gamma = (15.0 * pow (n, 2.0) / 16.0) + (-15.0 * pow (n, 4.0) / 32.0);
    
    /* Precalculate delta */
    delta = (-35.0 * pow (n, 3.0) / 48.0) + (105.0 * pow (n, 5.0) / 256.0);
    
    /* Precalculate epsilon */
    epsilon = (315.0 * pow (n, 4.0) / 512.0);
    
    /* Now calculate the sum of the series and return */
    result = alpha
                * (phi + (beta * sin (2.0 * phi))
                + (gamma * sin (4.0 * phi))
                + (delta * sin (6.0 * phi))
                + (epsilon * sin (8.0 * phi)));
    
    return result;
}

double UTMCentralMeridian (double zone) {
    double cmeridian;
    cmeridian = degToRad (-183.0 + (zone * 6.0));
    return cmeridian;
}

void    mapLatlngToXY(double phi, double lambda, double lambda0, PsXY pxy) {
    double N, nu2, ep2, t, t2, l;
    double l3coef, l4coef, l5coef, l6coef, l7coef, l8coef;
    double tmp;
    
    /* Precalculate ep2 */
    ep2 = (pow (sm_a, 2.0) - pow (sm_b, 2.0)) / pow (sm_b, 2.0);
    
    /* Precalculate nu2 */
    nu2 = ep2 * pow (cos (phi), 2.0);
    
    /* Precalculate N */
    N = pow (sm_a, 2.0) / (sm_b * sqrt (1 + nu2));
    
    /* Precalculate t */
    t = tan (phi);
    t2 = t * t;
    tmp = (t2 * t2 * t2) - pow (t, 6.0);
    
    /* Precalculate l */
    l = lambda - lambda0;
    
    /* Precalculate coefficients for l**n in the equations below
     so a normal human being can read the expressions for easting
     and northing
     -- l**1 and l**2 have coefficients of 1.0 */
    l3coef = 1.0 - t2 + nu2;
    
    l4coef = 5.0 - t2 + 9 * nu2 + 4.0 * (nu2 * nu2);
    
    l5coef = 5.0 - 18.0 * t2 + (t2 * t2) + 14.0 * nu2 - 58.0 * t2 * nu2;
    
    l6coef = 61.0 - 58.0 * t2 + (t2 * t2) + 270.0 * nu2 - 330.0 * t2 * nu2;
    
    l7coef = 61.0 - 479.0 * t2 + 179.0 * (t2 * t2) - (t2 * t2 * t2);
    
    l8coef = 1385.0 - 3111.0 * t2 + 543.0 * (t2 * t2) - (t2 * t2 * t2);
    
    /* Calculate easting (x) */
    pxy->x = N * cos (phi) * l
            + (N / 6.0 * pow (cos (phi), 3.0) * l3coef * pow (l, 3.0))
            + (N / 120.0 * pow (cos (phi), 5.0) * l5coef * pow (l, 5.0))
            + (N / 5040.0 * pow (cos (phi), 7.0) * l7coef * pow (l, 7.0));
    
    /* Calculate northing (y) */
    pxy->y = arcLengthOfMeridian (phi)
            + (t / 2.0 * N * pow (cos (phi), 2.0) * pow (l, 2.0))
            + (t / 24.0 * N * pow (cos (phi), 4.0) * l4coef * pow (l, 4.0))
            + (t / 720.0 * N * pow (cos (phi), 6.0) * l6coef * pow (l, 6.0))
            + (t / 40320.0 * N * pow (cos (phi), 8.0) * l8coef * pow (l, 8.0));
    
    return;
}
