package com.ptro.dfci;

public class LatLng {
	private		double		latitude;
	private		double		longitude;
	private		LambertII	cachedLambertII;
	private		String		cachedDFCI;
	
	public LatLng(double latitude, double longitude) {
		super();
		this.latitude = latitude;
		this.longitude = longitude;
		this.cachedLambertII = null ;
		this.cachedDFCI = null ;
	}

	public double getLatitude() {
		return latitude;
	}

	public double getLongitude() {
		return longitude;
	}
	
	public LambertII	getLambertII() {
		if ( cachedLambertII != null ) {
			return cachedLambertII;
		}
		
	    double x;
	    double y;
	    
	    // conversion en radians de lat et lng
	    double lambda_w = longitude * Math.PI /180;
	    double phi_w = latitude * Math.PI /180;
	    
	    // conversion WGS84 géographiques > WGS84 cartésiennes
	    // d'après formules du document de l'IGN NTG_80
	    // constantes
	    double a_w = 6378137.0; 	// demi grand axe système WGS84
	    double b_w = 6356752.314;	// demi petit axe système WGS84
	    
	    //  calcul de la première excentricité dans le système WGS84
	    double e2_w = ((a_w*a_w) - (b_w*b_w)) / (a_w*a_w);
	    
	    // calcul de la grande normale de l'ellipsoide WGS84
	    double N = a_w / Math.sqrt(1 - e2_w * Math.pow(Math.sin(phi_w),2));
	    
	    // calcul des coordonnées X,Y,Z dans le système WGS84
	    double X_w = N * Math.cos(phi_w) * Math.cos(lambda_w);
	    double Y_w = N * Math.cos(phi_w) * Math.sin(lambda_w);
	    double Z_w = N * (1-e2_w) * Math.sin(phi_w);
	    
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
	    double e2_n = (Math.pow(a_n,2)- Math.pow(b_n,2)) / (Math.pow(a_n,2));
	    // on définit une tolérance de convergence
	    double epsilon = Math.pow(10,-10);
	    // boucle de calcul
	    double p0 = Math.atan(Z_n/Math.sqrt(X_n*X_n+Y_n*Y_n)*(1-(a_n*e2_n)/(Math.sqrt(X_n*X_n+Y_n*Y_n+Z_n*Z_n))));
	    double p1 = Math.atan((Z_n/Math.sqrt(X_n*X_n+Y_n*Y_n))/(1-(a_n*e2_n*Math.cos(p0))/(Math.sqrt((X_n*X_n+Y_n*Y_n)*(1-e2_n*Math.pow(Math.sin(p0),2))))));
	    
	    while(!(Math.abs(p1-p0)<epsilon)){
	        p0 = p1;
	        p1 = Math.atan((Z_n/Math.sqrt(X_n*X_n+Y_n*Y_n))/(1-(a_n*e2_n*Math.cos(p0))/(Math.sqrt((X_n*X_n+Y_n*Y_n)*(1-e2_n*Math.pow(Math.sin(p0),2))))));
	    }
	    
	    double phi_n = p1;
	    double lambda_n = Math.atan(Y_n/X_n);
	    
	    // conversion NTF géographiques -> Lambert II étendu
	    // constantes Lambert 2 étendu
	    double n = 0.7289686274;
	    double c = 11745793.39;
	    double Xs = 600000.0;
	    double Ys = 8199695.768;
	    double lambda0 = 0.04079234433198;   //correspond à la longitude en radian de Paris (2°20'14.025" E) par rapport à Greenwich
	    // excentricité de l'éllipsoïde
	    double e_n = Math.sqrt(e2_n);
	    // calcul de la latitude isométrique
	    double L = Math.log(Math.tan(Math.PI/4 + phi_n/2) * Math.pow(((1-e_n*Math.sin(phi_n))/(1+e_n*Math.sin(phi_n))),(e_n/2)));
	    // projection
	    double X_l2e = Xs + c*Math.exp((-n*L))*Math.sin(n*(lambda_n-lambda0));
	    double Y_l2e = Ys - c*Math.exp((-n*L))*Math.cos(n*(lambda_n-lambda0));
	    
	    x = Math.round(X_l2e*1000)/1000;
	    y = Math.round(Y_l2e*1000)/1000;
	    
	    cachedLambertII = new LambertII(x, y);

		return cachedLambertII ;
	}

	public String dfci() {
		if ( cachedDFCI != null ) {
			return cachedDFCI ;
		}
		
		String ABC = "ABCDEFGHKLMN012345678902468";
		StringBuffer sb = new StringBuffer();
		
		if ( cachedLambertII == null ) {
			getLambertII();
		}
		
		double x = Math.round(cachedLambertII.getX());
		double y = Math.round(cachedLambertII.getY());
		
	    if (x<=0 || x>=1200000 || y<=1600000 || y>=2700000) {
	        return sb.toString() ;
	        
	    } else {
	        // on ramène l'origine au sud de la Corse à zero
	        y -= 1600000;
	        
	        // carré 100*100 km
	        double X100 = Math.floor(x/100000);
	        double Y100 = Math.floor(y/100000);
	        
	        sb.append(ABC.charAt((int)X100));
	        sb.append(ABC.charAt(((int)Y100)+1));
	        	        
	        // carré 20*20 km
	        double Xtot =  x-(X100*100000);
	        double Ytot =  y-(Y100*100000);
	        double X20 = Math.floor(Xtot/20000);
	        double Y20 = Math.floor(Ytot/20000);
	        
	        sb.append(ABC.charAt(((int)X20)+22));
	        sb.append(ABC.charAt(((int)Y20)+22));

	        // carré 2*2 km
	        Xtot -= (X20*20000);
	        Ytot -= (Y20*20000);
	        double X2 = Math.floor(Xtot/2000);
	        double Y2 = Math.floor(Ytot/2000);
	        
	        sb.append(ABC.charAt(((int)X2)+0));
	        sb.append(ABC.charAt(((int)Y2)+12));
	        
	        // découpage "chasse" en 5 zones
	        Xtot -= (X2*2000);
	        Ytot -= (Y2*2000);
	        
	        char Xc='\0';
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
	        
	        sb.append(".");
	        sb.append(""+Xc);
	        
	        cachedDFCI = sb.toString() ;
	    }
	    

		
		return cachedDFCI ;
	}
}
