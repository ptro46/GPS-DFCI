//
//  Carre100Km.cpp
//  DFCI-Lib-CPP
//
//  Created by Patrice Trognon on 28/10/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#include "Carre100Km.hpp"

#include "Globals.h"

#include "Coord.hpp"
#include "Carre20Km.hpp"

#include "LambertII.hpp"
#include "LatLng.hpp"

#include "DFCICacheManager.hpp"

#include <iostream>
using namespace std;

Carre100Km::Carre100Km(string dfci) {
    nomDFCIComplet = dfci ;
    nomDFCICarre100Km = dfci.substr(0,2);
    
    string dfci100Km = nomDFCICarre100Km + "00A0.4";
    
    //---
    //   calculer le point SO en lambert
    LambertII lambert;
    LatLng latLng;
    
    lambertIIFromDFCI(dfci100Km, & lambert);
    latLngFromLambertII(lambert, & latLng);
    piCoordSO = new Coord(&latLng, &lambert);
    
    //---
    //   depuis le point SO calcul des autres points dans un carré de 100 000 m
    {
        LambertII lambertIISE(lambert.x + 100000,
                              lambert.y);
        LatLng latLngSE;
        latLngFromLambertII(lambertIISE, & latLngSE);
        piCoordSE = new Coord(&latLngSE, &lambertIISE);
    }
    
    {
        LambertII lambertIINE(lambert.x + 100000,
                              lambert.y + 100000);
        LatLng latLngNE;
        latLngFromLambertII(lambertIINE, & latLngNE);
        piCoordNE = new Coord(&latLngNE, &lambertIINE);
    }

    {
        LambertII lambertIINO(lambert.x ,
                              lambert.y + 100000);
        LatLng latLngNO;
        latLngFromLambertII(lambertIINO, & latLngNO);
        piCoordNO = new Coord(&latLngNO, &lambertIINO);
    }

    {
        LambertII lambertIICentre(lambert.x + 50000,
                                  lambert.y + 50000);
        LatLng latLngCentre;
        latLngFromLambertII(lambertIICentre, & latLngCentre);
        piCoordCentre = new Coord(&latLngCentre, &lambertIICentre);
    }
    
    for(int x=0; x<5; x++) {
        for(int y=0; y<5;y++) {
            matriceCarre20Km[x][y] = nullptr ;
        }
    }
}

Carre100Km::~Carre100Km() {
    safeDeletePtr(piCoordSO)
    safeDeletePtr(piCoordSE)
    safeDeletePtr(piCoordNE)
    safeDeletePtr(piCoordNO)
    safeDeletePtr(piCoordCentre)
    
    if ( matriceCarre20Km[0][0] == nullptr ) {
        for(int x=0; x<5; x++) {
            for(int y=0; y<5;y++) {
                safeDeletePtr(matriceCarre20Km[x][y])
            }
        }
    }
}

void
Carre100Km::performDetails() {
    if ( matriceCarre20Km[0][0] == nullptr ) {
        char LambertX[] = "02468";
        char LambertY[] = "02468";
        for(int x=0; x<5; x++) {
            for(int y=0; y<5;y++) {
                char dfci[9];
                sprintf(dfci, "%s%c%cA0.4",nomDFCICarre100Km.c_str(),LambertX[x],LambertY[y]);
                matriceCarre20Km[x][y] = new Carre20Km(dfci,this);
            }
        }
        
        for(int x=0; x<5; x++) {
            for(int y=0; y<5;y++) {
                matriceCarre20Km[x][y]->performDetails();
            }
        }
    }
}

Carre20Km*
Carre100Km::carre20Km(int x, int y) {
    return matriceCarre20Km[x][y] ;
}

Carre100Km*
Carre100Km::northCarre100Km() {
    string nameNorth = northDFCIName();
    Carre100Km *carre100Km = DFCICacheManager::getInstance()->carre100KmFromDFCI(nameNorth);
    if ( carre100Km == nullptr ) {
        carre100Km = new Carre100Km(nameNorth);
    }
    return carre100Km ;
}

Carre100Km*
Carre100Km::northEastCarre100Km() {
    return nullptr ;
}

Carre100Km*
Carre100Km::eastCarre100Km() {
    return nullptr ;
}

Carre100Km*
Carre100Km::southEastCarre100Km() {
    return nullptr ;
}

Carre100Km*
Carre100Km::southCarre100Km() {
    return nullptr ;
}

Carre100Km*
Carre100Km::southWestCarre100Km() {
    return nullptr ;
}

Carre100Km*
Carre100Km::westCarre100Km() {
    return nullptr ;
}

Carre100Km*
Carre100Km::northWestCarre100Km() {
    return nullptr ;
}

void
Carre100Km::dumpWithIndentLevel(int indentLevel) {
    cout << indentWithIndentLevel(indentLevel) << "Carre100Km {" << endl ;
    cout << indentWithIndentLevel(indentLevel) << "    dfci : " << nomDFCICarre100Km << endl ;
    dumpCoordWithPrompt(*piCoordCentre, "coordCentre", indentLevel+2);
    dumpCoordWithPrompt(*piCoordSO, "coordSO", indentLevel+2);
    dumpCoordWithPrompt(*piCoordNO, "coordNO", indentLevel+2);
    dumpCoordWithPrompt(*piCoordNE, "coordNE", indentLevel+2);
    dumpCoordWithPrompt(*piCoordSE, "coordSE", indentLevel+2);
    if ( matriceCarre20Km[0][0] != nullptr ) {
        for(int x=0; x<5; x++) {
            for(int y=0; y<5;y++) {
                matriceCarre20Km[x][y]->dumpWithIndentLevel(indentLevel+1);
            }
        }
    }
    cout << indentWithIndentLevel(indentLevel) << "}" << endl ;
}
