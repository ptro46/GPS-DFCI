//
//  Carre2Km.h
//  DFCI-ObjC
//
//  Created by Patrice Trognon on 19/09/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CarreDFCI.h"

@class Coord ;
@class ZoneChasseSecteur1;
@class ZoneChasseSecteur2;
@class ZoneChasseSecteur3;
@class ZoneChasseSecteur4;
@class ZoneChasseSecteur5;

@class Carre20Km;

@interface Carre2Km : CarreDFCI

@property(nonatomic,strong)     NSString                *   nomDFCIComplet;
@property(nonatomic,strong)     NSString                *   nomDFCICarre2Km;
@property(nonatomic,strong)     Coord                   *   coordCentre;
@property(nonatomic,strong)     Coord                   *   coordSO;
@property(nonatomic,strong)     Coord                   *   coordNO;
@property(nonatomic,strong)     Coord                   *   coordNE;
@property(nonatomic,strong)     Coord                   *   coordSE;

@property(nonatomic,strong)     ZoneChasseSecteur1      *   secteur1;
@property(nonatomic,strong)     ZoneChasseSecteur2      *   secteur2;
@property(nonatomic,strong)     ZoneChasseSecteur3      *   secteur3;
@property(nonatomic,strong)     ZoneChasseSecteur4      *   secteur4;
@property(nonatomic,strong)     ZoneChasseSecteur5      *   secteur5;

@property(nonatomic,strong)     Carre20Km               *   carre20km;

-(instancetype)initWithDFCI:(NSString*)dfci carre20Km:(Carre20Km*)carre20km;

-(Carre2Km*)northCarre2Km;
-(Carre2Km*)northEastCarre2Km;
-(Carre2Km*)eastCarre2Km;
-(Carre2Km*)southEastCarre2Km;
-(Carre2Km*)southCarre2Km;
-(Carre2Km*)southWestCarre2Km;
-(Carre2Km*)westCarre2Km;
-(Carre2Km*)northWestCarre2Km;

-(void)dumpWithIndentLevel:(int)indentLevel;

@end
