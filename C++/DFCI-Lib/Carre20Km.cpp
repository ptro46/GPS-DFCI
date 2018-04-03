//
//  Carre20Km.cpp
//  DFCI-Lib-CPP
//
//  Created by Patrice Trognon on 28/10/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#include "Carre20Km.hpp"

#include "Globals.h"

#include "Coord.hpp"
#include "Carre2Km.hpp"

#include "LambertII.hpp"
#include "LatLng.hpp"

#include <iostream>
using namespace std;

Carre20Km::Carre20Km(string dfci, Carre100Km *poCarre100Km_) {
    nomDFCIComplet = dfci ;
    nomDFCICarre20Km = dfci.substr(0,4);
    
    poCarre100Km = poCarre100Km_ ;
    
    string dfci20Km = dfci.substr(0,4) + "A0.4";
    
    //---
    //   calculer le point SO en lambert
    LambertII lambert;
    LatLng latLng;
    
    lambertIIFromDFCI(dfci20Km, & lambert);
    latLngFromLambertII(lambert, & latLng);
    piCoordSO = new Coord(&latLng, &lambert);

    //---
    //   depuis le point SO calcul des autres points dans un carré de 100 000 m
    {
        LambertII lambertIISE(lambert.x + 20000,
                              lambert.y);
        LatLng latLngSE;
        latLngFromLambertII(lambertIISE, & latLngSE);
        piCoordSE = new Coord(&latLngSE, &lambertIISE);
    }
    
    {
        LambertII lambertIINE(lambert.x + 20000,
                              lambert.y + 20000);
        LatLng latLngNE;
        latLngFromLambertII(lambertIINE, & latLngNE);
        piCoordNE = new Coord(&latLngNE, &lambertIINE);
    }
    
    {
        LambertII lambertIINO(lambert.x ,
                              lambert.y + 20000);
        LatLng latLngNO;
        latLngFromLambertII(lambertIINO, & latLngNO);
        piCoordNO = new Coord(&latLngNO, &lambertIINO);
    }
    
    {
        LambertII lambertIICentre(lambert.x + 10000,
                                  lambert.y + 10000);
        LatLng latLngCentre;
        latLngFromLambertII(lambertIICentre, & latLngCentre);
        piCoordCentre = new Coord(&latLngCentre, &lambertIICentre);
    }

    for(int x=0; x<10; x++) {
        for(int y=0; y<10;y++) {
            matriceCarre2Km[x][y] = nullptr ;
        }
    }

}

Carre20Km::~Carre20Km() {
    safeDeletePtr(piCoordSO)
    safeDeletePtr(piCoordSE)
    safeDeletePtr(piCoordNE)
    safeDeletePtr(piCoordNO)
    safeDeletePtr(piCoordCentre)

    if ( matriceCarre2Km[0][0] == nullptr ) {
        for(int x=0; x<10; x++) {
            for(int y=0; y<10;y++) {
                safeDeletePtr(matriceCarre2Km[x][y])
            }
        }
    }
}

void
Carre20Km::performDetails() {
    if ( matriceCarre2Km[0][0] == nullptr ) {
        char LambertX[] = "ABCDEFGHKL";
        char LambertY[] = "0123456789";
        for(int x=0; x<10; x++) {
            for(int y=0; y<10;y++) {
                char dfci[9];
                sprintf(dfci, "%s%c%c.4",nomDFCIComplet.substr(0,4).c_str(),LambertX[x],LambertY[y]);
                matriceCarre2Km[x][y] = new Carre2Km(dfci,this);
            }
        }
    }

}

Carre2Km*
Carre20Km::carre2Km(int x, int y) {
    return matriceCarre2Km[x][y] ;
}

Carre20Km*
Carre20Km::northCarre20Km() {
    return nullptr ;
}

Carre20Km*
Carre20Km::northEastCarre20Km() {
    return nullptr ;
}

Carre20Km*
Carre20Km::eastCarre20Km() {
    return nullptr ;
}

Carre20Km*
Carre20Km::southEastCarre20Km() {
    return nullptr ;
}

Carre20Km*
Carre20Km::southCarre20Km() {
    return nullptr ;
}

Carre20Km*
Carre20Km::southWestCarre20Km() {
    return nullptr ;
}

Carre20Km*
Carre20Km::westCarre20Km() {
    return nullptr ;
}

Carre20Km*
Carre20Km::northWestCarre20Km() {
    return nullptr ;
}

void
Carre20Km::dumpWithIndentLevel(int indentLevel) {
    cout << indentWithIndentLevel(indentLevel) << "Carre20Km {" << endl ;
    cout << indentWithIndentLevel(indentLevel) << "    dfci : " << nomDFCICarre20Km << endl ;
    dumpCoordWithPrompt(*piCoordCentre, "coordCentre", indentLevel+2);
    dumpCoordWithPrompt(*piCoordSO, "coordSO", indentLevel+2);
    dumpCoordWithPrompt(*piCoordNO, "coordNO", indentLevel+2);
    dumpCoordWithPrompt(*piCoordNE, "coordNE", indentLevel+2);
    dumpCoordWithPrompt(*piCoordSE, "coordSE", indentLevel+2);
    if ( matriceCarre2Km[0][0] != nullptr ) {
        for(int x=0; x<10; x++) {
            for(int y=0; y<10;y++) {
                matriceCarre2Km[x][y]->dumpWithIndentLevel(indentLevel+1);
            }
        }
    }
    cout << indentWithIndentLevel(indentLevel) << "}" << endl ;
}
