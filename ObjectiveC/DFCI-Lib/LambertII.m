//
//  LambertII.m
//  DFCI-ObjC
//
//  Created by Patrice Trognon on 19/09/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#import "LambertII.h"

@implementation LambertII

-(instancetype)initWithXLambert:(double)x YLambert:(double)y {
    self = [super init];
    if ( self ) {
        self.x = x ;
        self.y = y ;
    }
    return self;
}

@end
