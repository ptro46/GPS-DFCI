# GPS-DFCI

## Conversions

Routines de conversion entre les systèmes de coordonnées
   -   DFCI
   -   WGS84 dms
   -   WGS decimal
   -   lambertII
   -   UTM

### Exemple
```
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
```

### Résultats

```
lat(44.671123 N) lng(1.277227 E)

DFCI (FE06H1.2)
Loc         (JN04PQ31)
WGS84 dms   lat(44:40'16.04''N) lng(001:16'38.02''E)
WGS decimal lat(44.671123 N) lng(01.277227 E)
lambertII   X(515954 m) Y(1963930 m)
UTM         Z(31 T) E(363444 m E) N(4947860 m N)


lat(44.667205 N) lng(1.271582 E)
```

## Calcul des carrés DFCI depuis une coordonnée GPS

Routine de calcul du carré DFCI de 100km, 20km et 2km depuis une coordonnée GPS, les points calculés permettent de tracer les carrés DFCI sur une map travaillant en LambertII ou en coordonnées GPS.

```
    strcpy(dfci, "FE06H2");
    cBool bWithCutting = bTrue ;
    
    DFCI2CarreDeuxKm(dfci, bWithCutting, &carre2Km);
    DFCI2CarreVingtKm(dfci, bWithCutting, &carre20Km);
    DFCI2CarreCentKm(dfci, bWithCutting, &carre100Km);

    
    dumpCarreDeuxKm(&carre2Km, bWithCutting, 0);
    dumpCarreVingtKm(&carre20Km, bWithCutting, 0);
    dumpCarreCentKm(&carre100Km, bWithCutting, 0);
```

## Calcul d'un carroyage DFCI

Routine de calcul du carroyage DFCI (100km, 20km et 2km) sur toute la France métropolitaine.

```
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
```

## Langages

L'ensemble des routines est disponible dans 4 langages de programmation avec un portage natif (le c++ n'utilise pas les mapping C)
   -   C
   -   C++
   -   Java
   -   Objective C
  


