//
//  ZoneChasseSecteur3.m
//  DFCI-ObjC
//
//  Created by Patrice Trognon on 19/09/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#import "ZoneChasseSecteur3.h"

#import "LambertII.h"
#import "Coord.h"

@implementation ZoneChasseSecteur3

-(instancetype)initWithNumeroZone:(int)numeroZone carre2Km:(Carre2Km*)carre2Km lambertOrigine:(LambertII*)lambert {
    self = [super init];
    if ( self ) {
        self.numeroZone = numeroZone ;
        self.carre2Km = carre2Km ;
        
        {
            LambertII *lambertIISO = [[LambertII alloc]initWithXLambert:lambert.x + 1000
                                                               YLambert:lambert.y ];
            LatLng *latLngSO = [self latLngFromLambertII:lambertIISO];
            self.coordSO = [[Coord alloc]initWithLatLng:latLngSO lambertII:lambertIISO];
        }
        
        {
            LambertII *lambertIISE = [[LambertII alloc]initWithXLambert:lambert.x + 2000
                                                               YLambert:lambert.y ];
            LatLng *latLngSE = [self latLngFromLambertII:lambertIISE];
            self.coordSE = [[Coord alloc]initWithLatLng:latLngSE lambertII:lambertIISE];
        }
        
        {
            LambertII *lambertIINE = [[LambertII alloc]initWithXLambert:lambert.x + 2000
                                                               YLambert:lambert.y + 1000];
            LatLng *latLngNE = [self latLngFromLambertII:lambertIINE];
            self.coordNE = [[Coord alloc]initWithLatLng:latLngNE lambertII:lambertIINE];
        }
        
        {
            LambertII *lambertIINO = [[LambertII alloc]initWithXLambert:lambert.x + 1000
                                                               YLambert:lambert.y + 1000 ];
            LatLng *latLngNO = [self latLngFromLambertII:lambertIINO];
            self.coordNO = [[Coord alloc]initWithLatLng:latLngNO lambertII:lambertIINO];
        }
        
        {
            LambertII *lambertIINOIntermediaire1 = [[LambertII alloc]initWithXLambert:lambert.x + 1000
                                                                             YLambert:lambert.y + 500];
            LatLng *latLngNOIntermediaire1 = [self latLngFromLambertII:lambertIINOIntermediaire1];
            self.coordNOIntermediaire1 = [[Coord alloc]initWithLatLng:latLngNOIntermediaire1 lambertII:lambertIINOIntermediaire1];
        }
        
        {
            LambertII *lambertIINOIntermediaire2 = [[LambertII alloc]initWithXLambert:lambert.x + 1500
                                                                             YLambert:lambert.y + 500];
            LatLng *latLngNOIntermediaire2 = [self latLngFromLambertII:lambertIINOIntermediaire2];
            self.coordNOIntermediaire2 = [[Coord alloc]initWithLatLng:latLngNOIntermediaire2 lambertII:lambertIINOIntermediaire2];
            
            self.coordCentre = [[Coord alloc]initWithLatLng:latLngNOIntermediaire2 lambertII:lambertIINOIntermediaire2];
        }
        
        {
            LambertII *lambertIINOIntermediaire3 = [[LambertII alloc]initWithXLambert:lambert.x + 1500
                                                                             YLambert:lambert.y + 1000];
            LatLng *latLngNOIntermediaire3 = [self latLngFromLambertII:lambertIINOIntermediaire3];
            self.coordNOIntermediaire3 = [[Coord alloc]initWithLatLng:latLngNOIntermediaire3 lambertII:lambertIINOIntermediaire3];
        }

    }
    return self;
}

@end
