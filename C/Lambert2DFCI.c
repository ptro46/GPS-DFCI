//
//  Lambert2DFCI.c
//  GPS-DFCI
//
//  Created by Patrice Trognon on 07/08/2015.
//

#include "Lambert2DFCI.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

char*    lambert2DFCI(double x, double y) {
    static char     dfci[10];
    int             index = 0 ;
    char*           ABC = "ABCDEFGHKLMN012345678902468";
    
    memset(dfci, 0, sizeof(dfci));
    
    x = round(x);
    y = round(y);
    
    // on limite le carroyage à la France
    // 0-1200 km de l'Ouest à Est et 1600-2700km du N au S
    if (x<=0 || x>=1200000 || y<=1600000 || y>=2700000) {
        return dfci ;
        
    } else {
        // on ramène l'origine au sud de la Corse à zero
        y -= 1600000;
        
        // carré 100*100 km
        double X100 = floor(x/100000);
        double Y100 = floor(y/100000);
        
        dfci[index++] = ABC[(int)X100];
        dfci[index++] = ABC[((int)Y100)+1];

        // carré 20*20 km
        double Xtot =  x-(X100*100000);
        double Ytot =  y-(Y100*100000);
        double X20 = floor(Xtot/20000);
        double Y20 = floor(Ytot/20000);
        
        dfci[index++] = ABC[((int)X20)+22];
        dfci[index++] = ABC[((int)Y20)+22];
        
        // carré 2*2 km
        Xtot -= (X20*20000);
        Ytot -= (Y20*20000);
        double X2 = floor(Xtot/2000);
        double Y2 = floor(Ytot/2000);
        
        dfci[index++] = ABC[((int)X2)+0];
        dfci[index++] = ABC[((int)Y2)+12];

        // découpage "chasse" en 5 zones
        Xtot -= (X2*2000);
        Ytot -= (Y2*2000);
        
        char Xc;
        if (Xtot>500 && Xtot<1500 && Ytot>500 && Ytot<1500) {
            Xc='5';
        } else if (Xtot<1000 && Ytot>1000) {
            Xc='1';
        } else if (Xtot<1000 && Ytot<1000) {
            Xc='4';
        } else if (Xtot>1000 && Ytot>1000) {
            Xc='2';
        } else if (Xtot>1000 &&  Ytot<1000) {
            Xc='3';
        }
        
        dfci[index++] = '.';
        dfci[index++] = Xc;
    }
    
    return dfci ;
}
