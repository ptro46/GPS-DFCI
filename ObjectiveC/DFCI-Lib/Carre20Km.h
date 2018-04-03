//
//  Carre20Km.h
//  DFCI-ObjC
//
//  Created by Patrice Trognon on 19/09/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CarreDFCI.h"

@class Coord ;
@class Carre2Km;
@class Carre100Km;

@interface Carre20Km : CarreDFCI

@property(nonatomic,strong)     NSString                *   nomDFCIComplet;
@property(nonatomic,strong)     NSString                *   nomDFCICarre20Km;
@property(nonatomic,strong)     Coord                   *   coordCentre;
@property(nonatomic,strong)     Coord                   *   coordSO;
@property(nonatomic,strong)     Coord                   *   coordNO;
@property(nonatomic,strong)     Coord                   *   coordNE;
@property(nonatomic,strong)     Coord                   *   coordSE;


@property(nonatomic,strong)     Carre100Km              *   carre100Km;

-(instancetype)initWithLatitude:(double)latitude longitude:(double)longitude;
-(instancetype)initWithDFCI:(NSString*)dfci carre100Km:(Carre100Km*)carre100Km;

-(void)performDetails;

-(Carre2Km*)carre2KmWithX:(int)x andY:(int)y;

-(Carre20Km*)northCarre20Km;
-(Carre20Km*)northEastCarre20Km;
-(Carre20Km*)eastCarre20Km;
-(Carre20Km*)southEastCarre20Km;
-(Carre20Km*)southCarre20Km;
-(Carre20Km*)southWestCarre20Km;
-(Carre20Km*)westCarre20Km;
-(Carre20Km*)northWestCarre20Km;

-(void)dumpWithIndentLevel:(int)indentLevel;

@end
