//
//  Coord.cpp
//  DFCI-Lib-CPP
//
//  Created by Patrice Trognon on 28/10/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#include "Coord.hpp"

#include "Globals.h"

#include "LatLng.hpp"
#include "LambertII.hpp"

Coord::Coord(LatLng* pLatLng, LambertII* pLambertII) {
    piLatLng = new LatLng(pLatLng->latitude, pLatLng->longitude);
    piLambertII = new LambertII(pLambertII->x, pLambertII->y);
}

Coord::Coord(const Coord& rCoord) {
    piLambertII = new LambertII(*rCoord.piLambertII);
    piLatLng = new LatLng(*rCoord.piLatLng);
}

Coord::~Coord() {
    safeDeletePtr(piLambertII)
    safeDeletePtr(piLambertII)
}


Coord&
Coord::operator=(const Coord& rCoord) {

    if ( this != &rCoord ) {
        safeDeletePtr(piLambertII)
        piLambertII = new LambertII(*rCoord.piLambertII);
        
        safeDeletePtr(piLatLng)
        piLatLng = new LatLng(*rCoord.piLatLng);
    }
    
    return *this;
}
