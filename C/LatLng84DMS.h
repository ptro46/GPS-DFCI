//
//  LatLng84DMS.h
//  GPS-DFCI
//
//  Created by Patrice Trognon on 08/08/2015.
//

#ifndef __GPS_DFCI__LatLng84DMS__
#define __GPS_DFCI__LatLng84DMS__

#include <stdio.h>

typedef struct sLatLng84DMS {
    char    latDecimal[12];
    char    lngDecimal[12];
    char    latDMS[16];
    char    lngDMS[18];
} sLatLng84DMS, *PsLatLng84DMS;

//---
// function to transform a Google map point to
// latitude and longitude in decimal and DMS format.
// input : (pointlat,point.lng)
// output: LatLng in array(4) format
// returns : 	sLatLng84DMS
// Conversion du code javascript écrit par Patrick EGLOFF (04/2009) http://www.egloff.eu
// feel free to use this script as long as you mention the origin
//---
sLatLng84DMS  latLng284DMS(double lat, double lng) ;

#endif /* defined(__GPS_DFCI__LatLng84DMS__) */
