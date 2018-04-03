//
//  main.c
//  GPS-DFCI
//
//  Created by Patrice Trognon on 07/08/2015.
//  Copyright (c) 2015 Patrice Trognon. All rights reserved.
//

//---
//   Remerciements et Documentation
//
//   Pour la plupart des algorithmes implementes, un grand merci à l'I.G.N.
//   (Institut Geographique National - France), Etablissement Public qui honore cet adjectif depuis de longues annees
//   en rendant accessible au plus grand nombre un savoir et une experience de si grande qualite que seuls quelques-uns
//   ont eu la patience (passion ?), la rigueur et la tenacite de les elaborer ...
//   L'accueil du site de l'I.G.N. : www.ign.fr
//   Les ressources techniques (algorithmes avec jeu d'essai) : http://geodesie.ign.fr/index.php?page=algorithmes
//
//   Un site de base pour ceux qui veulent s'initier à la geodesie, http://sgcaf.free.fr/pages/techniques/ign_coordonnees.htm
//---

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "LatLng2Lambert.h"
#include "Lambert2DFCI.h"
#include "LatLng84DMS.h"
#include "FloatFormater.h"
#include "LatLgn2Locator.h"
#include "LatLng2UTM.h"

#include "DFCI2LatLng.h"

void carroyageDFCI();


int main(int argc, const char * argv[]) {
    char dfci[10];
    char locator[10];
    double lat=44.671123;
    double lng=1.277227;
    sLambertII lambertII;
    sLatLng84DMS latLng84DMS;
    sUTM utm;
    sLatLng latLng;

    strcpy(locator, latLng2Locator(lat, lng));
    latLng84DMS = latLng284DMS(lat, lng);
    
    lambertII = latLng2Lambert(lat, lng);
    strcpy(dfci,lambert2DFCI(lambertII.x, lambertII.y));
    
    utm = latLng2UTM(lat, lng);
    
    printf("lat(%f N) lng(%f E)\n\n",lat,lng);
    printf("DFCI (%s)\n",dfci);

    printf("Loc         (%s)\n",locator);
    printf("WGS84 dms   lat(%s) lng(%s)\n",latLng84DMS.latDMS,latLng84DMS.lngDMS);
    printf("WGS decimal lat(%s) lng(%s)\n",latLng84DMS.latDecimal,latLng84DMS.lngDecimal);
    printf("lambertII   X(%.0f m) Y(%.0f m)\n",lambertII.x, lambertII.y);
    printf("UTM         Z(%s) E(%s) N(%s)\n",utm.utmZ, utm.utmE,utm.utmN);
    
    latLng = DFCI2LatLng(dfci);
    printf("\n\n");
    printf("lat(%f N) lng(%f E)\n\n",latLng.lat,latLng.lng);

    sCarre2Km carre2Km;
    sCarre20Km carre20Km;
    sCarre100Km carre100Km;
    
//    strcpy(dfci, "FE06H2");
    cBool bWithCutting = bTrue ;
    
    DFCI2CarreDeuxKm(dfci, bWithCutting, &carre2Km);
    DFCI2CarreVingtKm(dfci, bWithCutting, &carre20Km);
    DFCI2CarreCentKm(dfci, bWithCutting, &carre100Km);

    
    dumpCarreDeuxKm(&carre2Km, bWithCutting, 0);
    dumpCarreVingtKm(&carre20Km, bWithCutting, 0);
    dumpCarreCentKm(&carre100Km, bWithCutting, 0);
     
//    carroyageDFCI();
    
    return 0;
}

void carroyageDFCI() {
    sFranceDFCI *pFranceDFCI;
    
    time_t tStart = time(&tStart);
    
    pFranceDFCI = calloc(1, sizeof(sFranceDFCI));
    
    performCarroyageDFCI(pFranceDFCI);
    
    time_t tEnd = time(&tEnd);
    
    printf("memory used %lu bytes\n",sizeof(sFranceDFCI));
    printf("Time Elapsed : %ld\n",tEnd-tStart);
    
    free(pFranceDFCI);
}

