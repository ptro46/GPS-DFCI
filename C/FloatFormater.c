//
//  FloatFormater.c
//  GPS-DFCI
//
//  Created by Patrice Trognon on 08/08/2015.
//

#include "FloatFormater.h"

char* formatDouble(double value, int intPad, int floatPad) {
    static char buf[20];
    
    char bufIntFormat[20];
    char bufInt[20];
    
    bufIntFormat[0]='%';
    sprintf(bufIntFormat+1, "0%dd",intPad);
    sprintf(bufInt, bufIntFormat,(int)value);
    
    double vWithoutInt = value - ((int)value) ;
    char bufFloat[20];
    char bufFloatFormat[20];
    
    bufFloatFormat[0]='%';
    sprintf(bufFloatFormat+1, ".%df",floatPad);
    sprintf(bufFloat, bufFloatFormat,vWithoutInt);
    
    sprintf(buf, "%s%s",bufInt,bufFloat+1);
    
    return buf;
}