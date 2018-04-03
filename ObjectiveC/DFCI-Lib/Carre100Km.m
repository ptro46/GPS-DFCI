//
//  Carre100Km.m
//  DFCI-ObjC
//
//  Created by Patrice Trognon on 19/09/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#import "Carre100Km.h"

#import "Globals.h"

#import "LambertII.h"
#import "Coord.h"
#import "Carre20Km.h"

@interface Carre100Km ()
@property(nonatomic,strong)     NSMutableArray          *   matriceCarres20Km;
@end

@implementation Carre100Km

-(instancetype)initWithDFCI:(NSString*)dfci {
    self = [super init];
    if ( self ) {
        self.nomDFCIComplet = dfci ;
        self.nomDFCICarre100Km = [dfci substringWithRange:NSMakeRange(0, 2)];
        
        NSString *dfci100Km = [NSString stringWithFormat:@"%@00A0.4",self.nomDFCICarre100Km];
        
        //---
        //   calculer le point SO en lambert
        LambertII *lambert = [self lambertIIFromDFCI:dfci100Km];
        LatLng *latLng = [self latLngFromLambertII:lambert];
        self.coordSO = [[Coord alloc]initWithLatLng:latLng lambertII:lambert];
        
        //---
        //   depuis le point SO calcul des autres points dans un carré de 100 000 m
        {
            LambertII *lambertIISE = [[LambertII alloc]initWithXLambert:lambert.x + 100000
                                                               YLambert:lambert.y];
            LatLng *latLngSE = [self latLngFromLambertII:lambertIISE];
            self.coordSE = [[Coord alloc]initWithLatLng:latLngSE lambertII:lambertIISE];
        }
        
        {
            LambertII *lambertIINE = [[LambertII alloc]initWithXLambert:lambert.x + 100000
                                                               YLambert:lambert.y + 100000];
            LatLng *latLngNE = [self latLngFromLambertII:lambertIINE];
            self.coordNE = [[Coord alloc]initWithLatLng:latLngNE lambertII:lambertIINE];
        }
        
        {
            LambertII *lambertIINO = [[LambertII alloc]initWithXLambert:lambert.x
                                                               YLambert:lambert.y + 100000 ];
            LatLng *latLngNO = [self latLngFromLambertII:lambertIINO];
            self.coordNO = [[Coord alloc]initWithLatLng:latLngNO lambertII:lambertIINO];
        }
        
        {
            LambertII *lambertIICentre = [[LambertII alloc]initWithXLambert:lambert.x + 50000
                                                                   YLambert:lambert.y + 50000];
            LatLng *latLngCentre = [self latLngFromLambertII:lambertIICentre];
            self.coordCentre = [[Coord alloc]initWithLatLng:latLngCentre lambertII:lambertIICentre];
        }
        
        self.matriceCarres20Km = nil ;
    }
    return self;
}

-(instancetype)initWithLatitude:(double)latitude longitude:(double)longitude { // TODO
    self = [super init];
    return self ;
}

-(void)performDetails {
    Carre20Km *carre20Km ;

    if ( self.matriceCarres20Km == nil || self.matriceCarres20Km.count != 5*5 ) {
        self.matriceCarres20Km = [NSMutableArray array];
        char LambertX[] = "02468";
        char LambertY[] = "02468";
        for(int x=0; x<5; x++) {
            for(int y=0; y<5;y++) {
                NSString *dfci = [NSString stringWithFormat:@"%@%c%cA0.4",self.nomDFCICarre100Km,LambertX[x],LambertY[y]];
                carre20Km = [[Carre20Km alloc]initWithDFCI:dfci carre100Km:self];
                [self.matriceCarres20Km addObject:carre20Km];
            }
        }
        
        for(Carre20Km *carre20Km in self.matriceCarres20Km) {
            [carre20Km performDetails];
        }

    }
}

-(Carre20Km*)carre20KmWithX:(int)x andY:(int)y {
    Carre20Km *carre20Km ;
    
    [self performDetails];
    
    carre20Km = self.matriceCarres20Km[(x*5)+y];
    
    return carre20Km ;
}

-(Carre100Km*)northCarre100Km { // TODO
    
    return nil ;
}

-(Carre100Km*)northEastCarre100Km { // TODO
    return nil ;
}

-(Carre100Km*)eastCarre100Km { // TODO
    return nil ;
}

-(Carre100Km*)southEastCarre100Km { // TODO
    return nil ;
}

-(Carre100Km*)southCarre100Km { // TODO
    return nil ;
}

-(Carre100Km*)southWestCarre100Km { // TODO
    return nil ;
}

-(Carre100Km*)westCarre100Km { // TODO
    return nil ;
}

-(Carre100Km*)northWestCarre100Km { // TODO
    return nil ;
}

-(void)dumpWithIndentLevel:(int)indentLevel {
    CustomLog(@"%@Carre100Km {\n",[self indentWithIndentLevel:indentLevel]);
    CustomLog(@"%@    dfci : %@\n",[self indentWithIndentLevel:indentLevel],self.nomDFCICarre100Km);
    [self dumpCoord:self.coordCentre withPrompt:@"coordCentre" indentLevel:indentLevel+2];
    [self dumpCoord:self.coordSO withPrompt:@"coordSO" indentLevel:indentLevel+2];
    [self dumpCoord:self.coordNO withPrompt:@"coordNO" indentLevel:indentLevel+2];
    [self dumpCoord:self.coordNE withPrompt:@"coordNE" indentLevel:indentLevel+2];
    [self dumpCoord:self.coordSE withPrompt:@"coordSE" indentLevel:indentLevel+2];
    if ( self.matriceCarres20Km != nil && self.matriceCarres20Km.count > 0 ) {
        for(Carre20Km *carre20Km in self.matriceCarres20Km) {
            [carre20Km dumpWithIndentLevel:indentLevel+1];
        }
    }
    CustomLog(@"%@}\n",[self indentWithIndentLevel:indentLevel]);
}

@end
