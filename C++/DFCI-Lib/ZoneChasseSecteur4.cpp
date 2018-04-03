//
//  ZoneChasseSecteur4.cpp
//  DFCI-Lib-CPP
//
//  Created by Patrice Trognon on 28/10/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#include "ZoneChasseSecteur4.hpp"

#include "Globals.h"

#include "Coord.hpp"
#include "Carre2Km.hpp"

#include "LambertII.hpp"
#include "LatLng.hpp"

#include <iostream>
using namespace std;

ZoneChasseSecteur4::ZoneChasseSecteur4(int numeroZone_, Carre2Km *poCarre2Km_, const LambertII& lambert) {
    numeroZone = numeroZone_ ;
    poCarre2Km = poCarre2Km_ ;
    
    {
        LambertII lambertIISO(lambert.x ,
                              lambert.y );
        LatLng latLngSO;
        latLngFromLambertII(lambertIISO, & latLngSO);
        piCoordSO = new Coord(&latLngSO, &lambertIISO);
    }
    
    {
        LambertII lambertIISE(lambert.x + 1000,
                              lambert.y );
        LatLng latLngSE;
        latLngFromLambertII(lambertIISE, & latLngSE);
        piCoordSE = new Coord(&latLngSE, &lambertIISE);
    }
    
    {
        LambertII lambertIINE(lambert.x + 1000,
                              lambert.y + 1000);
        LatLng latLngNE;
        latLngFromLambertII(lambertIINE, & latLngNE);
        piCoordNE = new Coord(&latLngNE, &lambertIINE);
    }
    
    {
        LambertII lambertIINO(lambert.x ,
                              lambert.y + 1000);
        LatLng latLngNO;
        latLngFromLambertII(lambertIINO, & latLngNO);
        piCoordNO = new Coord(&latLngNO, &lambertIINO);
    }
    
    {
        LambertII lambertIIIntermediaire1(lambert.x + 500,
                                          lambert.y + 1000);
        LatLng latLngIntermediaire1;
        latLngFromLambertII(lambertIIIntermediaire1, & latLngIntermediaire1);
        piCoordNEIntermediaire1 = new Coord(&latLngIntermediaire1, &lambertIIIntermediaire1);
    }
    
    {
        LambertII lambertIIIntermediaire2(lambert.x + 500,
                                          lambert.y + 500);
        LatLng latLngIntermediaire2;
        latLngFromLambertII(lambertIIIntermediaire2, & latLngIntermediaire2);
        piCoordNEIntermediaire2 = new Coord(&latLngIntermediaire2, &lambertIIIntermediaire2);
        
        piCoordCentre = new Coord(&latLngIntermediaire2, &lambertIIIntermediaire2);
    }
    
    {
        LambertII lambertIIIntermediaire3(lambert.x + 1000,
                                          lambert.y + 500);
        LatLng latLngIntermediaire3;
        latLngFromLambertII(lambertIIIntermediaire3, & latLngIntermediaire3);
        piCoordNEIntermediaire3 = new Coord(&latLngIntermediaire3, &lambertIIIntermediaire3);
    }
}

ZoneChasseSecteur4::~ZoneChasseSecteur4() {
    safeDeletePtr(piCoordSO)
    safeDeletePtr(piCoordSE)
    safeDeletePtr(piCoordNE)
    safeDeletePtr(piCoordNO)
    safeDeletePtr(piCoordNEIntermediaire1)
    safeDeletePtr(piCoordNEIntermediaire2)
    safeDeletePtr(piCoordNEIntermediaire3)
    safeDeletePtr(piCoordCentre)
}
