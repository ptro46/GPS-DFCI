//
//  ZoneChasseSecteur5.hpp
//  DFCI-Lib-CPP
//
//  Created by Patrice Trognon on 28/10/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#ifndef ZoneChasseSecteur5_hpp
#define ZoneChasseSecteur5_hpp

#include <iostream>
#include "CarreDFCI.hpp"

class Coord;
class Carre2Km ;
class LambertII;

class ZoneChasseSecteur5 : public CarreDFCI {
private:
    int             numeroZone;
    
    Coord       *   piCoordSO;
    Coord       *   piCoordNO;
    Coord       *   piCoordNE;
    Coord       *   piCoordSE;
    Coord       *   piCoordCentre;
    
    Carre2Km    *   poCarre2Km;
    
    friend class Carre2Km;

public:
    ZoneChasseSecteur5(int numeroZone, Carre2Km *poCarre2Km_, const LambertII& lambert);
    ~ZoneChasseSecteur5();

};

#endif /* ZoneChasseSecteur5_hpp */
