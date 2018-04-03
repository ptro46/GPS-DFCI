//
//  LatLng.h
//  DFCI-ObjC
//
//  Created by Patrice Trognon on 19/09/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LambertII;

@interface LatLng : NSObject

@property(nonatomic)    double      latitude;
@property(nonatomic)    double      longitude;

-(instancetype)initWithLatitude:(double)latitude longitude:(double)longitude;

@property(nonatomic,readonly)   LambertII   *       lambertII ;
@property(nonatomic,readonly)   NSString    *       dfci;


@end
