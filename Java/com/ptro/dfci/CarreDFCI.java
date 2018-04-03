package com.ptro.dfci;

import static com.ptro.dfci.SubString.subString;

public abstract class CarreDFCI {

	protected LambertII lambertIIFromLatitudeAndLongitude(double latitude, double longitude) {
		LatLng latLng = new LatLng(latitude, longitude);
		return latLng.getLambertII() ;
	}
	
	protected LambertII lambertIIFromDFCI(String dfci) {
	    LambertII lambertII ;
	    double XLamb, YLamb ;
	    
	    YLamb=1500000 ;
	    XLamb=0;
	    
	    String carre100 = subString(dfci, 0, 2);
	    String carre20 = subString(dfci,2,2);
	    String carre2 = subString(dfci,4,2);
	    String zon5 = subString(dfci,6,2);
	    
	    String dfciLetters = "ABCDEFGHKLMN";
	    
	    int a;
	    
	    //---
	    //  FE06H1.2
	    //  F
	    //  E
	    a = dfciLetters.indexOf(dfci.charAt(0));
	    XLamb = XLamb + a*100000;
	    a = dfciLetters.indexOf(dfci.charAt(1));
	    YLamb = YLamb + a*100000;

	    //---
	    //  FE06H1.2
	    //  06
	    String a20 = subString(carre20, 0, 1);
	    a = Integer.parseInt(a20)/2;
	    XLamb = XLamb + a*20000;
	    
	    a20 = subString(carre20, 1, 1);
	    a = Integer.parseInt(a20)/2;
	    YLamb = YLamb + a*20000;
	    
	    a = dfciLetters.indexOf(carre2.charAt(0));
	    XLamb = XLamb + a*2000;
	    
	    a20 = subString(carre2, 1, 1);
	    a = Integer.parseInt(a20);
	    YLamb = YLamb + a*2000;
	    
	    switch ( zon5.charAt(1) ) {
	        case '1' : {
	            //XLamb = XLamb+500;
	            YLamb = YLamb+1000;
	        } break ;
	            
	        case '2' : {
	            XLamb = XLamb+1500;
	            YLamb = YLamb+1500;
	        } break ;
	            
	        case '3' : {
	            XLamb = XLamb+1000;
	            //YLamb = YLamb+500;
	        } break ;
	            
	        case '4' : {
	            //XLamb = XLamb+500;
	            //YLamb = YLamb+500;
	        } break ;
	            
	        default : {
	            XLamb = XLamb+500;
	            YLamb = YLamb+500;
	        } break ;
	    }
	    
	    lambertII = new LambertII(XLamb, YLamb);
	    
	    return lambertII ;
	}
	
	protected LatLng latLngFromLambertII(LambertII lambertII) {
	    LatLng latLng ;
	    
	    double latNTF ;
	    double lonNTF ;
	    
	    double latitude ;
	    double longitude ;
	    
	    latNTF = lambLatNTFFromLambert(lambertII.getX(), lambertII.getY(), 0);
	    lonNTF = lambLonNTFFromLambert(lambertII.getX(), lambertII.getY(), 0);
	    
	    latitude =  ntfLatWGSFromLatLonNTF(latNTF, lonNTF);
	    longitude = ntfLonWGSFromLatLonNTF(latNTF, lonNTF);
	    
	    latLng = new LatLng(latitude, longitude);
	    return latLng ;
	}
	
	protected String indentWithIndentLevel(int indentLevel) {
		StringBuffer buffer = new StringBuffer();
		
	    for(int i=0; i<indentLevel; i++) {
	        buffer.append("    ");
	    }
		
		return buffer.toString() ;
	}
	
	protected void dumpCoordWithPrompt(Coord pCoord, String prompt, int indentLevel) {
	    System.out.printf("%sCoordonnees %s {\n",indentWithIndentLevel(indentLevel),prompt);
	    System.out.printf("%s    LambertII : {\n",indentWithIndentLevel(indentLevel));
	    System.out.printf("%s        x:%f\n",indentWithIndentLevel(indentLevel),pCoord.getLambertII().getX());
	    System.out.printf("%s        y:%f\n",indentWithIndentLevel(indentLevel),pCoord.getLambertII().getY());
	    System.out.printf("%s    }\n",indentWithIndentLevel(indentLevel));
	    System.out.printf("%s    GPS : {\n",indentWithIndentLevel(indentLevel));
	    System.out.printf("%s        lat:%f\n",indentWithIndentLevel(indentLevel),pCoord.getLatLng().getLatitude());
	    System.out.printf("%s        lng:%f\n",indentWithIndentLevel(indentLevel),pCoord.getLatLng().getLongitude());
	    System.out.printf("%s    }\n",indentWithIndentLevel(indentLevel));
	    System.out.printf("%s}\n",indentWithIndentLevel(indentLevel));
	}
	
	private double lambLatNTFFromLambert(double xLambert, double yLambert, int typLamb) {
	    double Clarke1880;
	    double e, R, L, n, c, Xs, Ys;
	    
	    //    double rad2Deg=180/M_PI;
	    //    double deg2Rad=M_PI/180;
	    
	    Clarke1880=0.08248325676342;
	    e=Clarke1880;
	    
	    //   Lambert II etendu par defaut
	    switch ( typLamb ) {
	        case 1: {
	            n = 0.7604059656;
	            c = 11603796.98;
	            Xs = 600000;
	            Ys = 5657616.674;
	        } break ;
	            
	        case 2: {
	            n = 0.7289686274;
	            c = 11745793.39;
	            Xs = 600000;
	            Ys = 6199695.768;
	            
	        } break ;
	            
	        case 3: {
	            n = 0.6959127966;
	            c = 11947992.52;
	            Xs = 600000;
	            Ys = 6791905.085;
	        } break ;
	            
	        case 4: {
	            n = 0.6712679322;
	            c = 12136281.99;
	            Xs = 234.358;
	            Ys = 7239161.542;
	        } break ;
	            
	        default: {
	            n = 0.7289686274;
	            c = 11745793.39;
	            Xs = 600000;
	            Ys = 8199695.768;
	        } break ;
	            
	    }
	    
	    R = Math.sqrt((xLambert-Xs)*(xLambert-Xs) + (yLambert-Ys)*(yLambert-Ys));
	    L = -1 / n * Math.log(Math.abs(R/c));
	    return isomLat(L,e,0.00000000001);
	}
	
	private double lambLonNTFFromLambert(double xLambert, double yLambert, int typLamb) {
	    double LX=0.0, R=0.0, g=0.0, n=0.0, c=0.0, Xs=0.0, Ys=0.0;
	    
	    double rad2Deg=180/Math.PI;
	    //    double deg2Rad=M_PI/180;
	    
	    //    double MeridParis = 2.33722916666667;
	    
	    //   Lambert II etendu par defaut
	    switch ( typLamb ) {
	        case 1: {
	            n = 0.7604059656;
	            c = 11603796.98;
	            Xs = 600000;
	            Ys = 5657616.674;
	        } break ;
	            
	        case 2: {
	            n = 0.7289686274;
	            c = 11745793.39;
	            Xs = 600000;
	            Ys = 6199695.768;
	            
	        } break ;
	            
	        case 3: {
	            n = 0.6959127966;
	            c = 11947992.52;
	            Xs = 600000;
	            Ys = 6791905.085;
	        } break ;
	            
	        case 4: {
	            n = 0.6712679322;
	            c = 12136281.99;
	            Xs = 234.358;
	            Ys = 7239161.542;
	        } break ;
	            
	        default: {
	            n = 0.7289686274;
	            c = 11745793.39;
	            Xs = 600000;
	            Ys = 8199695.768;
	        } break ;
	            
	    }
	    
	    R = Math.sqrt((xLambert-Xs)*(xLambert-Xs) + (yLambert-Ys)*(yLambert-Ys));
	    g = Math.atan((xLambert-Xs) / (Ys-yLambert));
	    LX= g / n;
	    return LX*rad2Deg;
	}
	
	private double ntfLatWGSFromLatLonNTF(double latitudeNTF, double longitudeNTF) {
	    double Phi, Lambda, h, AA, aNTF, aWGS, b=0.0, bNTF, bWGS, eNTF, eWGS, e2, v, X, Y, Z, p, r, f, u;
	    double MeridParis;
	    MeridParis=2.33722916666667;
	    
	    double rad2Deg=180/Math.PI;
	    double deg2Rad=Math.PI/180;
	    
	    Phi = latitudeNTF*deg2Rad;
	    Lambda = (longitudeNTF+MeridParis)*deg2Rad;
	    h = 0;
	    
	    // aNTF = Demi Grand-Axe de l'ellipsoïde de Clarke 1880
	    aNTF = 6378249.2;
	    
	    // bNTF = Demi Petit-Axe de l'ellipsoïde de Clarke 1880
	    bNTF = 6356515 ;
	    
	    // eNTF = Premiere Excentricite de l'ellipsoïde de Clarke 1880
	    eNTF = Math.sqrt(1 - (bNTF / aNTF)*(bNTF / aNTF));
	    
	    // aWGS = Demi Grand-Axe de l'ellipsoïde WGS84
	    aWGS = 6378137;
	    
	    // bWGS = Demi Petit-Axe de l'ellipsoïde WGS84
	    bWGS = 6356752.314;
	    
	    // eWGS = Premiere Excentricite de l'ellipsoïde WGS84
	    eWGS = Math.sqrt(1 - (bWGS / aWGS)*(bWGS / aWGS));
	    AA = aNTF;
	    e2 = eNTF * eNTF;
	    f = (AA - b) / AA;
	    v = AA / Math.sqrt(1 - e2 * Math.sin(Phi) * Math.sin(Phi));
	    
	    // Coordonnee Geocentriques NTF : X, Y, Z
	    X = (v + h) * Math.cos(Phi) * Math.cos(Lambda);
	    Y = (v + h) * Math.cos(Phi) * Math.sin(Lambda);
	    Z = ((1 - e2) * v + h) * Math.sin(Phi);
	    
	    // Changement de referentiel NGF vers WGS84
	    X = X - 168;
	    Y = Y - 60;
	    Z = Z + 320;
	    AA = aWGS;
	    b = bWGS;
	    e2 = eWGS * eWGS;
	    f = (AA - b) / AA;
	    p = Math.sqrt(X * X + Y * Y);
	    r = p + Z * Z;
	    u = Math.atan((Z / p) * ((1 - f) + (e2 * AA / r)));
	    Phi = Math.atan((Z * (1 - f) + e2 * AA * Math.sin(u) * Math.sin(u) * Math.sin(u)) / ((1 - f) * (p - e2 * AA * Math.cos(u) * Math.cos(u) * Math.cos(u))));
	    
	    return Phi*rad2Deg;
	}
	
	private double ntfLonWGSFromLatLonNTF(double latitudeNTF, double longitudeNTF) {
	    double Phi, Lambda, h, AA, aNTF, b=0.0, bNTF, eNTF, e2, v, X, Y, Z, f;
	    double MeridParis;
	    MeridParis=2.33722916666667;
	    
	    double rad2Deg=180/Math.PI;
	    double deg2Rad=Math.PI/180;
	    
	    // h = hauteur sur l'ellipsoïde - mis à zero
	    Phi = latitudeNTF*deg2Rad;
	    Lambda = (longitudeNTF+MeridParis)*deg2Rad;
	    h = 0;
	    
	    // aNTF = Demi Grand-Axe de l'ellipsoïde de Clarke 1880
	    aNTF = 6378249.2;
	    
	    // bNTF = Demi Petit-Axe de l'ellipsoïde de Clarke 1880
	    bNTF = 6356515 ;
	    
	    // eNTF = Premiere Excentricite de l'ellipsoïde de Clarke 1880
	    eNTF= Math.sqrt(1 - (bNTF / aNTF)*(bNTF / aNTF));
	    AA = aNTF;
	    e2 = eNTF * eNTF;
	    f = (AA - b) / AA;
	    v = AA / Math.sqrt(1 - e2 * Math.sin(Phi) * Math.sin(Phi));
	    
	    // Coordonnee Geocentriques NTF : X, Y, Z
	    X = (v + h) * Math.cos(Phi) * Math.cos(Lambda);
	    Y = (v + h) * Math.cos(Phi) * Math.sin(Lambda);
	    Z = ((1 - e2) * v + h) * Math.sin(Phi);
	    
	    // Changement de referentiel NTF vers WGS84
	    X = X - 168;
	    Y = Y - 60;
	    Z = Z + 320;
	    
	    Lambda = Math.atan(Y / X);
	    if ( X < 0 ) {
	        Lambda = Lambda + Math.PI;
	    }
	    return Lambda*rad2Deg;
	}
	
	private double isomLat(double latitIsom, double premExcEllips, double tolConverg) {
	    double rad2Deg=180/Math.PI;
	    //    double deg2Rad=M_PI/180;
	    
	    double EL=Math.exp(latitIsom);
	    
	    double rPremEx=premExcEllips;
	    double rTolConv=tolConverg;
	    
	    double s0 = 0;
	    double s1 = 2 * Math.atan(EL)-Math.PI/2;
	    double d=0;
	    
	    while (Math.abs(s0 - s1) > rTolConv ) {
	        s0 = s1;
	        d = Math.log(((1 + rPremEx * Math.sin(s0)) / (1 - rPremEx * Math.sin(s0))));
	        d = Math.exp(d*(rPremEx / 2));
	        s1 = 2 * Math.atan(d*EL)-Math.PI/2;
	    }
	    return s1 * rad2Deg ;
	}
}
