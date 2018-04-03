//
//  ZoneChasseSecteur1.hpp
//  DFCI-Lib-CPP
//
//  Created by Patrice Trognon on 28/10/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#ifndef ZoneChasseSecteur1_hpp
#define ZoneChasseSecteur1_hpp

#include <iostream>
#include "CarreDFCI.hpp"

class Coord;
class Carre2Km ;
class LambertII;

class ZoneChasseSecteur1 : public CarreDFCI {
private:
    int             numeroZone;

    Coord       *   piCoordSO;
    Coord       *   piCoordNO;
    Coord       *   piCoordNE;
    Coord       *   piCoordSEIntermediaire1;
    Coord       *   piCoordSEIntermediaire2;
    Coord       *   piCoordSEIntermediaire3;
    Coord       *   piCoordSE;
    Coord       *   piCoordCentre;

    Carre2Km    *   poCarre2Km;
    
    friend class Carre2Km;
    
public:
    ZoneChasseSecteur1(int numeroZone, Carre2Km *poCarre2Km_, const LambertII& lambert);
    ~ZoneChasseSecteur1();
    
};

#endif /* ZoneChasseSecteur1_hpp */
