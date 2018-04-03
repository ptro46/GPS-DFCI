//
//  ZoneChasseSecteur3.hpp
//  DFCI-Lib-CPP
//
//  Created by Patrice Trognon on 28/10/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#ifndef ZoneChasseSecteur3_hpp
#define ZoneChasseSecteur3_hpp

#include <iostream>
#include "CarreDFCI.hpp"

class Coord;
class Carre2Km ;
class LambertII;

class ZoneChasseSecteur3 : public CarreDFCI {
private:
    int             numeroZone;
    
    Coord       *   piCoordSO;
    Coord       *   piCoordNOIntermediaire1;
    Coord       *   piCoordNOIntermediaire2;
    Coord       *   piCoordNOIntermediaire3;
    Coord       *   piCoordNO;
    Coord       *   piCoordNE;
    Coord       *   piCoordSE;
    Coord       *   piCoordCentre;
    
    Carre2Km    *   poCarre2Km;
    
    friend class Carre2Km;

public:
    ZoneChasseSecteur3(int numeroZone, Carre2Km *poCarre2Km_, const LambertII& lambert);
    ~ZoneChasseSecteur3();

};

#endif /* ZoneChasseSecteur3_hpp */
