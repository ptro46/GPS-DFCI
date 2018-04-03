//
//  LatLng.m
//  DFCI-ObjC
//
//  Created by Patrice Trognon on 19/09/2015.
//  Copyright © 2015 Patrice Trognon. All rights reserved.
//

#import "LatLng.h"

#import "LambertII.h"

@interface LatLng ()
@property(nonatomic,strong)     LambertII       *       cachedLambertII ;
@property(nonatomic,strong)     NSString        *       cachedDFCI;
@end

@implementation LatLng

-(instancetype)initWithLatitude:(double)latitude longitude:(double)longitude {
    self = [super init];
    if ( self ) {
        self.latitude = latitude ;
        self.longitude = longitude ;
        self.cachedLambertII = nil ;
        self.cachedDFCI = nil ; 
    }
    return self;
}

-(LambertII*)lambertII {
    LambertII *lambertII ;
    double x;
    double y;
    
    if ( self.cachedLambertII != nil ) {
        return self.cachedLambertII ;
    }
    
    // conversion en radians de lat et lng
    double lambda_w = self.longitude * M_PI /180;
    double phi_w = self.latitude * M_PI /180;
    
    // conversion WGS84 géographiques > WGS84 cartésiennes
    // d'après formules du document de l'IGN NTG_80
    // constantes
    double a_w = 6378137.0; 	// demi grand axe système WGS84
    double b_w = 6356752.314;	// demi petit axe système WGS84
    
    //  calcul de la première excentricité dans le système WGS84
    double e2_w = ((a_w*a_w) - (b_w*b_w)) / (a_w*a_w);
    
    // calcul de la grande normale de l'ellipsoide WGS84
    double N = a_w / sqrt(1 - e2_w * pow(sin(phi_w),2));
    
    // calcul des coordonnées X,Y,Z dans le système WGS84
    double X_w = N * cos(phi_w) * cos(lambda_w);
    double Y_w = N * cos(phi_w) * sin(lambda_w);
    double Z_w = N * (1-e2_w) * sin(phi_w);
    
    // conversion WGS84 cartésiennes > NTF cartésiennes
    // simple translation. Données IGN.
    double X_n = X_w + 168;
    double Y_n = Y_w + 60;
    double Z_n = Z_w - 320;
    
    // conversion NTF cartésiennes > NTF géographiques
    // d'après formules du document de l'IGN sur la transformation entre systèmes géodésiques en France, page 4/14
    double a_n = 6378249.2; // demi grand axe système Clarke 1880 IGN
    double b_n = 6356515.0; // demi petit axe système Clarke 1880 IGN
    // calcul de la première excentricité dans le système NTF
    double e2_n = (pow(a_n,2)- pow(b_n,2)) / (pow(a_n,2));
    // on définit une tolérance de convergence
    double epsilon = pow(10,-10);
    // boucle de calcul
    double p0 = atan(Z_n/sqrt(X_n*X_n+Y_n*Y_n)*(1-(a_n*e2_n)/(sqrt(X_n*X_n+Y_n*Y_n+Z_n*Z_n))));
    double p1 = atan((Z_n/sqrt(X_n*X_n+Y_n*Y_n))/(1-(a_n*e2_n*cos(p0))/(sqrt((X_n*X_n+Y_n*Y_n)*(1-e2_n*pow(sin(p0),2))))));
    
    while(!(fabs(p1-p0)<epsilon)){
        p0 = p1;
        p1 = atan((Z_n/sqrt(X_n*X_n+Y_n*Y_n))/(1-(a_n*e2_n*cos(p0))/(sqrt((X_n*X_n+Y_n*Y_n)*(1-e2_n*pow(sin(p0),2))))));
    }
    
    double phi_n = p1;
    double lambda_n = atan(Y_n/X_n);
    
    // conversion NTF géographiques -> Lambert II étendu
    // constantes Lambert 2 étendu
    double n = 0.7289686274;
    double c = 11745793.39;
    double Xs = 600000.0;
    double Ys = 8199695.768;
    double lambda0 = 0.04079234433198;   //correspond à la longitude en radian de Paris (2°20'14.025" E) par rapport à Greenwich
    // excentricité de l'éllipsoïde
    double e_n = sqrt(e2_n);
    // calcul de la latitude isométrique
    double L = log(tan(M_PI/4 + phi_n/2) * pow(((1-e_n*sin(phi_n))/(1+e_n*sin(phi_n))),(e_n/2)));
    // projection
    double X_l2e = Xs + c*exp((-n*L))*sin(n*(lambda_n-lambda0));
    double Y_l2e = Ys - c*exp((-n*L))*cos(n*(lambda_n-lambda0));
    
    x = round(X_l2e*1000)/1000;
    y = round(Y_l2e*1000)/1000;
    
    lambertII = [[LambertII alloc]initWithXLambert:x YLambert:y];
    
    self.cachedLambertII = lambertII ;
    
    return lambertII ;
}

-(NSString*)dfci {
    NSString    *   nsDFCI = @"";
    char            dfci[10];
    char*           ABC = "ABCDEFGHKLMN012345678902468";
    int             index = 0 ;
    
    if ( self.cachedDFCI != nil ) {
        return self.cachedDFCI ;
    }
    
    LambertII *     lambertII = self.lambertII ;
    
    double x = round(lambertII.x);
    double y = round(lambertII.y);
    
    memset(dfci, 0, sizeof(dfci));
    
    if (x<=0 || x>=1200000 || y<=1600000 || y>=2700000) {
        return nsDFCI ;
        
    } else {
        // on ramène l'origine au sud de la Corse à zero
        y -= 1600000;
        
        // carré 100*100 km
        double X100 = floor(x/100000);
        double Y100 = floor(y/100000);
        
        dfci[index++] = ABC[(int)X100];
        dfci[index++] = ABC[((int)Y100)+1];
        
        // carré 20*20 km
        double Xtot =  x-(X100*100000);
        double Ytot =  y-(Y100*100000);
        double X20 = floor(Xtot/20000);
        double Y20 = floor(Ytot/20000);
        
        dfci[index++] = ABC[((int)X20)+22];
        dfci[index++] = ABC[((int)Y20)+22];
        
        // carré 2*2 km
        Xtot -= (X20*20000);
        Ytot -= (Y20*20000);
        double X2 = floor(Xtot/2000);
        double Y2 = floor(Ytot/2000);
        
        dfci[index++] = ABC[((int)X2)+0];
        dfci[index++] = ABC[((int)Y2)+12];
        
        // découpage "chasse" en 5 zones
        Xtot -= (X2*2000);
        Ytot -= (Y2*2000);
        
        char Xc;
        if (Xtot>500 && Xtot<1500 && Ytot>500 && Ytot<1500) {
            Xc='5';
        } else if (Xtot<1000 && Ytot>1000) {
            Xc='1';
        } else if (Xtot<1000 && Ytot<1000) {
            Xc='4';
        } else if (Xtot>1000 && Ytot>1000) {
            Xc='2';
        } else if (Xtot>1000 &&  Ytot<1000) {
            Xc='3';
        }
        
        dfci[index++] = '.';
        dfci[index++] = Xc;
    }
    
    nsDFCI = [NSString stringWithFormat:@"%s",dfci];
    
    self.cachedDFCI = nsDFCI ;
    
    return nsDFCI ;
}

@end
