//
//  LambertII.h
//  DFCI-ObjC
//
//  Created by Patrice Trognon on 19/09/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface LambertII : NSObject

@property(nonatomic)    double      x;
@property(nonatomic)    double      y;

-(instancetype)initWithXLambert:(double)x YLambert:(double)y;

@end
