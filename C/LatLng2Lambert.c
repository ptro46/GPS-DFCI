//
//  LatLng2Lambert.c
//  GPS-DFCI
//
//  Created by Patrice Trognon on 07/08/2015.
//

#include "LatLng2Lambert.h"

#include <math.h>

sLambertII  latLng2Lambert(double lat, double lng) {
    sLambertII lambertII ;
    
    // conversion en radians de lat et lng
    double lambda_w = lng * M_PI /180;
    double phi_w = lat * M_PI /180;
    
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

    lambertII.x = round(X_l2e*1000)/1000;
    lambertII.y = round(Y_l2e*1000)/1000;
    
    return lambertII ;
}
