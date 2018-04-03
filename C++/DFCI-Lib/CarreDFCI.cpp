//
//  CarreDFCI.cpp
//  DFCI-Lib-CPP
//
//  Created by Patrice Trognon on 28/10/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#include "CarreDFCI.hpp"

#include "LambertII.hpp"
#include "LatLng.hpp"
#include "Coord.hpp"

#include <sstream>
#include <cassert>

#include <string.h>
#include <math.h>

using namespace std;


int    InStr(char *myString, char searchChar,size_t maxLen) {
    int i=0;
    
    while ( (myString[i] != searchChar) && (i<maxLen) ) {
        i++;
    }
    return i;
}

CarreDFCI::CarreDFCI() {
    
}

CarreDFCI::~CarreDFCI() {
    
}

void
CarreDFCI::lambertIIFromLatitudeAndLongitude(double latitude, double longitude, LambertII *pOutLambertII) {
    LatLng latLng(latitude,longitude);
    LambertII *pLambertII = latLng ;
    
    pOutLambertII->x =  pLambertII->x ;
    pOutLambertII->y =  pLambertII->y ;
}

void
CarreDFCI::lambertIIFromDFCI(string sDfci, LambertII *pOutLambertII) {
    double XLamb, YLamb ;
    
    char dfci[9];
    strcpy(dfci, sDfci.c_str());
    
    // FE06H1.2
    char carre100[3] ;
    carre100[0] = dfci[0];
    carre100[1] = dfci[1];
    carre100[2] = 0 ;
    
    char carre20[3];
    carre20[0] = dfci[2];
    carre20[1] = dfci[3];
    carre20[2] = 0 ;
    
    char carre2[3];
    carre2[0] = dfci[4];
    carre2[1] = dfci[5];
    carre2[2] = 0 ;
    
    char zon5[3];
    zon5[0] = dfci[6];
    zon5[1] = dfci[7];
    zon5[2] = 0 ;
    
    YLamb=1500000 ;
    XLamb=0;
    
    char dfciLetters[] = "ABCDEFGHKLMN";
    
    int a;
    
    a = InStr(dfciLetters, carre100[0],strlen(dfciLetters));
    XLamb = XLamb + a*100000;
    a = InStr(dfciLetters, carre100[1],strlen(dfciLetters));
    YLamb = YLamb + a*100000;
    
    char a20[2];
    
    a20[0] = carre20[0];
    a20[1] = 0 ;
    a = atoi(a20)/2;
    XLamb = XLamb + a*20000;
    
    a20[0] = carre20[1];
    a20[1] = 0 ;
    a = atoi(a20)/2;
    YLamb = YLamb + a*20000;
    
    a = InStr(dfciLetters, carre2[0],strlen(dfciLetters));
    XLamb = XLamb + a*2000;
    
    a20[0] = carre2[1];
    a20[1] = 0 ;
    a = atoi(a20);
    YLamb = YLamb + a*2000;
    
    switch ( zon5[1] ) {
        case '1' : {
            //XLamb = XLamb+500;
            YLamb = YLamb+1000;
        } break ;
            
        case '2' : {
            XLamb = XLamb+1500;
            YLamb = YLamb+1500;
        } break ;
            
        case '3' : {
            XLamb = XLamb+1000;
            //YLamb = YLamb+500;
        } break ;
            
        case '4' : {
            //XLamb = XLamb+500;
            //YLamb = YLamb+500;
        } break ;
            
        default : {
            XLamb = XLamb+500;
            YLamb = YLamb+500;
        } break ;
    }

    assert(pOutLambertII != nullptr);
    pOutLambertII->x = XLamb ;
    pOutLambertII->y = YLamb ;
}

void
CarreDFCI::latLngFromLambertII(const LambertII& rLambertII, LatLng *pOutLatLng) {
    double latNTF = 0.0 ;
    double lonNTF = 0.0 ;
    
    double latitude ;
    double longitude ;
    
    latNTF = lambLatNTFFromLambert(rLambertII.x, rLambertII.y, 0);
    lonNTF = lambLonNTFFromLambert(rLambertII.x, rLambertII.y, 0);
    
    latitude = ntfLatWGSFromLatLonNTF(latNTF, lonNTF);
    longitude = ntfLonWGSFromLatLonNTF(latNTF, lonNTF);

    assert(pOutLatLng != nullptr);
    pOutLatLng->latitude = latitude ;
    pOutLatLng->longitude = longitude ;
}

string
CarreDFCI::indentWithIndentLevel(int indentLevel) {
    stringstream ss;
    
    for(int i=0; i<indentLevel; i++) {
        ss << "    ";
    }

    return ss.str();
}

void
CarreDFCI::dumpCoordWithPrompt(const Coord& rCoord, string prompt, int indentLevel) {
    cout << indentWithIndentLevel(indentLevel) << "Coordonnees " << prompt << " {" << endl ;
    cout << indentWithIndentLevel(indentLevel) << "    LambertII : {" << endl ;
//    cout << indentWithIndentLevel(indentLevel) << "        x:" << rCoord.piLambertII->x << endl ;
//    cout << indentWithIndentLevel(indentLevel) << "        y:" << rCoord.piLambertII->y << endl ;
    printf("%s        x:%f\n",indentWithIndentLevel(indentLevel).c_str(),rCoord.piLambertII->x);
    printf("%s        y:%f\n",indentWithIndentLevel(indentLevel).c_str(),rCoord.piLambertII->y);
    cout << indentWithIndentLevel(indentLevel) << "    }" << endl ;
    cout << indentWithIndentLevel(indentLevel) << "    GPS : {" << endl ;
//    cout << indentWithIndentLevel(indentLevel) << "        lat:" << rCoord.piLatLng->latitude << endl ;
//    cout << indentWithIndentLevel(indentLevel) << "        lng:" << rCoord.piLatLng->longitude << endl ;
    printf("%s        lat:%f\n",indentWithIndentLevel(indentLevel).c_str(),rCoord.piLatLng->latitude);
    printf("%s        lng:%f\n",indentWithIndentLevel(indentLevel).c_str(),rCoord.piLatLng->longitude);
    cout << indentWithIndentLevel(indentLevel) << "    }" << endl ;
    cout << indentWithIndentLevel(indentLevel) << "}" << endl ;
}

double
CarreDFCI::lambLatNTFFromLambert(double xLambert, double yLambert, int typLamb) {
    double Clarke1880;
    double e, R, L, n, c, Xs, Ys;
    
    //    double rad2Deg=180/M_PI;
    //    double deg2Rad=M_PI/180;
    
    Clarke1880=0.08248325676342;
    e=Clarke1880;
    
    //   Lambert II etendu par defaut
    switch ( typLamb ) {
        case 1: {
            n = 0.7604059656;
            c = 11603796.98;
            Xs = 600000;
            Ys = 5657616.674;
        } break ;
            
        case 2: {
            n = 0.7289686274;
            c = 11745793.39;
            Xs = 600000;
            Ys = 6199695.768;
            
        } break ;
            
        case 3: {
            n = 0.6959127966;
            c = 11947992.52;
            Xs = 600000;
            Ys = 6791905.085;
        } break ;
            
        case 4: {
            n = 0.6712679322;
            c = 12136281.99;
            Xs = 234.358;
            Ys = 7239161.542;
        } break ;
            
        default: {
            n = 0.7289686274;
            c = 11745793.39;
            Xs = 600000;
            Ys = 8199695.768;
        } break ;
            
    }
    
    R = sqrt((xLambert-Xs)*(xLambert-Xs) + (yLambert-Ys)*(yLambert-Ys));
    L = -1 / n * log(fabs(R/c));
    return isomLat(L, e, 0.00000000001);
}

double
CarreDFCI::lambLonNTFFromLambert(double xLambert, double yLambert, int typLamb) {
    double LX, R, g, n, c, Xs, Ys;
    
    double rad2Deg=180/M_PI;
    //    double deg2Rad=M_PI/180;
    
    //    double MeridParis = 2.33722916666667;
    
    //   Lambert II etendu par defaut
    switch ( typLamb ) {
        case 1: {
            n = 0.7604059656;
            c = 11603796.98;
            Xs = 600000;
            Ys = 5657616.674;
        } break ;
            
        case 2: {
            n = 0.7289686274;
            c = 11745793.39;
            Xs = 600000;
            Ys = 6199695.768;
            
        } break ;
            
        case 3: {
            n = 0.6959127966;
            c = 11947992.52;
            Xs = 600000;
            Ys = 6791905.085;
        } break ;
            
        case 4: {
            n = 0.6712679322;
            c = 12136281.99;
            Xs = 234.358;
            Ys = 7239161.542;
        } break ;
            
        default: {
            n = 0.7289686274;
            c = 11745793.39;
            Xs = 600000;
            Ys = 8199695.768;
        } break ;
            
    }
    
    R = sqrt((xLambert-Xs)*(xLambert-Xs) + (yLambert-Ys)*(yLambert-Ys));
    g = atan((xLambert-Xs) / (Ys-yLambert));
    LX= g / n;
    return LX*rad2Deg;
}

double
CarreDFCI::ntfLatWGSFromLatLonNTF(double latitudeNTF, double longitudeNTF) {
    double Phi, Lambda, h, AA, aNTF, aWGS, b, bNTF, bWGS, eNTF, eWGS, e2, v, X, Y, Z, p, r, f, u;
    double MeridParis;
    MeridParis=2.33722916666667;
    
    double rad2Deg=180/M_PI;
    double deg2Rad=M_PI/180;
    
    Phi = latitudeNTF*deg2Rad;
    Lambda = (longitudeNTF+MeridParis)*deg2Rad;
    h = 0;
    
    // aNTF = Demi Grand-Axe de l'ellipsoïde de Clarke 1880
    aNTF = 6378249.2;
    
    // bNTF = Demi Petit-Axe de l'ellipsoïde de Clarke 1880
    bNTF = 6356515 ;
    
    // eNTF = Premiere Excentricite de l'ellipsoïde de Clarke 1880
    eNTF = sqrt(1 - (bNTF / aNTF)*(bNTF / aNTF));
    
    // aWGS = Demi Grand-Axe de l'ellipsoïde WGS84
    aWGS = 6378137;
    
    // bWGS = Demi Petit-Axe de l'ellipsoïde WGS84
    bWGS = 6356752.314;
    
    // eWGS = Premiere Excentricite de l'ellipsoïde WGS84
    eWGS = sqrt(1 - (bWGS / aWGS)*(bWGS / aWGS));
    AA = aNTF;
    e2 = eNTF * eNTF;
    f = (AA - b) / AA;
    v = AA / sqrt(1 - e2 * sin(Phi) * sin(Phi));
    
    // Coordonnee Geocentriques NTF : X, Y, Z
    X = (v + h) * cos(Phi) * cos(Lambda);
    Y = (v + h) * cos(Phi) * sin(Lambda);
    Z = ((1 - e2) * v + h) * sin(Phi);
    
    // Changement de referentiel NGF vers WGS84
    X = X - 168;
    Y = Y - 60;
    Z = Z + 320;
    AA = aWGS;
    b = bWGS;
    e2 = eWGS * eWGS;
    f = (AA - b) / AA;
    p = sqrt(X * X + Y * Y);
    r = p + Z * Z;
    u = atan((Z / p) * ((1 - f) + (e2 * AA / r)));
    Phi = atan((Z * (1 - f) + e2 * AA * sin(u) * sin(u) * sin(u)) / ((1 - f) * (p - e2 * AA * cos(u) * cos(u) * cos(u))));
    
    return Phi*rad2Deg;
}

double
CarreDFCI::ntfLonWGSFromLatLonNTF(double latitudeNTF, double longitudeNTF) {
    // Calcul de la Longitude WGS84 à partir des coordonnees geographiques NTF en Degres decimaux
    // GLat, GLon en Degres decimaux
    
    double Phi, Lambda, h, AA, aNTF, b, bNTF, eNTF, e2, v, X, Y, Z, f;
    double MeridParis;
    MeridParis=2.33722916666667;
    
    double rad2Deg=180/M_PI;
    double deg2Rad=M_PI/180;
    
    // h = hauteur sur l'ellipsoïde - mis à zero
    Phi = latitudeNTF*deg2Rad;
    Lambda = (longitudeNTF+MeridParis)*deg2Rad;
    h = 0;
    
    // aNTF = Demi Grand-Axe de l'ellipsoïde de Clarke 1880
    aNTF = 6378249.2;
    
    // bNTF = Demi Petit-Axe de l'ellipsoïde de Clarke 1880
    bNTF = 6356515 ;
    
    // eNTF = Premiere Excentricite de l'ellipsoïde de Clarke 1880
    eNTF= sqrt(1 - (bNTF / aNTF)*(bNTF / aNTF));
    AA = aNTF;
    e2 = eNTF * eNTF;
    f = (AA - b) / AA;
    v = AA / sqrt(1 - e2 * sin(Phi) * sin(Phi));
    
    // Coordonnee Geocentriques NTF : X, Y, Z
    X = (v + h) * cos(Phi) * cos(Lambda);
    Y = (v + h) * cos(Phi) * sin(Lambda);
    Z = ((1 - e2) * v + h) * sin(Phi);
    
    // Changement de referentiel NTF vers WGS84
    X = X - 168;
    Y = Y - 60;
    Z = Z + 320;
    
    Lambda = atan(Y / X);
    if ( X < 0 ) {
        Lambda = Lambda + M_PI;
    }
    
    return Lambda*rad2Deg;
}

double
CarreDFCI::isomLat(double latitIsom, double premExcEllips, double tolConverg) {
    //    double clarke1880=0.08248325676342;
    //    double iagGrs80=0.08182297965731;
    
    double rad2Deg=180/M_PI;
    //    double deg2Rad=M_PI/180;
    
    double EL=exp(latitIsom);
    
    double rPremEx=premExcEllips;
    double rTolConv=tolConverg;
    
    double s0 = 0;
    double s1 = 2 * atan(EL)-M_PI/2;
    double d=0;
    
    while (fabs(s0 - s1) > rTolConv ) {
        s0 = s1;
        d = log(((1 + rPremEx * sin(s0)) / (1 - rPremEx * sin(s0))));
        d = exp(d*(rPremEx / 2));
        s1 = 2 * atan(d*EL)-M_PI/2;
    }
    
    return s1 * rad2Deg ;

}
