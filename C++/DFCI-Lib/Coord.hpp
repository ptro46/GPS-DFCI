//
//  Coord.hpp
//  DFCI-Lib-CPP
//
//  Created by Patrice Trognon on 28/10/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#ifndef Coord_hpp
#define Coord_hpp

#include <iostream>

class LatLng;
class LambertII;

class Coord {
private:
    LatLng              *           piLatLng;
    LambertII           *           piLambertII;
    
    friend class CarreDFCI;
    
public:
    Coord(LatLng* pLatLng, LambertII* pLambertII);
    Coord(const Coord& rCoord);
    virtual ~Coord();

    Coord& operator=(const Coord& rCoord);

};

#endif /* Coord_hpp */
