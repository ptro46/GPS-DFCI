//
//  ZoneChasseSecteur4.m
//  DFCI-ObjC
//
//  Created by Patrice Trognon on 19/09/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#import "ZoneChasseSecteur4.h"

#import "LambertII.h"
#import "Coord.h"

@implementation ZoneChasseSecteur4

-(instancetype)initWithNumeroZone:(int)numeroZone carre2Km:(Carre2Km*)carre2Km lambertOrigine:(LambertII*)lambert {
    self = [super init];
    if ( self ) {
        self.numeroZone = numeroZone ;
        self.carre2Km = carre2Km ;
        
        {
            LambertII *lambertIISO = [[LambertII alloc]initWithXLambert:lambert.x
                                                               YLambert:lambert.y ];
            LatLng *latLngSO = [self latLngFromLambertII:lambertIISO];
            self.coordSO = [[Coord alloc]initWithLatLng:latLngSO lambertII:lambertIISO];
        }
        
        {
            LambertII *lambertIISE = [[LambertII alloc]initWithXLambert:lambert.x + 1000
                                                               YLambert:lambert.y ];
            LatLng *latLngSE = [self latLngFromLambertII:lambertIISE];
            self.coordSE = [[Coord alloc]initWithLatLng:latLngSE lambertII:lambertIISE];
        }
        
        {
            LambertII *lambertIINE = [[LambertII alloc]initWithXLambert:lambert.x + 1000
                                                               YLambert:lambert.y + 1000];
            LatLng *latLngNE = [self latLngFromLambertII:lambertIINE];
            self.coordNE = [[Coord alloc]initWithLatLng:latLngNE lambertII:lambertIINE];
        }
        
        {
            LambertII *lambertIINO = [[LambertII alloc]initWithXLambert:lambert.x
                                                               YLambert:lambert.y + 1000 ];
            LatLng *latLngNO = [self latLngFromLambertII:lambertIINO];
            self.coordNO = [[Coord alloc]initWithLatLng:latLngNO lambertII:lambertIINO];
        }
        
        {
            LambertII *lambertIINEIntermediaire1 = [[LambertII alloc]initWithXLambert:lambert.x + 500
                                                                             YLambert:lambert.y + 1000];
            LatLng *latLngNEIntermediaire1 = [self latLngFromLambertII:lambertIINEIntermediaire1];
            self.coordNEIntermediaire1 = [[Coord alloc]initWithLatLng:latLngNEIntermediaire1 lambertII:lambertIINEIntermediaire1];
        }
        
        {
            LambertII *lambertIINEIntermediaire2 = [[LambertII alloc]initWithXLambert:lambert.x + 500
                                                                             YLambert:lambert.y + 500];
            LatLng *latLngNEIntermediaire2 = [self latLngFromLambertII:lambertIINEIntermediaire2];
            self.coordNEIntermediaire2 = [[Coord alloc]initWithLatLng:latLngNEIntermediaire2 lambertII:lambertIINEIntermediaire2];
            
            self.coordCentre = [[Coord alloc]initWithLatLng:latLngNEIntermediaire2 lambertII:lambertIINEIntermediaire2];
        }
        
        {
            LambertII *lambertIINEIntermediaire3 = [[LambertII alloc]initWithXLambert:lambert.x + 1000
                                                                             YLambert:lambert.y + 500];
            LatLng *latLngNEIntermediaire3 = [self latLngFromLambertII:lambertIINEIntermediaire3];
            self.coordNEIntermediaire3 = [[Coord alloc]initWithLatLng:latLngNEIntermediaire3 lambertII:lambertIINEIntermediaire3];
        }

    }
    return self;
}

@end
