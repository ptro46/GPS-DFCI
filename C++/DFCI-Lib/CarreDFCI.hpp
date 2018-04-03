//
//  CarreDFCI.hpp
//  DFCI-Lib-CPP
//
//  Created by Patrice Trognon on 28/10/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#ifndef CarreDFCI_hpp
#define CarreDFCI_hpp

#include <iostream>
#include <string>

using namespace std;

class LatLng;
class LambertII;
class Coord;

class CarreDFCI {
public:
    CarreDFCI();
    virtual ~CarreDFCI();
    
protected:
    void    lambertIIFromLatitudeAndLongitude(double latitude, double longitude, LambertII *pOutLambertII);
    void    lambertIIFromDFCI(string dfci, LambertII *pOutLambertII);
    void    latLngFromLambertII(const LambertII& rLambertII, LatLng *pOutLatLng);
    
    string  indentWithIndentLevel(int indentLevel);
    void    dumpCoordWithPrompt(const Coord& rCoord, string prompt, int indentLevel);
    
private:
    double  lambLatNTFFromLambert(double xLambert, double yLambert, int typLamb);
    double  lambLonNTFFromLambert(double xLambert, double yLambert, int typLamb);
    double  ntfLatWGSFromLatLonNTF(double latitudeNTF, double longitudeNTF);
    double  ntfLonWGSFromLatLonNTF(double latitudeNTF, double longitudeNTF);
    double  isomLat(double latitIsom, double premExcEllips, double tolConverg);
    
};

#endif /* CarreDFCI_hpp */
