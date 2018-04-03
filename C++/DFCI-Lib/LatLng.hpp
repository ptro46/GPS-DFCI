//
//  LatLng.hpp
//  DFCI-Lib-CPP
//
//  Created by Patrice Trognon on 28/10/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#ifndef LatLng_hpp
#define LatLng_hpp

#include <iostream>
#include "CarreDFCI.hpp"

class LambertII ;

class LatLng {
protected:
    double      latitude;
    double      longitude;
    
    friend class CarreDFCI;
    friend class Coord;
    
    LambertII   *   piCachedLambertII;
    string          cachedDFCI;
    
public:
    LatLng();
    LatLng(double lat, double lng);
    virtual ~LatLng();
    
    operator LambertII*() ;
    operator string() ;
};

#endif /* LatLng_hpp */
