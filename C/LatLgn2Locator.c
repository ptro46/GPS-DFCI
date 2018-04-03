//
//  LatLgn2Locator.c
//  GPS-DFCI
//
//  Created by Patrice Trognon on 08/08/2015.
//

#include "LatLgn2Locator.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

char*    latLng2Locator(double lat, double lng) {
    static char     locator[10];
    
    memset(locator, 0, sizeof(locator));
    
    lat += 90;          // lat origin of Maidenhead is 90S
    lng += 180;         // lng origin of Maidenhead is 180W
    double units=43200; // 18 fields * 10 squares * 24 subsquares * 10 extended square
    
    // get the extended sq
    double lat1 = floor(lat*units/180.0);
    double lng1 = floor(lng*units/360.0);
    
    // get the subsq.
    double lat2 = floor(lat1/10);
    double lng2 = floor(lng1/10);

    // get the sq.
    double lat3 = floor(lat2/24);
    double lng3 = floor(lng2/24);
    
    // get the fields
    double lat4 = floor(lat3/10);
    double lng4 = floor(lng3/10);

    sprintf(locator, "%c%c%c%c%c%c%c%c",
            (int)65+((int)lng4),(int)65+((int)lat4),
            48 + (((int)lng3) % 10), 48 + (((int)lat3) % 10),
            65 + (((int)lng2) % 24), 65 + (((int)lat2) % 24),
            48 + (((int)lng1) % 10), 48 + (((int)lat1) % 10)
            );
    
    return locator ;
}
