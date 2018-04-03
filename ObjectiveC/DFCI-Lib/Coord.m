//
//  Coord.m
//  DFCI-ObjC
//
//  Created by Patrice Trognon on 19/09/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#import "Coord.h"

#import "LatLng.h"
#import "LambertII.h"

@implementation Coord

-(instancetype)initWithLatLng:(LatLng*)latLng lambertII:(LambertII*)lambertII {
    self = [super init];
    if ( self ) {
        self.latLng = latLng ;
        self.lambertII = lambertII ;
    }
    return self ;
}

-(instancetype)initWithLatitude:(double)latitude longitude:(double)longitude XLambert:(double)x YLambert:(double)y {
    self = [super init];
    if ( self ) {
        self.latLng = [[LatLng alloc]initWithLatitude:latitude longitude:longitude];
        self.lambertII = [[LambertII alloc]initWithXLambert:x YLambert:y];
    }
    return self ;
}

-(instancetype)initLatLngFromXLambert:(double)x YLambert:(double)y {
    self = [super init];
    if ( self ) {
        self.lambertII = [[LambertII alloc]initWithXLambert:x YLambert:y];
    }
    return self ;
}

-(instancetype)initLambertFromLatitude:(double)latitude longitude:(double)longitude {
    self = [super init];
    if ( self ) {
        self.latLng = [[LatLng alloc]initWithLatitude:latitude longitude:longitude];
    }
    return self ;
}

@end
