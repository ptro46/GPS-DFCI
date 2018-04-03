//
//  Carre100Km.h
//  DFCI-ObjC
//
//  Created by Patrice Trognon on 19/09/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CarreDFCI.h"

@class Coord ;
@class Carre20Km;

@interface Carre100Km : CarreDFCI

@property(nonatomic,strong)     NSString                *   nomDFCIComplet;
@property(nonatomic,strong)     NSString                *   nomDFCICarre100Km;
@property(nonatomic,strong)     Coord                   *   coordCentre;
@property(nonatomic,strong)     Coord                   *   coordSO;
@property(nonatomic,strong)     Coord                   *   coordNO;
@property(nonatomic,strong)     Coord                   *   coordNE;
@property(nonatomic,strong)     Coord                   *   coordSE;

-(instancetype)initWithLatitude:(double)latitude longitude:(double)longitude;
-(instancetype)initWithDFCI:(NSString*)dfci;

-(void)performDetails;

-(Carre20Km*)carre20KmWithX:(int)x andY:(int)y;

-(Carre100Km*)northCarre100Km;
-(Carre100Km*)northEastCarre100Km;
-(Carre100Km*)eastCarre100Km;
-(Carre100Km*)southEastCarre100Km;
-(Carre100Km*)southCarre100Km;
-(Carre100Km*)southWestCarre100Km;
-(Carre100Km*)westCarre100Km;
-(Carre100Km*)northWestCarre100Km;

-(void)dumpWithIndentLevel:(int)indentLevel;

@end
