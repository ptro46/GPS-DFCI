//
//  ZoneChasseSecteur1.m
//  DFCI-ObjC
//
//  Created by Patrice Trognon on 19/09/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#import "ZoneChasseSecteur1.h"

#import "LambertII.h"
#import "Coord.h"

@implementation ZoneChasseSecteur1

-(instancetype)initWithNumeroZone:(int)numeroZone carre2Km:(Carre2Km*)carre2Km lambertOrigine:(LambertII*)lambert {
    self = [super init];
    if ( self ) {
        self.numeroZone = numeroZone ;
        self.carre2Km = carre2Km ;

        {
            LambertII *lambertIISO = [[LambertII alloc]initWithXLambert:lambert.x
                                                               YLambert:lambert.y + 1000];
            LatLng *latLngSO = [self latLngFromLambertII:lambertIISO];
            self.coordSO = [[Coord alloc]initWithLatLng:latLngSO lambertII:lambertIISO];
        }

        {
            LambertII *lambertIISE = [[LambertII alloc]initWithXLambert:lambert.x + 1000
                                                               YLambert:lambert.y + 1000];
            LatLng *latLngSE = [self latLngFromLambertII:lambertIISE];
            self.coordSE = [[Coord alloc]initWithLatLng:latLngSE lambertII:lambertIISE];
        }
        
        {
            LambertII *lambertIINE = [[LambertII alloc]initWithXLambert:lambert.x + 1000
                                                               YLambert:lambert.y + 2000];
            LatLng *latLngNE = [self latLngFromLambertII:lambertIINE];
            self.coordNE = [[Coord alloc]initWithLatLng:latLngNE lambertII:lambertIINE];
        }
        
        {
            LambertII *lambertIINO = [[LambertII alloc]initWithXLambert:lambert.x
                                                               YLambert:lambert.y + 2000 ];
            LatLng *latLngNO = [self latLngFromLambertII:lambertIINO];
            self.coordNO = [[Coord alloc]initWithLatLng:latLngNO lambertII:lambertIINO];
        }
        
        {
            LambertII *lambertIISEIntermediaire1 = [[LambertII alloc]initWithXLambert:lambert.x + 1000
                                                                             YLambert:lambert.y + 1500];
            LatLng *latLngSEIntermediaire1 = [self latLngFromLambertII:lambertIISEIntermediaire1];
            self.coordSEIntermediaire1 = [[Coord alloc]initWithLatLng:latLngSEIntermediaire1 lambertII:lambertIISEIntermediaire1];
        }

        {
            LambertII *lambertIISEIntermediaire2 = [[LambertII alloc]initWithXLambert:lambert.x + 500
                                                                             YLambert:lambert.y + 1500];
            LatLng *latLngSEIntermediaire2 = [self latLngFromLambertII:lambertIISEIntermediaire2];
            self.coordSEIntermediaire2 = [[Coord alloc]initWithLatLng:latLngSEIntermediaire2 lambertII:lambertIISEIntermediaire2];
            
            self.coordCentre = [[Coord alloc]initWithLatLng:latLngSEIntermediaire2 lambertII:lambertIISEIntermediaire2];
        }

        {
            LambertII *lambertIISEIntermediaire3 = [[LambertII alloc]initWithXLambert:lambert.x + 500
                                                                             YLambert:lambert.y + 1000];
            LatLng *latLngSEIntermediaire3 = [self latLngFromLambertII:lambertIISEIntermediaire3];
            self.coordSEIntermediaire3 = [[Coord alloc]initWithLatLng:latLngSEIntermediaire3 lambertII:lambertIISEIntermediaire3];
        }
    }
    return self;
}

@end
