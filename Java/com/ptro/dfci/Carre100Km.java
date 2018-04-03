package com.ptro.dfci;

import java.util.ArrayList;
import static com.ptro.dfci.SubString.subString;

public class Carre100Km extends CarreDFCI {
	private		String		nomDFCIComplet;
	private		String		nomDFCICarre100Km;
	private		Coord		coordCentre;
	private		Coord		coordSO;
	private		Coord		coordNO;
	private		Coord		coordNE;
	private		Coord		coordSE;
	
	private		ArrayList<Carre20Km>	matriceCarres20Km;
	
	public Carre100Km(String dfci) {
		nomDFCIComplet = dfci ;
		nomDFCICarre100Km = subString(dfci, 0, 2);
		
		String dfci100Km = nomDFCICarre100Km + "00A0.4";
		
		LambertII lambert = lambertIIFromDFCI(dfci100Km);
		LatLng latLng = latLngFromLambertII(lambert);
		coordSO = new Coord(latLng, lambert);
		
		{
			LambertII lambertIISE = new LambertII(lambert.getX() + 100000, 
												  lambert.getY());
			LatLng latLngSE = latLngFromLambertII(lambertIISE);
			coordSE = new Coord(latLngSE, lambertIISE);
		}

		{
			LambertII lambertIINE = new LambertII(lambert.getX() + 100000, 
												  lambert.getY() + 100000);
			LatLng latLngNE = latLngFromLambertII(lambertIINE);
			coordNE = new Coord(latLngNE, lambertIINE);
		}

		{
			LambertII lambertIINO = new LambertII(lambert.getX() , 
												  lambert.getY() + 100000);
			LatLng latLngNO = latLngFromLambertII(lambertIINO);
			coordNO = new Coord(latLngNO, lambertIINO);
		}

		{
			LambertII lambertIICentre = new LambertII(lambert.getX() + 50000, 
												  	  lambert.getY() + 50000);
			LatLng latLngCentre = latLngFromLambertII(lambertIICentre);
			coordCentre = new Coord(latLngCentre, lambertIICentre);
		}

		matriceCarres20Km = null ;
	}
	
	public void performDetails() {
		Carre20Km carre20Km ;
		
		if ( matriceCarres20Km == null ) {
			matriceCarres20Km = new ArrayList<Carre20Km>();
			String LambertX = "02468";
			String LambertY = "02468";
			
	        for(int x=0; x<5; x++) {
	            for(int y=0; y<5;y++) {
	            	String dfci = nomDFCICarre100Km + LambertX.charAt(x) + LambertY.charAt(y);
	                carre20Km = new Carre20Km(dfci,this);
	                matriceCarres20Km.add(carre20Km);
	            }
	        }

	        for(Carre20Km c20Km : matriceCarres20Km) {
	        	c20Km.performDetails();
	        }
		}
	}
	
	public Carre20Km carre20Km(int x, int y) {
		Carre20Km carre20Km ;
		
		performDetails();
		
		carre20Km = matriceCarres20Km.get(x*5+y);
		
		return carre20Km;
	}
	
	public void dumpWithIndentLevel(int indentLevel) {
		System.out.printf("%sCarre100Km {\n",indentWithIndentLevel(indentLevel));
		System.out.printf("%s    dfci : %s\n",indentWithIndentLevel(indentLevel),nomDFCICarre100Km);
		dumpCoordWithPrompt(coordCentre, "coordCentre", indentLevel+2);
		dumpCoordWithPrompt(coordSO, "coordSO", indentLevel+2);
		dumpCoordWithPrompt(coordNO, "coordNO", indentLevel+2);
		dumpCoordWithPrompt(coordNE, "coordNE", indentLevel+2);
		dumpCoordWithPrompt(coordSE, "coordSE", indentLevel+2);
		if ( matriceCarres20Km != null ) {
	        for(Carre20Km c20Km : matriceCarres20Km) {
	        	c20Km.dumpWithIndentLevel(indentLevel+1);
	        }
		}
		System.out.printf("%s}\n",indentWithIndentLevel(indentLevel));
	}
	
}
