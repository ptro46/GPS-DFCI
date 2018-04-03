//
//  Carre20Km.hpp
//  DFCI-Lib-CPP
//
//  Created by Patrice Trognon on 28/10/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#ifndef Carre20Km_hpp
#define Carre20Km_hpp

#include <iostream>
#include <string>

using namespace std;

class Coord ;
class Carre2Km;
class Carre100Km;

#include "CarreDFCI.hpp"

class Carre20Km : public CarreDFCI {
private:
    string          nomDFCIComplet;
    string          nomDFCICarre20Km;
    Coord       *   piCoordCentre;
    Coord       *   piCoordSO;
    Coord       *   piCoordNO;
    Coord       *   piCoordNE;
    Coord       *   piCoordSE;
    
    Carre2Km    *   matriceCarre2Km[10][10];
    
    Carre100Km  *   poCarre100Km;
    
public:
    Carre20Km(string dfci, Carre100Km *poCarre100Km_);
    ~Carre20Km();
    
    void            performDetails();
    Carre2Km*       carre2Km(int x, int y);
    
    Carre20Km*      northCarre20Km();
    Carre20Km*      northEastCarre20Km();
    Carre20Km*      eastCarre20Km();
    Carre20Km*      southEastCarre20Km();
    Carre20Km*      southCarre20Km();
    Carre20Km*      southWestCarre20Km();
    Carre20Km*      westCarre20Km();
    Carre20Km*      northWestCarre20Km();

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
Carre20Km::northDFCIName() {
    return "TODO";
}

inline
string
Carre20Km::northEastDFCIName() {
    return "TODO";
}

inline
string
Carre20Km::eastDFCIName() {
    return "TODO";
}

inline
string
Carre20Km::southEastDFCIName() {
    return "TODO";
}

inline
string
Carre20Km::southDFCIName() {
    return "TODO";
}

inline
string
Carre20Km::westDFCIName() {
    return "TODO";
}

inline
string
Carre20Km::northWestDFCIName() {
    return "TODO";
}

#endif /* Carre20Km_hpp */
