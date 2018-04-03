//
//  LatLng84DMS.c
//  GPS-DFCI
//
//  Created by Patrice Trognon on 08/08/2015.
//

#include "LatLng84DMS.h"

#include <math.h>
#include <string.h>
#include "FloatFormater.h"

sLatLng84DMS  latLng284DMS(double lat, double lng) {
    sLatLng84DMS    latLng84DMS;
    
    // compute and format longitudes
    // lng >0 is E, lng <0 is W
    char lngDir='E';
    if (lng < 0) {
        lngDir = 'W';
        lng=-lng ;
    }
    
    // compute longitude in DMS
    // degrees
    double lngDeg = floor(lng);
    double lngMin = (lng - lngDeg) * 100;
    // min in DMS
    double lngMin2 = lngMin * 60 / 100;
    // seconds with 2 decimals
    double lngSec = (lngMin2 - floor(lngMin2)) * 60;
    
    // formats DMS longitude in 000:00'00" format
    // formats degrees to 000
    char bufLngDeg[4];
    sprintf(bufLngDeg, "%03d",(int)lngDeg);

    // formats mins to 00
    lngMin=floor(lngMin2);
    char bufLngMin[3];
    sprintf(bufLngMin, "%02d",(int)lngMin);
    
    // formats seconds to 01.00
    char bufLngSec[6];
    strcpy(bufLngSec,formatDouble(lngSec, 2, 2));
    
    
    char latDir='N';
    if (lat < 0) {
        latDir = 'S';
        lat=-lat;
    }
    // compute latitude in DMS
    // degrees
    double latDeg = floor(lat);
    // mins
    double latMin = (lat - latDeg) * 100;
    double latMin2 = latMin * 60 / 100;

    double latSec = (latMin2 - floor(latMin2)) * 60;
    
    // formats DMS latitude in 00:00'00.00" format
    // degrees 00 format
    char bufLatDeg[4];
    sprintf(bufLatDeg, "%02d",(int)latDeg);

    
    // mins 00 format
    latMin=floor(latMin2);
    char bufLatMin[3];
    sprintf(bufLatMin, "%02d",(int)latMin);

    // secs 00.00 format
    char bufLatSec[6];
    strcpy(bufLatSec,formatDouble(latSec, 2, 2));

    double latDec= round(lat * 1000000) / 1000000;
    char bufLatDec[10];
    strcpy(bufLatDec,formatDouble(latDec, 2, 6));
    
    double lngDec= round(lng * 1000000) / 1000000;
    char bufLngDec[10];
    strcpy(bufLngDec,formatDouble(lngDec, 2, 6));
    
    sprintf(latLng84DMS.latDecimal, "%s %c",bufLatDec, latDir);
    sprintf(latLng84DMS.lngDecimal, "%s %c",bufLngDec, lngDir);
    sprintf(latLng84DMS.latDMS, "%s:%s'%s''%c",bufLatDeg, bufLatMin, bufLatSec, latDir);
    sprintf(latLng84DMS.lngDMS, "%s:%s'%s''%c",bufLngDeg, bufLngMin, bufLngSec, lngDir);
    
    
    return latLng84DMS;
}
