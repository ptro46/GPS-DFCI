//
//  Carre2Km.m
//  DFCI-ObjC
//
//  Created by Patrice Trognon on 19/09/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#import "Carre2Km.h"

#import "Globals.h"

#import "LambertII.h"
#import "Coord.h"
#import "ZoneChasseSecteur1.h"
#import "ZoneChasseSecteur2.h"
#import "ZoneChasseSecteur3.h"
#import "ZoneChasseSecteur4.h"
#import "ZoneChasseSecteur5.h"

@interface Carre2Km ()

@end

@implementation Carre2Km

-(instancetype)initWithDFCI:(NSString*)dfci carre20Km:(Carre20Km*)carre20km {
    self = [super init];
    if ( self ) {
        self.nomDFCIComplet = dfci ;
        self.nomDFCICarre2Km = [dfci substringWithRange:NSMakeRange(0, 6)];
        
        self.carre20km = carre20km ;
        
        NSString *dfci2Km = [NSString stringWithFormat:@"%@.4",[dfci substringWithRange:NSMakeRange(0, 6)]];
        
        //---
        //   calculer le point SO en lambert
        LambertII *lambert = [self lambertIIFromDFCI:dfci2Km];
        LatLng *latLng = [self latLngFromLambertII:lambert];
        self.coordSO = [[Coord alloc]initWithLatLng:latLng lambertII:lambert];
        
        //---
        //   depuis le point SO calcul des autres points dans un carré de 2 000 m
        {
            LambertII *lambertIISE = [[LambertII alloc]initWithXLambert:lambert.x + 2000
                                                               YLambert:lambert.y];
            LatLng *latLngSE = [self latLngFromLambertII:lambertIISE];
            self.coordSE = [[Coord alloc]initWithLatLng:latLngSE lambertII:lambertIISE];
        }
        
        {
            LambertII *lambertIINE = [[LambertII alloc]initWithXLambert:lambert.x + 2000
                                                               YLambert:lambert.y + 2000];
            LatLng *latLngNE = [self latLngFromLambertII:lambertIINE];
            self.coordNE = [[Coord alloc]initWithLatLng:latLngNE lambertII:lambertIINE];
        }
        
        {
            LambertII *lambertIINO = [[LambertII alloc]initWithXLambert:lambert.x
                                                               YLambert:lambert.y + 2000 ];
            LatLng *latLngNO = [self latLngFromLambertII:lambertIINO];
            self.coordNO = [[Coord alloc]initWithLatLng:latLngNO lambertII:lambertIINO];
        }
        
        {
            LambertII *lambertIICentre = [[LambertII alloc]initWithXLambert:lambert.x + 1000
                                                                   YLambert:lambert.y + 1000];
            LatLng *latLngCentre = [self latLngFromLambertII:lambertIICentre];
            self.coordCentre = [[Coord alloc]initWithLatLng:latLngCentre lambertII:lambertIICentre];
        }
        
        self.secteur1 = [[ZoneChasseSecteur1 alloc]initWithNumeroZone:1 carre2Km:self lambertOrigine:lambert];
        self.secteur2 = [[ZoneChasseSecteur2 alloc]initWithNumeroZone:2 carre2Km:self lambertOrigine:lambert];
        self.secteur3 = [[ZoneChasseSecteur3 alloc]initWithNumeroZone:3 carre2Km:self lambertOrigine:lambert];
        self.secteur4 = [[ZoneChasseSecteur4 alloc]initWithNumeroZone:4 carre2Km:self lambertOrigine:lambert];
        self.secteur5 = [[ZoneChasseSecteur5 alloc]initWithNumeroZone:5 carre2Km:self lambertOrigine:lambert];

    }
    return self;
}

-(Carre2Km*)northCarre2Km {
    return nil ;
}

-(Carre2Km*)northEastCarre2Km {
    return nil ;
}

-(Carre2Km*)eastCarre2Km {
    return nil ;
}

-(Carre2Km*)southEastCarre2Km {
    return nil ;
}

-(Carre2Km*)southCarre2Km {
    return nil ;
}

-(Carre2Km*)southWestCarre2Km {
    return nil ;
}

-(Carre2Km*)westCarre2Km {
    return nil ;
}

-(Carre2Km*)northWestCarre2Km {
    return nil ;
}

-(void)dumpWithIndentLevel:(int)indentLevel {
    CustomLog(@"%@Carre2Km {\n",[self indentWithIndentLevel:indentLevel]);
    CustomLog(@"%@    dfci : %@\n",[self indentWithIndentLevel:indentLevel],self.nomDFCICarre2Km);
    [self dumpCoord:self.coordCentre withPrompt:@"coordCentre" indentLevel:indentLevel+2];
    [self dumpCoord:self.coordSO withPrompt:@"coordSO" indentLevel:indentLevel+2];
    [self dumpCoord:self.coordNO withPrompt:@"coordNO" indentLevel:indentLevel+2];
    [self dumpCoord:self.coordNE withPrompt:@"coordNE" indentLevel:indentLevel+2];
    [self dumpCoord:self.coordSE withPrompt:@"coordSE" indentLevel:indentLevel+2];

    CustomLog(@"%@        secteur1 {\n",[self indentWithIndentLevel:indentLevel]);
    [self dumpCoord:self.secteur1.coordSO withPrompt:@"coordSO" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur1.coordNO withPrompt:@"coordNO" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur1.coordNE withPrompt:@"coordNE" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur1.coordSEIntermediaire1 withPrompt:@"coordSEIntermediaire1" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur1.coordSEIntermediaire2 withPrompt:@"coordSEIntermediaire2" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur1.coordSEIntermediaire3 withPrompt:@"coordSEIntermediaire3" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur1.coordSE withPrompt:@"coordSE" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur1.coordCentre withPrompt:@"coordCentre" indentLevel:indentLevel+3];
    CustomLog(@"%@        }\n",[self indentWithIndentLevel:indentLevel]);

    CustomLog(@"%@        secteur2 {\n",[self indentWithIndentLevel:indentLevel]);
    [self dumpCoord:self.secteur2.coordSO withPrompt:@"coordSO" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur2.coordSOIntermediaire1 withPrompt:@"coordSOIntermediaire1" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur2.coordSOIntermediaire2 withPrompt:@"coordSOIntermediaire2" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur2.coordSOIntermediaire3 withPrompt:@"coordSOIntermediaire3" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur2.coordNO withPrompt:@"coordNO" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur2.coordNE withPrompt:@"coordNE" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur2.coordSE withPrompt:@"coordSE" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur2.coordCentre withPrompt:@"coordCentre" indentLevel:indentLevel+3];
    CustomLog(@"%@        }\n",[self indentWithIndentLevel:indentLevel]);

    CustomLog(@"%@        secteur3 {\n",[self indentWithIndentLevel:indentLevel]);
    [self dumpCoord:self.secteur3.coordSO withPrompt:@"coordSO" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur3.coordNOIntermediaire1 withPrompt:@"coordNOIntermediaire1" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur3.coordNOIntermediaire2 withPrompt:@"coordNOIntermediaire2" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur3.coordNOIntermediaire3 withPrompt:@"coordNOIntermediaire3" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur3.coordNO withPrompt:@"coordNO" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur3.coordNE withPrompt:@"coordNE" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur3.coordSE withPrompt:@"coordSE" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur3.coordCentre withPrompt:@"coordCentre" indentLevel:indentLevel+3];
    CustomLog(@"%@        }\n",[self indentWithIndentLevel:indentLevel]);

    CustomLog(@"%@        secteur4 {\n",[self indentWithIndentLevel:indentLevel]);
    [self dumpCoord:self.secteur4.coordSO withPrompt:@"coordSO" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur4.coordNO withPrompt:@"coordNO" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur4.coordNEIntermediaire1 withPrompt:@"coordNEIntermediaire1" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur4.coordNEIntermediaire2 withPrompt:@"coordNEIntermediaire2" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur4.coordNEIntermediaire3 withPrompt:@"coordNEIntermediaire3" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur4.coordNE withPrompt:@"coordNE" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur4.coordSE withPrompt:@"coordSE" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur4.coordCentre withPrompt:@"coordCentre" indentLevel:indentLevel+3];
    CustomLog(@"%@        }\n",[self indentWithIndentLevel:indentLevel]);

    CustomLog(@"%@        secteur5 {\n",[self indentWithIndentLevel:indentLevel]);
    [self dumpCoord:self.secteur5.coordSO withPrompt:@"coordSO" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur5.coordNO withPrompt:@"coordNO" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur5.coordNE withPrompt:@"coordNE" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur5.coordSE withPrompt:@"coordSE" indentLevel:indentLevel+3];
    [self dumpCoord:self.secteur5.coordCentre withPrompt:@"coordCentre" indentLevel:indentLevel+3];
    CustomLog(@"%@        }\n",[self indentWithIndentLevel:indentLevel]);

    CustomLog(@"%@}\n",[self indentWithIndentLevel:indentLevel]);
}

@end
