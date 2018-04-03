//
//  Carre20Km.m
//  DFCI-ObjC
//
//  Created by Patrice Trognon on 19/09/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#import "Carre20Km.h"

#import "Globals.h"

#import "LambertII.h"
#import "Coord.h"
#import "Carre2Km.h"

@interface Carre20Km ()
@property(nonatomic,strong)     NSMutableArray          *   matriceCarres2Km;
@end

@implementation Carre20Km

-(instancetype)initWithDFCI:(NSString*)dfci carre100Km:(Carre100Km*)carre100Km {
    self = [super init];
    if ( self ) {
        self.nomDFCIComplet = dfci ;
        self.nomDFCICarre20Km = [dfci substringWithRange:NSMakeRange(0, 4)];
        
        self.carre100Km = carre100Km ;
        
        NSString *dfci20Km = [NSString stringWithFormat:@"%@A0.4",[dfci substringWithRange:NSMakeRange(0, 4)]];
        
        //---
        //   calculer le point SO en lambert
        LambertII *lambert = [self lambertIIFromDFCI:dfci20Km];
        LatLng *latLng = [self latLngFromLambertII:lambert];
        self.coordSO = [[Coord alloc]initWithLatLng:latLng lambertII:lambert];
        
        //---
        //   depuis le point SO calcul des autres points dans un carré de 20 000 m
        {
            LambertII *lambertIISE = [[LambertII alloc]initWithXLambert:lambert.x + 20000
                                                               YLambert:lambert.y];
            LatLng *latLngSE = [self latLngFromLambertII:lambertIISE];
            self.coordSE = [[Coord alloc]initWithLatLng:latLngSE lambertII:lambertIISE];
        }
        
        {
            LambertII *lambertIINE = [[LambertII alloc]initWithXLambert:lambert.x + 20000
                                                               YLambert:lambert.y + 20000];
            LatLng *latLngNE = [self latLngFromLambertII:lambertIINE];
            self.coordNE = [[Coord alloc]initWithLatLng:latLngNE lambertII:lambertIINE];
        }
        
        {
            LambertII *lambertIINO = [[LambertII alloc]initWithXLambert:lambert.x
                                                               YLambert:lambert.y + 20000 ];
            LatLng *latLngNO = [self latLngFromLambertII:lambertIINO];
            self.coordNO = [[Coord alloc]initWithLatLng:latLngNO lambertII:lambertIINO];
        }
        
        {
            LambertII *lambertIICentre = [[LambertII alloc]initWithXLambert:lambert.x + 10000
                                                                   YLambert:lambert.y + 10000];
            LatLng *latLngCentre = [self latLngFromLambertII:lambertIICentre];
            self.coordCentre = [[Coord alloc]initWithLatLng:latLngCentre lambertII:lambertIICentre];
        }
        
    }
    return self;
}

-(instancetype)initWithLatitude:(double)latitude longitude:(double)longitude { // TODO
    self = [super init];
    return self ;
}

-(void)performDetails {
    Carre2Km *carre2Km ;
    
    if ( self.matriceCarres2Km == nil || self.matriceCarres2Km.count != 10*10 ) {
        self.matriceCarres2Km = [NSMutableArray array];
        char LambertX[] = "ABCDEFGHKL";
        char LambertY[] = "0123456789";
        for(int x=0; x<10; x++) {
            for(int y=0; y<10;y++) {
                NSString *dfci = [NSString stringWithFormat:@"%@%c%c.4",[self.nomDFCIComplet substringWithRange:NSMakeRange(0, 4)],LambertX[x],LambertY[y]];
                carre2Km = [[Carre2Km alloc]initWithDFCI:dfci carre20Km:self];
                [self.matriceCarres2Km addObject:carre2Km];
            }
        }
    }
}

-(Carre2Km*)carre2KmWithX:(int)x andY:(int)y {
    Carre2Km *carre2Km ;

    [self performDetails];
    
    carre2Km = self.matriceCarres2Km[(x*10)+y];
    
    return carre2Km ;
}

-(Carre20Km*)northCarre20Km { // TODO
    return nil ;
}

-(Carre20Km*)northEastCarre20Km { // TODO
    return nil ;
}

-(Carre20Km*)eastCarre20Km { // TODO
    return nil ;
}

-(Carre20Km*)southEastCarre20Km { // TODO
    return nil ;
}

-(Carre20Km*)southCarre20Km { // TODO
    return nil ;
}

-(Carre20Km*)southWestCarre20Km { // TODO
    return nil ;
}

-(Carre20Km*)westCarre20Km { // TODO
    return nil ;
}

-(Carre20Km*)northWestCarre20Km { // TODO
    return nil ;
}

-(void)dumpWithIndentLevel:(int)indentLevel {
    CustomLog(@"%@Carre20Km {\n",[self indentWithIndentLevel:indentLevel]);
    CustomLog(@"%@    dfci : %@\n",[self indentWithIndentLevel:indentLevel],self.nomDFCICarre20Km);
    [self dumpCoord:self.coordCentre withPrompt:@"coordCentre" indentLevel:indentLevel+2];
    [self dumpCoord:self.coordSO withPrompt:@"coordSO" indentLevel:indentLevel+2];
    [self dumpCoord:self.coordNO withPrompt:@"coordNO" indentLevel:indentLevel+2];
    [self dumpCoord:self.coordNE withPrompt:@"coordNE" indentLevel:indentLevel+2];
    [self dumpCoord:self.coordSE withPrompt:@"coordSE" indentLevel:indentLevel+2];
    if ( self.matriceCarres2Km != nil && self.matriceCarres2Km.count > 0 ) {
        for(Carre2Km *carre2Km in self.matriceCarres2Km) {
            [carre2Km dumpWithIndentLevel:indentLevel+1];
        }
    }
    CustomLog(@"%@}\n",[self indentWithIndentLevel:indentLevel]);
}

@end
