//
//  ZoneChasseSecteur3.cpp
//  DFCI-Lib-CPP
//
//  Created by Patrice Trognon on 28/10/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#include "ZoneChasseSecteur3.hpp"

#include "Globals.h"

#include "Coord.hpp"
#include "Carre2Km.hpp"

#include "LambertII.hpp"
#include "LatLng.hpp"

#include <iostream>
using namespace std;

ZoneChasseSecteur3::ZoneChasseSecteur3(int numeroZone_, Carre2Km *poCarre2Km_, const LambertII& lambert) {
    numeroZone = numeroZone_ ;
    poCarre2Km = poCarre2Km_ ;
    
    {
        LambertII lambertIISO(lambert.x + 1000,
                              lambert.y );
        LatLng latLngSO;
        latLngFromLambertII(lambertIISO, & latLngSO);
        piCoordSO = new Coord(&latLngSO, &lambertIISO);
    }
    
    {
        LambertII lambertIISE(lambert.x + 2000,
                              lambert.y );
        LatLng latLngSE;
        latLngFromLambertII(lambertIISE, & latLngSE);
        piCoordSE = new Coord(&latLngSE, &lambertIISE);
    }
    
    {
        LambertII lambertIINE(lambert.x + 2000,
                              lambert.y + 1000);
        LatLng latLngNE;
        latLngFromLambertII(lambertIINE, & latLngNE);
        piCoordNE = new Coord(&latLngNE, &lambertIINE);
    }
    
    {
        LambertII lambertIINO(lambert.x + 1000,
                              lambert.y + 1000);
        LatLng latLngNO;
        latLngFromLambertII(lambertIINO, & latLngNO);
        piCoordNO = new Coord(&latLngNO, &lambertIINO);
    }
    
    {
        LambertII lambertIIIntermediaire1(lambert.x + 1000,
                                          lambert.y + 500);
        LatLng latLngIntermediaire1;
        latLngFromLambertII(lambertIIIntermediaire1, & latLngIntermediaire1);
        piCoordNOIntermediaire1 = new Coord(&latLngIntermediaire1, &lambertIIIntermediaire1);
    }
    
    {
        LambertII lambertIIIntermediaire2(lambert.x + 1500,
                                          lambert.y + 500);
        LatLng latLngIntermediaire2;
        latLngFromLambertII(lambertIIIntermediaire2, & latLngIntermediaire2);
        piCoordNOIntermediaire2 = new Coord(&latLngIntermediaire2, &lambertIIIntermediaire2);
        
        piCoordCentre = new Coord(&latLngIntermediaire2, &lambertIIIntermediaire2);
    }
    
    {
        LambertII lambertIIIntermediaire3(lambert.x + 1500,
                                          lambert.y + 1000);
        LatLng latLngIntermediaire3;
        latLngFromLambertII(lambertIIIntermediaire3, & latLngIntermediaire3);
        piCoordNOIntermediaire3 = new Coord(&latLngIntermediaire3, &lambertIIIntermediaire3);
    }

}

ZoneChasseSecteur3::~ZoneChasseSecteur3() {
    safeDeletePtr(piCoordSO)
    safeDeletePtr(piCoordSE)
    safeDeletePtr(piCoordNE)
    safeDeletePtr(piCoordNO)
    safeDeletePtr(piCoordNOIntermediaire1)
    safeDeletePtr(piCoordNOIntermediaire2)
    safeDeletePtr(piCoordNOIntermediaire3)
    safeDeletePtr(piCoordCentre)
}
