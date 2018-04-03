//
//  CarreDFCI.h
//  DFCI-Lib-ObjC
//
//  Created by Patrice Trognon on 17/10/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LatLng ;
@class LambertII ;
@class Coord;

@interface CarreDFCI : NSObject

-(LambertII*)lambertIIFromLatitude:(double)latitude longitude:(double)longitude;
-(LambertII*)lambertIIFromDFCI:(NSString*)dfci;

-(LatLng*)latLngFromLambertII:(LambertII*)lambertII;

-(NSString*)indentWithIndentLevel:(int)indentLevel;

-(void)dumpCoord:(Coord*)pCoord withPrompt:(NSString*)prompt indentLevel:(int)indentLevel;

@end
