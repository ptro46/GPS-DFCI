//
//  ZoneChasseSecteur2.m
//  DFCI-ObjC
//
//  Created by Patrice Trognon on 19/09/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#import "ZoneChasseSecteur2.h"

#import "LambertII.h"
#import "Coord.h"

@implementation ZoneChasseSecteur2

-(instancetype)initWithNumeroZone:(int)numeroZone carre2Km:(Carre2Km*)carre2Km lambertOrigine:(LambertII*)lambert {
    self = [super init];
    if ( self ) {
        self.numeroZone = numeroZone ;
        self.carre2Km = carre2Km ;
        
        {
            LambertII *lambertIISO = [[LambertII alloc]initWithXLambert:lambert.x + 1000
                                                               YLambert:lambert.y + 1000];
            LatLng *latLngSO = [self latLngFromLambertII:lambertIISO];
            self.coordSO = [[Coord alloc]initWithLatLng:latLngSO lambertII:lambertIISO];
        }
        
        {
            LambertII *lambertIISE = [[LambertII alloc]initWithXLambert:lambert.x + 2000
                                                               YLambert:lambert.y + 1000];
            LatLng *latLngSE = [self latLngFromLambertII:lambertIISE];
            self.coordSE = [[Coord alloc]initWithLatLng:latLngSE lambertII:lambertIISE];
        }
        
        {
            LambertII *lambertIINE = [[LambertII alloc]initWithXLambert:lambert.x + 2000
                                                               YLambert:lambert.y + 2000];
            LatLng *latLngNE = [self latLngFromLambertII:lambertIINE];
            self.coordNE = [[Coord alloc]initWithLatLng:latLngNE lambertII:lambertIINE];
        }
        
        {
            LambertII *lambertIINO = [[LambertII alloc]initWithXLambert:lambert.x + 1000
                                                               YLambert:lambert.y + 2000 ];
            LatLng *latLngNO = [self latLngFromLambertII:lambertIINO];
            self.coordNO = [[Coord alloc]initWithLatLng:latLngNO lambertII:lambertIINO];
        }
        
        {
            LambertII *lambertIISOIntermediaire1 = [[LambertII alloc]initWithXLambert:lambert.x + 1500
                                                                             YLambert:lambert.y + 1000];
            LatLng *latLngSOIntermediaire1 = [self latLngFromLambertII:lambertIISOIntermediaire1];
            self.coordSOIntermediaire1 = [[Coord alloc]initWithLatLng:latLngSOIntermediaire1 lambertII:lambertIISOIntermediaire1];
        }
        
        {
            LambertII *lambertIISOIntermediaire2 = [[LambertII alloc]initWithXLambert:lambert.x + 1500
                                                                             YLambert:lambert.y + 1500];
            LatLng *latLngSOIntermediaire2 = [self latLngFromLambertII:lambertIISOIntermediaire2];
            self.coordSOIntermediaire2 = [[Coord alloc]initWithLatLng:latLngSOIntermediaire2 lambertII:lambertIISOIntermediaire2];
            
            self.coordCentre = [[Coord alloc]initWithLatLng:latLngSOIntermediaire2 lambertII:lambertIISOIntermediaire2];
        }
        
        {
            LambertII *lambertIISOIntermediaire3 = [[LambertII alloc]initWithXLambert:lambert.x + 1000
                                                                             YLambert:lambert.y + 1500];
            LatLng *latLngSOIntermediaire3 = [self latLngFromLambertII:lambertIISOIntermediaire3];
            self.coordSOIntermediaire3 = [[Coord alloc]initWithLatLng:latLngSOIntermediaire3 lambertII:lambertIISOIntermediaire3];
        }

    }
    return self;
}

@end
