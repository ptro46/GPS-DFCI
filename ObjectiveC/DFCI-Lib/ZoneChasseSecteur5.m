//
//  ZoneChasseSecteur5.m
//  DFCI-ObjC
//
//  Created by Patrice Trognon on 19/09/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#import "ZoneChasseSecteur5.h"

#import "LambertII.h"
#import "Coord.h"

@implementation ZoneChasseSecteur5

-(instancetype)initWithNumeroZone:(int)numeroZone carre2Km:(Carre2Km*)carre2Km lambertOrigine:(LambertII*)lambert {
    self = [super init];
    if ( self ) {
        self.numeroZone = numeroZone ;
        self.carre2Km = carre2Km ;
        
        {
            LambertII *lambertIISO = [[LambertII alloc]initWithXLambert:lambert.x + 500
                                                               YLambert:lambert.y + 500];
            LatLng *latLngSO = [self latLngFromLambertII:lambertIISO];
            self.coordSO = [[Coord alloc]initWithLatLng:latLngSO lambertII:lambertIISO];
        }
        
        {
            LambertII *lambertIISE = [[LambertII alloc]initWithXLambert:lambert.x + 1500
                                                               YLambert:lambert.y + 500];
            LatLng *latLngSE = [self latLngFromLambertII:lambertIISE];
            self.coordSE = [[Coord alloc]initWithLatLng:latLngSE lambertII:lambertIISE];
        }
        
        {
            LambertII *lambertIINE = [[LambertII alloc]initWithXLambert:lambert.x + 1500
                                                               YLambert:lambert.y + 1500];
            LatLng *latLngNE = [self latLngFromLambertII:lambertIINE];
            self.coordNE = [[Coord alloc]initWithLatLng:latLngNE lambertII:lambertIINE];
        }
        
        {
            LambertII *lambertIINO = [[LambertII alloc]initWithXLambert:lambert.x + 500
                                                               YLambert:lambert.y + 1500 ];
            LatLng *latLngNO = [self latLngFromLambertII:lambertIINO];
            self.coordNO = [[Coord alloc]initWithLatLng:latLngNO lambertII:lambertIINO];
        }
        
        
        {
            LambertII *lambertIICentre = [[LambertII alloc]initWithXLambert:lambert.x + 1000
                                                                   YLambert:lambert.y + 1000];
            LatLng *latLngCentre = [self latLngFromLambertII:lambertIICentre];
            
            self.coordCentre = [[Coord alloc]initWithLatLng:latLngCentre lambertII:lambertIICentre];
        }
        

    }
    return self;
}

@end
