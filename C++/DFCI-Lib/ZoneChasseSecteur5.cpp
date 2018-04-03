//
//  ZoneChasseSecteur5.cpp
//  DFCI-Lib-CPP
//
//  Created by Patrice Trognon on 28/10/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#include "ZoneChasseSecteur5.hpp"

#include "Globals.h"

#include "Coord.hpp"
#include "Carre2Km.hpp"

#include "LambertII.hpp"
#include "LatLng.hpp"

#include <iostream>
using namespace std;

ZoneChasseSecteur5::ZoneChasseSecteur5(int numeroZone_, Carre2Km *poCarre2Km_, const LambertII& lambert) {
    numeroZone = numeroZone_ ;
    poCarre2Km = poCarre2Km_ ;
    
    {
        LambertII lambertIISO(lambert.x + 500,
                              lambert.y + 500);
        LatLng latLngSO;
        latLngFromLambertII(lambertIISO, & latLngSO);
        piCoordSO = new Coord(&latLngSO, &lambertIISO);
    }
    
    {
        LambertII lambertIISE(lambert.x + 1500,
                              lambert.y + 500);
        LatLng latLngSE;
        latLngFromLambertII(lambertIISE, & latLngSE);
        piCoordSE = new Coord(&latLngSE, &lambertIISE);
    }
    
    {
        LambertII lambertIINE(lambert.x + 1500,
                              lambert.y + 1500);
        LatLng latLngNE;
        latLngFromLambertII(lambertIINE, & latLngNE);
        piCoordNE = new Coord(&latLngNE, &lambertIINE);
    }
    
    {
        LambertII lambertIINO(lambert.x + 500,
                              lambert.y + 1500);
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

}

ZoneChasseSecteur5::~ZoneChasseSecteur5() {
    safeDeletePtr(piCoordSO)
    safeDeletePtr(piCoordSE)
    safeDeletePtr(piCoordNE)
    safeDeletePtr(piCoordNO)
    safeDeletePtr(piCoordCentre)
}
