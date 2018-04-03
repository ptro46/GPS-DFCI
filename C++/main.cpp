//
//  main.cpp
//  DFCI-Lib-CPP
//
//  Created by Patrice Trognon on 28/10/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#include <iostream>
using namespace std;

#include "Carre100Km.hpp"
#include "Carre20Km.hpp"
#include "Carre2Km.hpp"
#include "LatLng.hpp"


int main(int argc, const char * argv[]) {

    double lat=44.671123;
    double lng=1.277227;

    LatLng latLng(lat,lng);
    string dfci = latLng ;
    
    printf("lat(%f N) lng(%f E)\n\n",lat,lng);
    cout << "DFCI (" << dfci << ")" << endl ;
    
    Carre2Km carre2Km(dfci, nullptr);
    Carre20Km carre20Km(dfci, nullptr);
    Carre100Km carre100Km(dfci);
    
    
    carre20Km.performDetails();
    carre100Km.performDetails();
    
    carre2Km.dumpWithIndentLevel(0);
    carre20Km.dumpWithIndentLevel(0);
    carre100Km.dumpWithIndentLevel(0);
    
    return 0;
}
