//
//  LambertII.hpp
//  DFCI-Lib-CPP
//
//  Created by Patrice Trognon on 28/10/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#ifndef LambertII_hpp
#define LambertII_hpp

#include <iostream>
#include "CarreDFCI.hpp"

class LambertII {
protected:
    double      x;
    double      y;
    
    friend class CarreDFCI;
    friend class LatLng;
    friend class Coord;
    friend class Carre100Km;
    friend class Carre20Km;
    friend class Carre2Km;
    
    friend class ZoneChasseSecteur1;
    friend class ZoneChasseSecteur2;
    friend class ZoneChasseSecteur3;
    friend class ZoneChasseSecteur4;
    friend class ZoneChasseSecteur5;

public:
    LambertII();
    LambertII(double x_, double y_);
};

#endif /* LambertII_hpp */
