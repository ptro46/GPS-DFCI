//
//  Coord.h
//  DFCI-ObjC
//
//  Created by Patrice Trognon on 19/09/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LatLng ;
@class LambertII;

@interface Coord : NSObject

@property(nonatomic,strong)     LatLng      *       latLng;
@property(nonatomic,strong)     LambertII   *       lambertII;

-(instancetype)initWithLatLng:(LatLng*)latLng lambertII:(LambertII*)lambertII;
-(instancetype)initWithLatitude:(double)latitude longitude:(double)longitude XLambert:(double)x YLambert:(double)y;
-(instancetype)initLatLngFromXLambert:(double)x YLambert:(double)y;
-(instancetype)initLambertFromLatitude:(double)latitude longitude:(double)longitude;

@end
