//
//  DFCI2LatLng.h
//  GPS-DFCI
//
//  Created by Patrice Trognon on 08/08/2015.
//  Copyright (c) 2015 Patrice Trognon. All rights reserved.
//

#ifndef __GPS_DFCI__DFCI2LatLng__
#define __GPS_DFCI__DFCI2LatLng__

#include <stdio.h>

#include "LatLng2Lambert.h"

typedef enum cBool {
    bFalse      =       0,
    bTrue       =       1
} cBool ;

typedef struct  sLatLng {
    double      lat;
    double      lng;
} sLatLng, *PsLatLng ;

typedef struct sCoord {
    sLambertII      lambert;
    sLatLng         latLng;
} sCoord , *PsCoord ;

typedef struct sZoneChasseSecteur1 {
    int             numeroZone;
    sCoord          coordSO;
    sCoord          coordNO;
    sCoord          coordNE;
    sCoord          coordSEIntermediaire1;
    sCoord          coordSEIntermediaire2;
    sCoord          coordSEIntermediaire3;
    sCoord          coordSE;
    sCoord          coordCentre;
} sZoneChasseSecteur1, *PsZoneChasseSecteur1 ;

typedef struct sZoneChasseSecteur2 {
    int             numeroZone;
    sCoord          coordSO;
    sCoord          coordSOIntermediaire1;
    sCoord          coordSOIntermediaire2;
    sCoord          coordSOIntermediaire3;
    sCoord          coordNO;
    sCoord          coordNE;
    sCoord          coordSE;
    sCoord          coordCentre;
} sZoneChasseSecteur2, *PsZoneChasseSecteur2 ;

typedef struct sZoneChasseSecteur3 {
    int             numeroZone;
    sCoord          coordSO;
    sCoord          coordNOIntermediaire1;
    sCoord          coordNOIntermediaire2;
    sCoord          coordNOIntermediaire3;
    sCoord          coordNO;
    sCoord          coordNE;
    sCoord          coordSE;
    sCoord          coordCentre;
} sZoneChasseSecteur3, *PsZoneChasseSecteur3 ;

typedef struct sZoneChasseSecteur4 {
    int             numeroZone;
    sCoord          coordSO;
    sCoord          coordNO;
    sCoord          coordNEIntermediaire1;
    sCoord          coordNEIntermediaire2;
    sCoord          coordNEIntermediaire3;
    sCoord          coordNE;
    sCoord          coordSE;
    sCoord          coordCentre;
} sZoneChasseSecteur4, *PsZoneChasseSecteur4 ;

typedef struct sZoneChasseSecteur5 {
    int             numeroZone;
    sCoord          coordSO;
    sCoord          coordNO;
    sCoord          coordNE;
    sCoord          coordSE;
    sCoord          coordCentre;
} sZoneChasseSecteur5, *PsZoneChasseSecteur5 ;

typedef struct sCarre2Km {
    char                    nomDFCI[3];
    sCoord                  coordCentre;
    sCoord                  coordSO;
    sCoord                  coordNO;
    sCoord                  coordNE;
    sCoord                  coordSE;
    sZoneChasseSecteur1     secteur1;
    sZoneChasseSecteur2     secteur2;
    sZoneChasseSecteur3     secteur3;
    sZoneChasseSecteur4     secteur4;
    sZoneChasseSecteur5     secteur5;
} sCarre2Km, *PsCarre2Km;

typedef struct sCarre20Km {
    char                    nomDFCI[3];
    sCoord                  coordCentre;
    sCoord                  coordSO;
    sCoord                  coordNO;
    sCoord                  coordNE;
    sCoord                  coordSE;
    sCarre2Km               matriceCarres2Km[10][10];
} sCarre20Km, *PsCarre20Km;

typedef struct sCarre100Km {
    char                    nomDFCI[3];
    sCoord                  coordCentre;
    sCoord                  coordSO;
    sCoord                  coordNO;
    sCoord                  coordNE;
    sCoord                  coordSE;
    sCarre20Km              matriceCarres20Km[5][5];
} sCarre100Km, *PsCarre100Km ;

typedef struct sFranceDFCI {
    sCarre100Km     matriceFrance[12][12];
}sFranceDFCI, *PsFranceDFCI;

sLambertII  DFCI2Lambert(char *dfci);
sLatLng     DFCI2LatLng(char *dfci);

sLatLng     lambertII2LatLng(sLambertII sLambert);
void        performCarroyageDFCI(sFranceDFCI* pFranceDFCI);
void        DFCI2CarreCentKm(char *dfci,cBool bWithCutting,  sCarre100Km *pCarre100Km);
void        DFCI2CarreVingtKm(char *dfci,cBool bWithCutting, sCarre20Km  *pCarre20Km);
void        DFCI2CarreDeuxKm(char *dfci,cBool bWithCutting,  sCarre2Km   *pCarre2Km);

void        dumpCarreCentKm(sCarre100Km *pCarre100Km,cBool bWithCutting,int indentLevel);
void        dumpCarreVingtKm(sCarre20Km *pCarre20Km,cBool bWithCutting,int indentLevel);
void        dumpCarreDeuxKm(sCarre2Km *pCarre2Km,cBool bWithCutting,int indentLevel);

#endif /* defined(__GPS_DFCI__DFCI2LatLng__) */
