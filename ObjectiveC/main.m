//
//  main.m
//  DFCI-Lib-ObjC
//
//  Created by Patrice Trognon on 17/10/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "Globals.h"
#import "Carre100Km.h"
#import "Carre20Km.h"
#import "Carre2Km.h"
#import "LatLng.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        double lat=44.671123;
        double lng=1.277227;

        LatLng *latLng = [[LatLng alloc]initWithLatitude:lat longitude:lng];
        
        CustomLog(@"lat(%f N) lng(%f E)\n\n",lat,lng);
        CustomLog(@"DFCI (%@)\n",latLng.dfci);
        
        Carre2Km *carre2Km = [[Carre2Km alloc]initWithDFCI:latLng.dfci carre20Km:nil];
        Carre20Km *carre20Km = [[Carre20Km alloc]initWithDFCI:latLng.dfci carre100Km:nil];
        Carre100Km *carre100Km = [[Carre100Km alloc]initWithDFCI:latLng.dfci];
        
        
        [carre20Km performDetails];
        [carre100Km performDetails];
         
        
        [carre2Km dumpWithIndentLevel:0];
        [carre20Km dumpWithIndentLevel:0];
        [carre100Km dumpWithIndentLevel:0];
        
   }
    return 0;
}
