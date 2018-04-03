//
//  ZoneChasseSecteur4.hpp
//  DFCI-Lib-CPP
//
//  Created by Patrice Trognon on 28/10/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#ifndef ZoneChasseSecteur4_hpp
#define ZoneChasseSecteur4_hpp

#include <iostream>
#include "CarreDFCI.hpp"

class Coord;
class Carre2Km ;
class LambertII;

class ZoneChasseSecteur4 : public CarreDFCI {
private:
    int             numeroZone;
    
    Coord       *   piCoordSO;
    Coord       *   piCoordNO;
    Coord       *   piCoordNEIntermediaire1;
    Coord       *   piCoordNEIntermediaire2;
    Coord       *   piCoordNEIntermediaire3;
    Coord       *   piCoordNE;
    Coord       *   piCoordSE;
    Coord       *   piCoordCentre;
    
    Carre2Km    *   poCarre2Km;
    
    friend class Carre2Km;

public:
    ZoneChasseSecteur4(int numeroZone, Carre2Km *poCarre2Km_, const LambertII& lambert);
    ~ZoneChasseSecteur4();

};

#endif /* ZoneChasseSecteur4_hpp */
