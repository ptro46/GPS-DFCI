//
//  ZoneChasseSecteur5.h
//  DFCI-ObjC
//
//  Created by Patrice Trognon on 19/09/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CarreDFCI.h"

@class Coord;
@class Carre2Km ;
@class LambertII;

@interface ZoneChasseSecteur5 : CarreDFCI
@property(nonatomic)            int             numeroZone;

@property(nonatomic,strong)     Coord       *   coordSO;
@property(nonatomic,strong)     Coord       *   coordNO;
@property(nonatomic,strong)     Coord       *   coordNE;
@property(nonatomic,strong)     Coord       *   coordSE;
@property(nonatomic,strong)     Coord       *   coordCentre;

@property(nonatomic,strong)     Carre2Km    *   carre2Km;

-(instancetype)initWithNumeroZone:(int)numeroZone carre2Km:(Carre2Km*)carre2Km lambertOrigine:(LambertII*)lambert;
@end
