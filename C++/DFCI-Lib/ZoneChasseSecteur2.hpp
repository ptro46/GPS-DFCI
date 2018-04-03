//
//  ZoneChasseSecteur2.hpp
//  DFCI-Lib-CPP
//
//  Created by Patrice Trognon on 28/10/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#ifndef ZoneChasseSecteur2_hpp
#define ZoneChasseSecteur2_hpp

#include <iostream>
#include "CarreDFCI.hpp"

class Coord;
class Carre2Km ;
class LambertII;

class ZoneChasseSecteur2 : public CarreDFCI {
private:
    int             numeroZone;
    
    Coord       *   piCoordSO;
    Coord       *   piCoordSOIntermediaire1;
    Coord       *   piCoordSOIntermediaire2;
    Coord       *   piCoordSOIntermediaire3;
    Coord       *   piCoordNO;
    Coord       *   piCoordNE;
    Coord       *   piCoordSE;
    Coord       *   piCoordCentre;
    
    Carre2Km    *   poCarre2Km;
    
    friend class Carre2Km;

public:
    ZoneChasseSecteur2(int numeroZone, Carre2Km *poCarre2Km_, const LambertII& lambert);
    ~ZoneChasseSecteur2();
 
};

#endif /* ZoneChasseSecteur2_hpp */
