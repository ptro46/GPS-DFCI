//
//  Carre2Km.hpp
//  DFCI-Lib-CPP
//
//  Created by Patrice Trognon on 28/10/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#ifndef Carre2Km_hpp
#define Carre2Km_hpp

#include <iostream>
#include <string>

using namespace std;

#include "CarreDFCI.hpp"

class Coord ;
class ZoneChasseSecteur1;
class ZoneChasseSecteur2;
class ZoneChasseSecteur3;
class ZoneChasseSecteur4;
class ZoneChasseSecteur5;

class Carre20Km;

class Carre2Km : public CarreDFCI {
private:
    string          nomDFCIComplet;
    string          nomDFCICarre2Km;
    Coord       *   piCoordCentre;
    Coord       *   piCoordSO;
    Coord       *   piCoordNO;
    Coord       *   piCoordNE;
    Coord       *   piCoordSE;
    
    ZoneChasseSecteur1      *   piSecteur1;
    ZoneChasseSecteur2      *   piSecteur2;
    ZoneChasseSecteur3      *   piSecteur3;
    ZoneChasseSecteur4      *   piSecteur4;
    ZoneChasseSecteur5      *   piSecteur5;
    
    Carre20Km               *   poCarre20Km;
    
public:
    Carre2Km(string dfci, Carre20Km* poCarre20Km_);
    ~Carre2Km();
    
    Carre2Km*       northCarre2Km();
    Carre2Km*       northEastCarre2Km();
    Carre2Km*       eastCarre2Km();
    Carre2Km*       southEastCarre2Km();
    Carre2Km*       southCarre2Km();
    Carre2Km*       southWestCarre2Km();
    Carre2Km*       westCarre2Km();
    Carre2Km*       northWestCarre2Km();

    void            dumpWithIndentLevel(int indentLevel);
    
private:
    string          northDFCIName();
    string          northEastDFCIName();
    string          eastDFCIName();
    string          southEastDFCIName();
    string          southDFCIName();
    string          southWestDFCIName();
    string          westDFCIName();
    string          northWestDFCIName();

};

inline
string
Carre2Km::northDFCIName() {
    return "TODO";
}

inline
string
Carre2Km::northEastDFCIName() {
    return "TODO";
}

inline
string
Carre2Km::eastDFCIName() {
    return "TODO";
}

inline
string
Carre2Km::southEastDFCIName() {
    return "TODO";
}

inline
string
Carre2Km::southDFCIName() {
    return "TODO";
}

inline
string
Carre2Km::westDFCIName() {
    return "TODO";
}

inline
string
Carre2Km::northWestDFCIName() {
    return "TODO";
}

#endif /* Carre2Km_hpp */
