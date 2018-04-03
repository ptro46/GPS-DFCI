//
//  DFCI2LatLng.c
//  GPS-DFCI
//
//  Created by Patrice Trognon on 08/08/2015.
//  Copyright (c) 2015 Patrice Trognon. All rights reserved.
//

#include "DFCI2LatLng.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//---
//   internals


int    InStr(char *myString, char searchChar,size_t maxLen);
double IsomLat(double latitIsom,double premExcEllips, double tolConverg);
double NTFLatWGS(double gLat, double gLon);
double NTFLonWGS(double gLat, double gLon);
double LambLatNTF(double xLambert, double yLambert,int TypLamb);
double LambLonNTF(double xLambert, double yLambert,int TypLamb);
//   internals
//---

sLambertII  DFCI2Lambert(char *dfci) {
    sLambertII lambertII ;
 
    double XLamb, YLamb ;
    
    // FE06H1.2
    char carre100[3] ;
    carre100[0] = dfci[0];
    carre100[1] = dfci[1];
    carre100[2] = 0 ;
    
    char carre20[3];
    carre20[0] = dfci[2];
    carre20[1] = dfci[3];
    carre20[2] = 0 ;
    
    char carre2[3];
    carre2[0] = dfci[4];
    carre2[1] = dfci[5];
    carre2[2] = 0 ;
    
    char zon5[3];
    zon5[0] = dfci[6];
    zon5[1] = dfci[7];
    zon5[2] = 0 ;
    
    YLamb=1500000 ;
    XLamb=0;
    
    char *dfciLetters = "ABCDEFGHKLMN";
    
    int a;
    
    a = InStr(dfciLetters, carre100[0],strlen(dfciLetters));
    XLamb = XLamb + a*100000;
    a = InStr(dfciLetters, carre100[1],strlen(dfciLetters));
    YLamb = YLamb + a*100000;
    
    char a20[2];
    
    a20[0] = carre20[0];
    a20[1] = 0 ;
    a = atoi(a20)/2;
    XLamb = XLamb + a*20000;
    
    a20[0] = carre20[1];
    a20[1] = 0 ;
    a = atoi(a20)/2;
    YLamb = YLamb + a*20000;
    
    a = InStr(dfciLetters, carre2[0],strlen(dfciLetters));
    XLamb = XLamb + a*2000;
    
    a20[0] = carre2[1];
    a20[1] = 0 ;
    a = atoi(a20);
    YLamb = YLamb + a*2000;
    
    switch ( zon5[1] ) {
        case '1' : {
            //XLamb = XLamb+500;
            YLamb = YLamb+1000;
        } break ;
            
        case '2' : {
            XLamb = XLamb+1500;
            YLamb = YLamb+1500;
        } break ;
            
        case '3' : {
            XLamb = XLamb+1000;
            //YLamb = YLamb+500;
        } break ;
            
        case '4' : {
            //XLamb = XLamb+500;
            //YLamb = YLamb+500;
        } break ;
            
        default : {
            XLamb = XLamb+500;
            YLamb = YLamb+500;
        } break ;
    }
    
    lambertII.x = XLamb ;
    lambertII.y = YLamb ;
    
    return lambertII;
}

sLatLng DFCI2LatLng(char *dfci) {
    sLambertII lambertII = DFCI2Lambert(dfci);
    return lambertII2LatLng(lambertII);
}

void performCarroyageDFCI(sFranceDFCI* pFranceDFCI) {
    char dfci[10];
    char LambertX[] = "ABCDEFGHKLMN";
    char LambertY[] = "ABCDEFGHKLMN";
    
    dfci[2] = '0';
    dfci[3] = '0';
    dfci[4] = 'A';
    dfci[5] = '0';
    dfci[6] = '.';
    dfci[7] = '4';
    
    for(int x=0; x<12; x++) {
        for(int y=0; y<12; y++) {
            dfci[0] = LambertX[x];
            dfci[1] = LambertY[y];
            
            DFCI2CarreCentKm(dfci, bTrue, & pFranceDFCI->matriceFrance[x][y]);
        }
    }
}

void DFCI2CarreCentKm(char *dfci,cBool bWithCutting,  sCarre100Km *pCarre100Km) {
    char dfci100Km[10];
    
    strcpy(dfci100Km,dfci);
    dfci100Km[2] = '0';
    dfci100Km[3] = '0';
    dfci100Km[4] = 'A';
    dfci100Km[5] = '0';
    dfci100Km[7] = '4';
    
//    printf("100Km %s\n",dfci100Km);
    
    //---
    //  Nom du carré 100Km
    pCarre100Km->nomDFCI[0] = dfci[0];
    pCarre100Km->nomDFCI[1] = dfci[1];
    pCarre100Km->nomDFCI[2] = 0;

    //---
    //   calculer le point SO en lambert
    sLambertII lambert = DFCI2Lambert(dfci100Km);
    pCarre100Km->coordSO.lambert = lambert ;
    pCarre100Km->coordSO.latLng = lambertII2LatLng(pCarre100Km->coordSO.lambert);
    
    //---
    //   depuis le point SO calcul des autres points dans un carré de 2000 m
    pCarre100Km->coordSE.lambert.x = lambert.x + 100000 ;
    pCarre100Km->coordSE.lambert.y = lambert.y ;
    pCarre100Km->coordSE.latLng = lambertII2LatLng(pCarre100Km->coordSE.lambert);
    
    pCarre100Km->coordNE.lambert.x = lambert.x + 100000 ;
    pCarre100Km->coordNE.lambert.y = lambert.y + 100000 ;
    pCarre100Km->coordNE.latLng = lambertII2LatLng(pCarre100Km->coordNE.lambert);
    
    pCarre100Km->coordNO.lambert.x = lambert.x ;
    pCarre100Km->coordNO.lambert.y = lambert.y + 100000 ;
    pCarre100Km->coordNO.latLng = lambertII2LatLng(pCarre100Km->coordNO.lambert);

    pCarre100Km->coordCentre.lambert.x = lambert.x + 50000;
    pCarre100Km->coordCentre.lambert.y = lambert.y + 50000;
    pCarre100Km->coordCentre.latLng = lambertII2LatLng(pCarre100Km->coordCentre.lambert);
    

    if ( bWithCutting == bTrue ) {
        char LambertX[] = "02468";
        char LambertY[] = "02468";
        for(int x=0; x<5; x++) {
            for(int y=0; y<5;y++) {
                dfci100Km[2] = LambertX[x];
                dfci100Km[3] = LambertY[y];
                DFCI2CarreVingtKm(dfci100Km, bWithCutting, & pCarre100Km->matriceCarres20Km[x][y]);
            }
        }
    }
}

char *      indent(int indentLevel) {
    static char buffer[256];
    
    memset(buffer, 0, 256*sizeof(char));
    
    for(int i=0; i<indentLevel; i++) {
        strcat(buffer,"    ");
    }
    
    return buffer ;
}

void        dumpCoord(sCoord* pCoord, char* prompt,int indentLevel) {
    printf("%sCoordonnees %s {\n",indent(indentLevel),prompt);
    printf("%s    LambertII : {\n",indent(indentLevel));
    printf("%s        x:%f\n",indent(indentLevel),pCoord->lambert.x);
    printf("%s        y:%f\n",indent(indentLevel),pCoord->lambert.y);
    printf("%s    }\n",indent(indentLevel));
    printf("%s    GPS : {\n",indent(indentLevel));
    printf("%s        lat:%f\n",indent(indentLevel),pCoord->latLng.lat);
    printf("%s        lng:%f\n",indent(indentLevel),pCoord->latLng.lng);
    printf("%s    }\n",indent(indentLevel));
    printf("%s}\n",indent(indentLevel));
}

void        dumpCarreCentKm(sCarre100Km *pCarre100Km,cBool bWithCutting,int indentLevel) {
    printf("%sCarre100Km {\n",indent(indentLevel));
    printf("%s    dfci : %s\n",indent(indentLevel),pCarre100Km->nomDFCI);
    dumpCoord(&pCarre100Km->coordCentre,"coordCentre",indentLevel+2);
    dumpCoord(&pCarre100Km->coordSO,"coordSO",indentLevel+2);
    dumpCoord(&pCarre100Km->coordNO,"coordNO",indentLevel+2);
    dumpCoord(&pCarre100Km->coordNE,"coordNE",indentLevel+2);
    dumpCoord(&pCarre100Km->coordSE,"coordSE",indentLevel+2);
    if ( bWithCutting == bTrue ) {
        for(int x=0; x<5; x++) {
            for(int y=0; y<5;y++) {
                dumpCarreVingtKm(& pCarre100Km->matriceCarres20Km[x][y], bWithCutting, indentLevel+1);
            }
        }
    }
    printf("%s}\n",indent(indentLevel));
}

void DFCI2CarreVingtKm(char *dfci,cBool bWithCutting, sCarre20Km  *pCarre20Km) {
    char dfci20Km[10];
    
    strcpy(dfci20Km,dfci);
    dfci20Km[4] = 'A';
    dfci20Km[5] = '0';
    dfci20Km[7] = '4';
    
//    printf("        20Km %s\n",dfci20Km);

    
    //---
    //  Nom du carré 20Km
    pCarre20Km->nomDFCI[0] = dfci[2];
    pCarre20Km->nomDFCI[1] = dfci[3];
    pCarre20Km->nomDFCI[2] = 0;
    
    //---
    //   calculer le point SO en lambert
    sLambertII lambert = DFCI2Lambert(dfci20Km);
    pCarre20Km->coordSO.lambert = lambert ;
    pCarre20Km->coordSO.latLng = lambertII2LatLng(pCarre20Km->coordSO.lambert);
    
    //---
    //   depuis le point SO calcul des autres points dans un carré de 2000 m
    pCarre20Km->coordSE.lambert.x = lambert.x + 20000 ;
    pCarre20Km->coordSE.lambert.y = lambert.y ;
    pCarre20Km->coordSE.latLng = lambertII2LatLng(pCarre20Km->coordSE.lambert);
    
    pCarre20Km->coordNE.lambert.x = lambert.x + 20000 ;
    pCarre20Km->coordNE.lambert.y = lambert.y + 20000 ;
    pCarre20Km->coordNE.latLng = lambertII2LatLng(pCarre20Km->coordNE.lambert);
    
    pCarre20Km->coordNO.lambert.x = lambert.x ;
    pCarre20Km->coordNO.lambert.y = lambert.y + 20000 ;
    pCarre20Km->coordNO.latLng = lambertII2LatLng(pCarre20Km->coordNO.lambert);

    pCarre20Km->coordCentre.lambert.x = lambert.x + 10000;
    pCarre20Km->coordCentre.lambert.y = lambert.y + 10000;
    pCarre20Km->coordCentre.latLng = lambertII2LatLng(pCarre20Km->coordCentre.lambert);

    if ( bWithCutting == bTrue ) {
        char LambertX[] = "ABCDEFGHKL";
        char LambertY[] = "0123456789";
        for(int x=0; x<10; x++) {
            for(int y=0; y<10;y++) {
                dfci20Km[4] = LambertX[x];
                dfci20Km[5] = LambertY[y];
                DFCI2CarreDeuxKm(dfci20Km, bWithCutting, &pCarre20Km->matriceCarres2Km[x][y]);
            }
        }
    }
}

void        dumpCarreVingtKm(sCarre20Km *pCarre20Km,cBool bWithCutting,int indentLevel) {
    printf("%sCarre20Km {\n",indent(indentLevel));
    printf("%s    dfci : %s\n",indent(indentLevel),pCarre20Km->nomDFCI);
    dumpCoord(&pCarre20Km->coordCentre,"coordCentre",indentLevel+2);
    dumpCoord(&pCarre20Km->coordSO,"coordSO",indentLevel+2);
    dumpCoord(&pCarre20Km->coordNO,"coordNO",indentLevel+2);
    dumpCoord(&pCarre20Km->coordNE,"coordNE",indentLevel+2);
    dumpCoord(&pCarre20Km->coordSE,"coordSE",indentLevel+2);
    if ( bWithCutting == bTrue ) {
        for(int x=0; x<10; x++) {
            for(int y=0; y<10;y++) {
                dumpCarreDeuxKm(& pCarre20Km->matriceCarres2Km[x][y], bWithCutting, indentLevel+1);
            }
        }
    }
    printf("%s}\n",indent(indentLevel));
}

void   DFCI2CarreDeuxKm(char *dfci,cBool bWithCutting,  sCarre2Km   *pCarre2Km ) {
    //---
    //  Nom du carré 2Km
    pCarre2Km->nomDFCI[0] = dfci[4];
    pCarre2Km->nomDFCI[1] = dfci[5];
    pCarre2Km->nomDFCI[2] = 0;
    
    char dfci2Km[10];
    
    strcpy(dfci2Km,dfci);
    dfci2Km[7] = '4';
    
//    printf("        2Km %s\n",dfci2Km);

    //---
    //   calculer le point SO en lambert
    sLambertII lambert = DFCI2Lambert(dfci2Km);
    
    pCarre2Km->coordSO.lambert = lambert ;
    pCarre2Km->coordSO.latLng = lambertII2LatLng(pCarre2Km->coordSO.lambert);
    
    //---
    //   depuis le point SO calcul des autres points dans un carré de 2000 m
    pCarre2Km->coordSE.lambert.x = lambert.x + 2000 ;
    pCarre2Km->coordSE.lambert.y = lambert.y ;
    pCarre2Km->coordSE.latLng = lambertII2LatLng(pCarre2Km->coordSE.lambert);

    pCarre2Km->coordNE.lambert.x = lambert.x + 2000 ;
    pCarre2Km->coordNE.lambert.y = lambert.y + 2000 ;
    pCarre2Km->coordNE.latLng = lambertII2LatLng(pCarre2Km->coordNE.lambert);

    pCarre2Km->coordNO.lambert.x = lambert.x ;
    pCarre2Km->coordNO.lambert.y = lambert.y + 2000 ;
    pCarre2Km->coordNO.latLng = lambertII2LatLng(pCarre2Km->coordNO.lambert);
    
    pCarre2Km->coordCentre.lambert.x = lambert.x + 1000;
    pCarre2Km->coordCentre.lambert.y = lambert.y + 1000;
    pCarre2Km->coordCentre.latLng = lambertII2LatLng(pCarre2Km->coordCentre.lambert);

        //---
        //  calcul des secteurs, dit "zone chasse"
        
        // secteur 1
        pCarre2Km->secteur1.numeroZone = 1 ;
        pCarre2Km->secteur1.coordSO.lambert.x = lambert.x;
        pCarre2Km->secteur1.coordSO.lambert.y = lambert.y + 1000 ;
        pCarre2Km->secteur1.coordSO.latLng = lambertII2LatLng(pCarre2Km->secteur1.coordSO.lambert);
        
        pCarre2Km->secteur1.coordSE.lambert.x = lambert.x + 1000 ;
        pCarre2Km->secteur1.coordSE.lambert.y = lambert.y + 1000 ;
        pCarre2Km->secteur1.coordSE.latLng = lambertII2LatLng(pCarre2Km->secteur1.coordSE.lambert);

        pCarre2Km->secteur1.coordNE.lambert.x = lambert.x + 1000 ;
        pCarre2Km->secteur1.coordNE.lambert.y = lambert.y + 2000 ;
        pCarre2Km->secteur1.coordNE.latLng = lambertII2LatLng(pCarre2Km->secteur1.coordNE.lambert);

        pCarre2Km->secteur1.coordNO.lambert.x = lambert.x ;
        pCarre2Km->secteur1.coordNO.lambert.y = lambert.y + 2000 ;
        pCarre2Km->secteur1.coordNO.latLng = lambertII2LatLng(pCarre2Km->secteur1.coordNO.lambert);

        pCarre2Km->secteur1.coordSEIntermediaire1.lambert.x = lambert.x + 1000 ;
        pCarre2Km->secteur1.coordSEIntermediaire1.lambert.y = lambert.y + 1500 ;
        pCarre2Km->secteur1.coordSEIntermediaire1.latLng = lambertII2LatLng(pCarre2Km->secteur1.coordSEIntermediaire1.lambert);

        pCarre2Km->secteur1.coordSEIntermediaire2.lambert.x = lambert.x + 500 ;
        pCarre2Km->secteur1.coordSEIntermediaire2.lambert.y = lambert.y + 1500 ;
        pCarre2Km->secteur1.coordSEIntermediaire2.latLng = lambertII2LatLng(pCarre2Km->secteur1.coordSEIntermediaire2.lambert);

        pCarre2Km->secteur1.coordSEIntermediaire3.lambert.x = lambert.x + 500 ;
        pCarre2Km->secteur1.coordSEIntermediaire3.lambert.y = lambert.y + 1000 ;
        pCarre2Km->secteur1.coordSEIntermediaire3.latLng = lambertII2LatLng(pCarre2Km->secteur1.coordSEIntermediaire3.lambert);

        pCarre2Km->secteur1.coordCentre = pCarre2Km->secteur1.coordSEIntermediaire2;

        // secteur 2
        pCarre2Km->secteur2.numeroZone = 2 ;
        pCarre2Km->secteur2.coordSO.lambert.x = lambert.x + 1000 ;
        pCarre2Km->secteur2.coordSO.lambert.y = lambert.y + 1000 ;
        pCarre2Km->secteur2.coordSO.latLng = lambertII2LatLng(pCarre2Km->secteur2.coordSO.lambert);
        
        pCarre2Km->secteur2.coordSE.lambert.x = lambert.x + 2000 ;
        pCarre2Km->secteur2.coordSE.lambert.y = lambert.y + 1000 ;
        pCarre2Km->secteur2.coordSE.latLng = lambertII2LatLng(pCarre2Km->secteur2.coordSE.lambert);
        
        pCarre2Km->secteur2.coordNE.lambert.x = lambert.x + 2000 ;
        pCarre2Km->secteur2.coordNE.lambert.y = lambert.y + 2000 ;
        pCarre2Km->secteur2.coordNE.latLng = lambertII2LatLng(pCarre2Km->secteur2.coordNE.lambert);
        
        pCarre2Km->secteur2.coordNO.lambert.x = lambert.x + 1000 ;
        pCarre2Km->secteur2.coordNO.lambert.y = lambert.y + 2000 ;
        pCarre2Km->secteur2.coordNO.latLng = lambertII2LatLng(pCarre2Km->secteur2.coordNO.lambert);

        pCarre2Km->secteur2.coordSOIntermediaire1.lambert.x = lambert.x + 1500 ;
        pCarre2Km->secteur2.coordSOIntermediaire1.lambert.y = lambert.y + 1000 ;
        pCarre2Km->secteur2.coordSOIntermediaire1.latLng = lambertII2LatLng(pCarre2Km->secteur2.coordSOIntermediaire1.lambert);
        
        pCarre2Km->secteur2.coordSOIntermediaire2.lambert.x = lambert.x + 1500 ;
        pCarre2Km->secteur2.coordSOIntermediaire2.lambert.y = lambert.y + 1500 ;
        pCarre2Km->secteur2.coordSOIntermediaire2.latLng = lambertII2LatLng(pCarre2Km->secteur2.coordSOIntermediaire2.lambert);
        
        pCarre2Km->secteur2.coordSOIntermediaire3.lambert.x = lambert.x + 1000 ;
        pCarre2Km->secteur2.coordSOIntermediaire3.lambert.y = lambert.y + 1500 ;
        pCarre2Km->secteur2.coordSOIntermediaire3.latLng = lambertII2LatLng(pCarre2Km->secteur2.coordSOIntermediaire3.lambert);
        
        pCarre2Km->secteur2.coordCentre = pCarre2Km->secteur2.coordSOIntermediaire2;

        // secteur 3
        pCarre2Km->secteur3.numeroZone = 3 ;
        pCarre2Km->secteur3.coordSO.lambert.x = lambert.x + 1000 ;
        pCarre2Km->secteur3.coordSO.lambert.y = lambert.y  ;
        pCarre2Km->secteur3.coordSO.latLng = lambertII2LatLng(pCarre2Km->secteur3.coordSO.lambert);
        
        pCarre2Km->secteur3.coordSE.lambert.x = lambert.x + 2000 ;
        pCarre2Km->secteur3.coordSE.lambert.y = lambert.y  ;
        pCarre2Km->secteur3.coordSE.latLng = lambertII2LatLng(pCarre2Km->secteur3.coordSE.lambert);
        
        pCarre2Km->secteur3.coordNE.lambert.x = lambert.x + 2000 ;
        pCarre2Km->secteur3.coordNE.lambert.y = lambert.y + 1000 ;
        pCarre2Km->secteur3.coordNE.latLng = lambertII2LatLng(pCarre2Km->secteur3.coordNE.lambert);
        
        pCarre2Km->secteur3.coordNO.lambert.x = lambert.x + 1000 ;
        pCarre2Km->secteur3.coordNO.lambert.y = lambert.y + 1000 ;
        pCarre2Km->secteur3.coordNO.latLng = lambertII2LatLng(pCarre2Km->secteur3.coordNO.lambert);

        pCarre2Km->secteur3.coordNOIntermediaire1.lambert.x = lambert.x + 1000 ;
        pCarre2Km->secteur3.coordNOIntermediaire1.lambert.y = lambert.y + 500 ;
        pCarre2Km->secteur3.coordNOIntermediaire1.latLng = lambertII2LatLng(pCarre2Km->secteur3.coordNOIntermediaire1.lambert);
        
        pCarre2Km->secteur3.coordNOIntermediaire2.lambert.x = lambert.x + 1500 ;
        pCarre2Km->secteur3.coordNOIntermediaire2.lambert.y = lambert.y + 500 ;
        pCarre2Km->secteur3.coordNOIntermediaire2.latLng = lambertII2LatLng(pCarre2Km->secteur3.coordNOIntermediaire2.lambert);
        
        pCarre2Km->secteur3.coordNOIntermediaire3.lambert.x = lambert.x + 1500 ;
        pCarre2Km->secteur3.coordNOIntermediaire3.lambert.y = lambert.y + 1000 ;
        pCarre2Km->secteur3.coordNOIntermediaire3.latLng = lambertII2LatLng(pCarre2Km->secteur3.coordNOIntermediaire3.lambert);
        
        pCarre2Km->secteur3.coordCentre = pCarre2Km->secteur3.coordNOIntermediaire2;

        // secteur 4
        pCarre2Km->secteur4.numeroZone = 4 ;
        pCarre2Km->secteur4.coordSO.lambert.x = lambert.x  ;
        pCarre2Km->secteur4.coordSO.lambert.y = lambert.y  ;
        pCarre2Km->secteur4.coordSO.latLng = lambertII2LatLng(pCarre2Km->secteur4.coordSO.lambert);
        
        pCarre2Km->secteur4.coordSE.lambert.x = lambert.x + 1000 ;
        pCarre2Km->secteur4.coordSE.lambert.y = lambert.y  ;
        pCarre2Km->secteur4.coordSE.latLng = lambertII2LatLng(pCarre2Km->secteur4.coordSE.lambert);
        
        pCarre2Km->secteur4.coordNE.lambert.x = lambert.x + 1000 ;
        pCarre2Km->secteur4.coordNE.lambert.y = lambert.y + 1000 ;
        pCarre2Km->secteur4.coordNE.latLng = lambertII2LatLng(pCarre2Km->secteur4.coordNE.lambert);
        
        pCarre2Km->secteur4.coordNO.lambert.x = lambert.x  ;
        pCarre2Km->secteur4.coordNO.lambert.y = lambert.y + 1000 ;
        pCarre2Km->secteur4.coordNO.latLng = lambertII2LatLng(pCarre2Km->secteur4.coordNO.lambert);

        pCarre2Km->secteur4.coordNEIntermediaire1.lambert.x = lambert.x + 500 ;
        pCarre2Km->secteur4.coordNEIntermediaire1.lambert.y = lambert.y + 1000 ;
        pCarre2Km->secteur4.coordNEIntermediaire1.latLng = lambertII2LatLng(pCarre2Km->secteur4.coordNEIntermediaire1.lambert);
        
        pCarre2Km->secteur4.coordNEIntermediaire2.lambert.x = lambert.x + 500 ;
        pCarre2Km->secteur4.coordNEIntermediaire2.lambert.y = lambert.y + 500 ;
        pCarre2Km->secteur4.coordNEIntermediaire2.latLng = lambertII2LatLng(pCarre2Km->secteur4.coordNEIntermediaire2.lambert);
        
        pCarre2Km->secteur4.coordNEIntermediaire3.lambert.x = lambert.x + 1000 ;
        pCarre2Km->secteur4.coordNEIntermediaire3.lambert.y = lambert.y + 500 ;
        pCarre2Km->secteur4.coordNEIntermediaire3.latLng = lambertII2LatLng(pCarre2Km->secteur4.coordNEIntermediaire3.lambert);
        
        pCarre2Km->secteur4.coordCentre = pCarre2Km->secteur4.coordNEIntermediaire2;

        // secteur 5
        pCarre2Km->secteur5.numeroZone = 5 ;
        pCarre2Km->secteur5.coordSO.lambert.x = lambert.x + 500 ;
        pCarre2Km->secteur5.coordSO.lambert.y = lambert.y + 500 ;
        pCarre2Km->secteur5.coordSO.latLng = lambertII2LatLng(pCarre2Km->secteur5.coordSO.lambert);
        
        pCarre2Km->secteur5.coordSE.lambert.x = lambert.x + 1500 ;
        pCarre2Km->secteur5.coordSE.lambert.y = lambert.y + 500 ;
        pCarre2Km->secteur5.coordSE.latLng = lambertII2LatLng(pCarre2Km->secteur5.coordSE.lambert);
        
        pCarre2Km->secteur5.coordNE.lambert.x = lambert.x + 1500 ;
        pCarre2Km->secteur5.coordNE.lambert.y = lambert.y + 1500 ;
        pCarre2Km->secteur5.coordNE.latLng = lambertII2LatLng(pCarre2Km->secteur5.coordNE.lambert);
        
        pCarre2Km->secteur5.coordNO.lambert.x = lambert.x + 500 ;
        pCarre2Km->secteur5.coordNO.lambert.y = lambert.y + 1500 ;
        pCarre2Km->secteur5.coordNO.latLng = lambertII2LatLng(pCarre2Km->secteur5.coordNO.lambert);
        
        pCarre2Km->secteur5.coordCentre.lambert.x = lambert.x + 1000 ;
        pCarre2Km->secteur5.coordCentre.lambert.y = lambert.y + 1000 ;
        pCarre2Km->secteur5.coordCentre.latLng = lambertII2LatLng(pCarre2Km->secteur5.coordCentre.lambert);
}

void        dumpCarreDeuxKm(sCarre2Km *pCarre2Km,cBool bWithCutting,int indentLevel) {
    printf("%sCarre2Km {\n",indent(indentLevel));
    printf("%s    dfci : %s\n",indent(indentLevel),pCarre2Km->nomDFCI);
    dumpCoord(&pCarre2Km->coordCentre,"coordCentre",indentLevel+2);
    dumpCoord(&pCarre2Km->coordSO,"coordSO",indentLevel+2);
    dumpCoord(&pCarre2Km->coordNO,"coordNO",indentLevel+2);
    dumpCoord(&pCarre2Km->coordNE,"coordNE",indentLevel+2);
    dumpCoord(&pCarre2Km->coordSE,"coordSE",indentLevel+2);
        printf("%s        secteur1 {\n",indent(indentLevel));
        dumpCoord(&pCarre2Km->secteur1.coordSO, "coordSO", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur1.coordNO, "coordNO", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur1.coordNE, "coordNE", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur1.coordSEIntermediaire1, "coordSEIntermediaire1", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur1.coordSEIntermediaire2, "coordSEIntermediaire2", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur1.coordSEIntermediaire3, "coordSEIntermediaire3", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur1.coordSE, "coordSE", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur1.coordCentre,"coordCentre",indentLevel+3);
        printf("%s        }\n",indent(indentLevel));

        printf("%s        secteur2 {\n",indent(indentLevel));
        dumpCoord(&pCarre2Km->secteur2.coordSO, "coordSO", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur2.coordSOIntermediaire1, "coordSOIntermediaire1", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur2.coordSOIntermediaire2, "coordSOIntermediaire2", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur2.coordSOIntermediaire3, "coordSOIntermediaire3", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur2.coordNO, "coordNO", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur2.coordNE, "coordNE", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur2.coordSE, "coordSE", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur2.coordCentre,"coordCentre",indentLevel+3);
        printf("%s        }\n",indent(indentLevel));

        printf("%s        secteur3 {\n",indent(indentLevel));
        dumpCoord(&pCarre2Km->secteur3.coordSO, "coordSO", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur3.coordNOIntermediaire1, "coordNOIntermediaire1", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur3.coordNOIntermediaire2, "coordNOIntermediaire2", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur3.coordNOIntermediaire3, "coordNOIntermediaire3", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur3.coordNO, "coordNO", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur3.coordNE, "coordNE", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur3.coordSE, "coordSE", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur3.coordCentre,"coordCentre",indentLevel+3);
        printf("%s        }\n",indent(indentLevel));

        printf("%s        secteur4 {\n",indent(indentLevel));
        dumpCoord(&pCarre2Km->secteur4.coordSO, "coordSO", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur4.coordNO, "coordNO", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur4.coordNEIntermediaire1, "coordNEIntermediaire1", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur4.coordNEIntermediaire2, "coordNEIntermediaire2", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur4.coordNEIntermediaire3, "coordNEIntermediaire3", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur4.coordNE, "coordNE", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur4.coordSE, "coordSE", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur4.coordCentre,"coordCentre",indentLevel+3);
        printf("%s        }\n",indent(indentLevel));

        printf("%s        secteur5 {\n",indent(indentLevel));
        dumpCoord(&pCarre2Km->secteur5.coordSO, "coordSO", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur5.coordNO, "coordNO", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur5.coordNE, "coordNE", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur5.coordSE, "coordSE", indentLevel+3);
        dumpCoord(&pCarre2Km->secteur5.coordCentre,"coordCentre",indentLevel+3);
        printf("%s        }\n",indent(indentLevel));

    printf("%s}\n",indent(indentLevel));

}

sLatLng     lambertII2LatLng(sLambertII sLambert) {
    sLatLng latLng ;
    double latNTF, lonNTF ;
    
    latNTF = LambLatNTF(sLambert.x, sLambert.y, 0);
    lonNTF = LambLonNTF(sLambert.x, sLambert.y, 0);
    
    latLng.lat = NTFLatWGS(latNTF, lonNTF) ;
    latLng.lng = NTFLonWGS(latNTF, lonNTF) ;

    return latLng ;
}


int    InStr(char *myString, char searchChar,size_t maxLen) {
    int i=0;
    
    while ( (myString[i] != searchChar) && (i<maxLen) ) {
        i++;
    }
    return i;
}

double IsomLat(double latitIsom,double premExcEllips, double tolConverg) {
//    double clarke1880=0.08248325676342;
//    double iagGrs80=0.08182297965731;
    
    double rad2Deg=180/M_PI;
//    double deg2Rad=M_PI/180;
    
    double EL=exp(latitIsom);
    
    double rPremEx=premExcEllips;
    double rTolConv=tolConverg;
    
    double s0 = 0;
    double s1 = 2 * atan(EL)-M_PI/2;
    double d=0;
    
    while (fabs(s0 - s1) > rTolConv ) {
        s0 = s1;
        d = log(((1 + rPremEx * sin(s0)) / (1 - rPremEx * sin(s0))));
        d = exp(d*(rPremEx / 2));
        s1 = 2 * atan(d*EL)-M_PI/2;
    }
    return s1 * rad2Deg ;
}

double NTFLatWGS(double gLat, double gLon) {
    double Phi, Lambda, h, AA, aNTF, aWGS, b, bNTF, bWGS, eNTF, eWGS, e2, v, X, Y, Z, p, r, f, u;
    double MeridParis;
    MeridParis=2.33722916666667;

    double rad2Deg=180/M_PI;
    double deg2Rad=M_PI/180;
    
    Phi = gLat*deg2Rad;
    Lambda = (gLon+MeridParis)*deg2Rad;
    h = 0;

    // aNTF = Demi Grand-Axe de l'ellipsoïde de Clarke 1880
    aNTF = 6378249.2;
    
    // bNTF = Demi Petit-Axe de l'ellipsoïde de Clarke 1880
    bNTF = 6356515 ;

    // eNTF = Premiere Excentricite de l'ellipsoïde de Clarke 1880
    eNTF = sqrt(1 - (bNTF / aNTF)*(bNTF / aNTF));
    
    // aWGS = Demi Grand-Axe de l'ellipsoïde WGS84
    aWGS = 6378137;
    
    // bWGS = Demi Petit-Axe de l'ellipsoïde WGS84
    bWGS = 6356752.314;
    
    // eWGS = Premiere Excentricite de l'ellipsoïde WGS84
    eWGS = sqrt(1 - (bWGS / aWGS)*(bWGS / aWGS));
    AA = aNTF;
    e2 = eNTF * eNTF;
    f = (AA - b) / AA;
    v = AA / sqrt(1 - e2 * sin(Phi) * sin(Phi));
    
    // Coordonnee Geocentriques NTF : X, Y, Z
    X = (v + h) * cos(Phi) * cos(Lambda);
    Y = (v + h) * cos(Phi) * sin(Lambda);
    Z = ((1 - e2) * v + h) * sin(Phi);
    
    // Changement de referentiel NGF vers WGS84
    X = X - 168;
    Y = Y - 60;
    Z = Z + 320;
    AA = aWGS;
    b = bWGS;
    e2 = eWGS * eWGS;
    f = (AA - b) / AA;
    p = sqrt(X * X + Y * Y);
    r = p + Z * Z;
    u = atan((Z / p) * ((1 - f) + (e2 * AA / r)));
    Phi = atan((Z * (1 - f) + e2 * AA * sin(u) * sin(u) * sin(u)) / ((1 - f) * (p - e2 * AA * cos(u) * cos(u) * cos(u))));
    
    return Phi*rad2Deg;
}

double NTFLonWGS(double gLat, double gLon) {
    // Calcul de la Longitude WGS84 à partir des coordonnees geographiques NTF en Degres decimaux
    // GLat, GLon en Degres decimaux
    
    double Phi, Lambda, h, AA, aNTF, b, bNTF, eNTF, e2, v, X, Y, Z, f;
    double MeridParis;
    MeridParis=2.33722916666667;
    
    double rad2Deg=180/M_PI;
    double deg2Rad=M_PI/180;
    
    // h = hauteur sur l'ellipsoïde - mis à zero
    Phi = gLat*deg2Rad;
    Lambda = (gLon+MeridParis)*deg2Rad;
    h = 0;
    
    // aNTF = Demi Grand-Axe de l'ellipsoïde de Clarke 1880
    aNTF = 6378249.2;
    
    // bNTF = Demi Petit-Axe de l'ellipsoïde de Clarke 1880
    bNTF = 6356515 ;
    
    // eNTF = Premiere Excentricite de l'ellipsoïde de Clarke 1880
    eNTF= sqrt(1 - (bNTF / aNTF)*(bNTF / aNTF));
    AA = aNTF;
    e2 = eNTF * eNTF;
    f = (AA - b) / AA;
    v = AA / sqrt(1 - e2 * sin(Phi) * sin(Phi));
    
    // Coordonnee Geocentriques NTF : X, Y, Z
    X = (v + h) * cos(Phi) * cos(Lambda);
    Y = (v + h) * cos(Phi) * sin(Lambda);
    Z = ((1 - e2) * v + h) * sin(Phi);
    
    // Changement de referentiel NTF vers WGS84
    X = X - 168;
    Y = Y - 60;
    Z = Z + 320;
    
    Lambda = atan(Y / X);
    if ( X < 0 ) {
        Lambda = Lambda + M_PI;
    }
    return Lambda*rad2Deg;
}

double LambLatNTF(double xLambert, double yLambert,int TypLamb) {
    double Clarke1880;
    double e, R, L, n, c, Xs, Ys;

//    double rad2Deg=180/M_PI;
//    double deg2Rad=M_PI/180;

    Clarke1880=0.08248325676342;
    e=Clarke1880;
    
    //   Lambert II etendu par defaut
    switch ( TypLamb ) {
        case 1: {
            n = 0.7604059656;
            c = 11603796.98;
            Xs = 600000;
            Ys = 5657616.674;
        } break ;
            
        case 2: {
            n = 0.7289686274;
            c = 11745793.39;
            Xs = 600000;
            Ys = 6199695.768;
            
        } break ;
            
        case 3: {
            n = 0.6959127966;
            c = 11947992.52;
            Xs = 600000;
            Ys = 6791905.085;
        } break ;
            
        case 4: {
            n = 0.6712679322;
            c = 12136281.99;
            Xs = 234.358;
            Ys = 7239161.542;
        } break ;
            
        default: {
            n = 0.7289686274;
            c = 11745793.39;
            Xs = 600000;
            Ys = 8199695.768;
        } break ;
        
    }

    R = sqrt((xLambert-Xs)*(xLambert-Xs) + (yLambert-Ys)*(yLambert-Ys));
    L = -1 / n * log(fabs(R/c));
    return IsomLat(L, e, 0.00000000001);
}

double LambLonNTF(double xLambert, double yLambert,int TypLamb) {
    double LX, R, g, n, c, Xs, Ys;

    double rad2Deg=180/M_PI;
//    double deg2Rad=M_PI/180;

//    double MeridParis = 2.33722916666667;

    //   Lambert II etendu par defaut
    switch ( TypLamb ) {
        case 1: {
            n = 0.7604059656;
            c = 11603796.98;
            Xs = 600000;
            Ys = 5657616.674;
        } break ;
            
        case 2: {
            n = 0.7289686274;
            c = 11745793.39;
            Xs = 600000;
            Ys = 6199695.768;
            
        } break ;
            
        case 3: {
            n = 0.6959127966;
            c = 11947992.52;
            Xs = 600000;
            Ys = 6791905.085;
        } break ;
            
        case 4: {
            n = 0.6712679322;
            c = 12136281.99;
            Xs = 234.358;
            Ys = 7239161.542;
        } break ;
            
        default: {
            n = 0.7289686274;
            c = 11745793.39;
            Xs = 600000;
            Ys = 8199695.768;
        } break ;
            
    }
    
    R = sqrt((xLambert-Xs)*(xLambert-Xs) + (yLambert-Ys)*(yLambert-Ys));
    g = atan((xLambert-Xs) / (Ys-yLambert));
    LX= g / n;
    return LX*rad2Deg;
}


