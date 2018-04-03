package com.ptro;

import com.ptro.dfci.Carre100Km;
import com.ptro.dfci.Carre20Km;
import com.ptro.dfci.Carre2Km;
import com.ptro.dfci.LatLng;

public class Main {

	public static void main(String[] args) {
		
		double lat=44.671123;
	    double lng=1.277227;

	    LatLng latLng = new LatLng(lat, lng);
	    
	    System.out.println("DFCI " + latLng.dfci());
		
		Carre2Km carre2Km = new Carre2Km("FE06H2",null);
		Carre20Km carre20Km = new Carre20Km("FE06H2",null);
		Carre100Km carre100Km = new Carre100Km("FE06H2");
		
		carre20Km.performDetails();
		carre100Km.performDetails();

		carre2Km.dumpWithIndentLevel(0);
		carre20Km.dumpWithIndentLevel(0);
		carre100Km.dumpWithIndentLevel(0);

	}

}
