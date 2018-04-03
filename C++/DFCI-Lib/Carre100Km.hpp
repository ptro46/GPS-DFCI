//
//  Carre100Km.hpp
//  DFCI-Lib-CPP
//
//  Created by Patrice Trognon on 28/10/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#ifndef Carre100Km_hpp
#define Carre100Km_hpp

#include <iostream>
#include <string>

using namespace std;

#include "CarreDFCI.hpp"

class Coord ;
class Carre20Km;

class Carre100Km : public CarreDFCI {
private:
    string          nomDFCIComplet;
    string          nomDFCICarre100Km;
    
    Coord       *   piCoordCentre;
    Coord       *   piCoordSO;
    Coord       *   piCoordNO;
    Coord       *   piCoordNE;
    Coord       *   piCoordSE;
    
    Carre20Km   *   matriceCarre20Km[5][5];
    
public:
    Carre100Km(string dfci);
    ~Carre100Km();
    
    void            performDetails();
    Carre20Km*      carre20Km(int x, int y);
    
    Carre100Km*     northCarre100Km();
    Carre100Km*     northEastCarre100Km();
    Carre100Km*     eastCarre100Km();
    Carre100Km*     southEastCarre100Km();
    Carre100Km*     southCarre100Km();
    Carre100Km*     southWestCarre100Km();
    Carre100Km*     westCarre100Km();
    Carre100Km*     northWestCarre100Km();
    
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
Carre100Km::northDFCIName() {
    return "TODO";
}

inline
string
Carre100Km::northEastDFCIName() {
    return "TODO";
}

inline
string
Carre100Km::eastDFCIName() {
    return "TODO";
}

inline
string
Carre100Km::southEastDFCIName() {
    return "TODO";
}

inline
string
Carre100Km::southDFCIName() {
    return "TODO";
}

inline
string
Carre100Km::westDFCIName() {
    return "TODO";
}

inline
string
Carre100Km::northWestDFCIName() {
    return "TODO";
}

#endif /* Carre100Km_hpp */
