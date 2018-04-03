//
//  LatLgn2Locator.h
//  GPS-DFCI
//
//  Created by Patrice Trognon on 08/08/2015.
//

#ifndef __GPS_DFCI__LatLgn2Locator__
#define __GPS_DFCI__LatLgn2Locator__

#include <stdio.h>

//---
// Lat & Lng to Maidenhead conversion
//
// input : lat and lng in decimal format
// output : locator (string)
// returns : Maidenhead locator like JN42iw08
// Conversion du code javascript écrit par Patrick EGLOFF (04/2009) http://www.egloff.eu
//---
char*    latLng2Locator(double lat, double lng) ;

#endif /* defined(__GPS_DFCI__LatLgn2Locator__) */
