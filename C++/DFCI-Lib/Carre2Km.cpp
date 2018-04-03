//
//  Carre2Km.cpp
//  DFCI-Lib-CPP
//
//  Created by Patrice Trognon on 28/10/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#include "Carre2Km.hpp"

#include "Globals.h"

#include "Coord.hpp"
#include "Carre2Km.hpp"

#include "LambertII.hpp"
#include "LatLng.hpp"

#include "ZoneChasseSecteur1.hpp"
#include "ZoneChasseSecteur2.hpp"
#include "ZoneChasseSecteur3.hpp"
#include "ZoneChasseSecteur4.hpp"
#include "ZoneChasseSecteur5.hpp"

#include <iostream>
using namespace std;

Carre2Km::Carre2Km(string dfci, Carre20Km* poCarre20Km_) {
    nomDFCIComplet = dfci ;
    nomDFCICarre2Km = dfci.substr(0,6);
    
    poCarre20Km = poCarre20Km_ ;
    
    string dfci20Km = dfci.substr(0,6) + ".4";
   
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
        LambertII lambertIISE(lambert.x + 2000,
                              lambert.y);
        LatLng latLngSE;
        latLngFromLambertII(lambertIISE, & latLngSE);
        piCoordSE = new Coord(&latLngSE, &lambertIISE);
    }
    
    {
        LambertII lambertIINE(lambert.x + 2000,
                              lambert.y + 2000);
        LatLng latLngNE;
        latLngFromLambertII(lambertIINE, & latLngNE);
        piCoordNE = new Coord(&latLngNE, &lambertIINE);
    }
    
    {
        LambertII lambertIINO(lambert.x ,
                              lambert.y + 2000);
        LatLng latLngNO;
        latLngFromLambertII(lambertIINO, & latLngNO);
        piCoordNO = new Coord(&latLngNO, &lambertIINO);
    }
    
    {
        LambertII lambertIICentre(lambert.x + 1000,
                                  lambert.y + 1000);
        LatLng latLngCentre;
        latLngFromLambertII(lambertIICentre, & latLngCentre);
        piCoordCentre = new Coord(&latLngCentre, &lambertIICentre);
    }
    
    piSecteur1 = new ZoneChasseSecteur1(1,this,lambert);
    piSecteur2 = new ZoneChasseSecteur2(1,this,lambert);
    piSecteur3 = new ZoneChasseSecteur3(1,this,lambert);
    piSecteur4 = new ZoneChasseSecteur4(1,this,lambert);
    piSecteur5 = new ZoneChasseSecteur5(1,this,lambert);
}

Carre2Km::~Carre2Km() {
    safeDeletePtr(piCoordSO)
    safeDeletePtr(piCoordSE)
    safeDeletePtr(piCoordNE)
    safeDeletePtr(piCoordNO)
    safeDeletePtr(piCoordCentre)

    safeDeletePtr(piSecteur1)
    safeDeletePtr(piSecteur2)
    safeDeletePtr(piSecteur3)
    safeDeletePtr(piSecteur4)
    safeDeletePtr(piSecteur5)
}

Carre2Km*
Carre2Km::northCarre2Km() {
    return nullptr ;
}

Carre2Km*
Carre2Km::northEastCarre2Km() {
    return nullptr ;
}

Carre2Km*
Carre2Km::eastCarre2Km() {
    return nullptr ;
}

Carre2Km*
Carre2Km::southEastCarre2Km() {
    return nullptr ;
}

Carre2Km*
Carre2Km::southCarre2Km() {
    return nullptr ;
}

Carre2Km*
Carre2Km::southWestCarre2Km() {
    return nullptr ;
}

Carre2Km*
Carre2Km::westCarre2Km() {
    return nullptr ;
}

Carre2Km*
Carre2Km::northWestCarre2Km() {
    return nullptr ;
}

void
Carre2Km::dumpWithIndentLevel(int indentLevel) {
    cout << indentWithIndentLevel(indentLevel) << "Carre2Km {" << endl ;
    cout << indentWithIndentLevel(indentLevel) << "    dfci : " << nomDFCICarre2Km << endl ;
    dumpCoordWithPrompt(*piCoordCentre, "coordCentre", indentLevel+2);
    dumpCoordWithPrompt(*piCoordSO, "coordSO", indentLevel+2);
    dumpCoordWithPrompt(*piCoordNO, "coordNO", indentLevel+2);
    dumpCoordWithPrompt(*piCoordNE, "coordNE", indentLevel+2);
    dumpCoordWithPrompt(*piCoordSE, "coordSE", indentLevel+2);

    cout << indentWithIndentLevel(indentLevel) << "        secteur1 {" << endl ;
    dumpCoordWithPrompt(*piSecteur1->piCoordSO, "coordSO", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur1->piCoordNO, "coordNO", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur1->piCoordNE, "coordNE", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur1->piCoordSEIntermediaire1, "coordSEIntermediaire1", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur1->piCoordSEIntermediaire2, "coordSEIntermediaire2", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur1->piCoordSEIntermediaire3, "coordSEIntermediaire3", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur1->piCoordSE, "coordSE", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur1->piCoordCentre, "coordCentre", indentLevel+3);
    cout << indentWithIndentLevel(indentLevel) << "        }" << endl ;

    cout << indentWithIndentLevel(indentLevel) << "        secteur2 {" << endl ;
    dumpCoordWithPrompt(*piSecteur2->piCoordSO, "coordSO", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur2->piCoordSOIntermediaire1, "coordSOIntermediaire1", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur2->piCoordSOIntermediaire2, "coordSOIntermediaire2", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur2->piCoordSOIntermediaire3, "coordSOIntermediaire3", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur2->piCoordNO, "coordNO", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur2->piCoordNE, "coordNE", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur2->piCoordSE, "coordSE", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur2->piCoordCentre, "coordCentre", indentLevel+3);
    cout << indentWithIndentLevel(indentLevel) << "        }" << endl ;

    cout << indentWithIndentLevel(indentLevel) << "        secteur3 {" << endl ;
    dumpCoordWithPrompt(*piSecteur3->piCoordSO, "coordSO", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur3->piCoordNOIntermediaire1, "coordNOIntermediaire1", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur3->piCoordNOIntermediaire2, "coordNOIntermediaire2", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur3->piCoordNOIntermediaire3, "coordNOIntermediaire3", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur3->piCoordNO, "coordNO", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur3->piCoordNE, "coordNE", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur3->piCoordSE, "coordSE", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur3->piCoordCentre, "coordCentre", indentLevel+3);
    cout << indentWithIndentLevel(indentLevel) << "        }" << endl ;

    cout << indentWithIndentLevel(indentLevel) << "        secteur4 {" << endl ;
    dumpCoordWithPrompt(*piSecteur4->piCoordSO, "coordSO", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur4->piCoordNO, "coordNO", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur4->piCoordNEIntermediaire1, "coordNEIntermediaire1", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur4->piCoordNEIntermediaire2, "coordNEIntermediaire2", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur4->piCoordNEIntermediaire3, "coordNEIntermediaire3", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur4->piCoordNE, "coordNE", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur4->piCoordSE, "coordSE", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur4->piCoordCentre, "coordCentre", indentLevel+3);
    cout << indentWithIndentLevel(indentLevel) << "        }" << endl ;

    cout << indentWithIndentLevel(indentLevel) << "        secteur5 {" << endl ;
    dumpCoordWithPrompt(*piSecteur5->piCoordSO, "coordSO", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur5->piCoordNO, "coordNO", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur5->piCoordNE, "coordNE", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur5->piCoordSE, "coordSE", indentLevel+3);
    dumpCoordWithPrompt(*piSecteur5->piCoordCentre, "coordCentre", indentLevel+3);
    cout << indentWithIndentLevel(indentLevel) << "        }" << endl ;

    cout << indentWithIndentLevel(indentLevel) << "}" << endl ;
}
