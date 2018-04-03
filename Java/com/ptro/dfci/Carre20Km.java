package com.ptro.dfci;

import java.util.ArrayList;

import static com.ptro.dfci.SubString.subString;

public class Carre20Km extends CarreDFCI {
	private		String		nomDFCIComplet;
	private		String		nomDFCICarre20Km;
	private		Coord		coordCentre;
	private		Coord		coordSO;
	private		Coord		coordNO;
	private		Coord		coordNE;
	private		Coord		coordSE;
	
	private		Carre100Km	carre100Km;

	private		ArrayList<Carre2Km>	matriceCarres2Km;
	
	public Carre20Km(String dfci, Carre100Km carre100Km) {
		nomDFCIComplet = dfci ;
		nomDFCICarre20Km = subString(dfci, 2, 2);
		
		String dfci20Km = subString(dfci, 0, 4) + "A0.4";
		
		LambertII lambert = lambertIIFromDFCI(dfci20Km);
		LatLng latLng = latLngFromLambertII(lambert);
		coordSO = new Coord(latLng, lambert);
		
		{
			LambertII lambertIISE = new LambertII(lambert.getX() + 20000, 
												  lambert.getY());
			LatLng latLngSE = latLngFromLambertII(lambertIISE);
			coordSE = new Coord(latLngSE, lambertIISE);
		}

		{
			LambertII lambertIINE = new LambertII(lambert.getX() + 20000, 
												  lambert.getY() + 20000);
			LatLng latLngNE = latLngFromLambertII(lambertIINE);
			coordNE = new Coord(latLngNE, lambertIINE);
		}

		{
			LambertII lambertIINO = new LambertII(lambert.getX() , 
												  lambert.getY() + 20000);
			LatLng latLngNO = latLngFromLambertII(lambertIINO);
			coordNO = new Coord(latLngNO, lambertIINO);
		}

		{
			LambertII lambertIICentre = new LambertII(lambert.getX() + 10000, 
												  	  lambert.getY() + 10000);
			LatLng latLngCentre = latLngFromLambertII(lambertIICentre);
			coordCentre = new Coord(latLngCentre, lambertIICentre);
		}

		matriceCarres2Km = null ;
	}
	
	public void performDetails() {
		Carre2Km carre2Km ;
		
		if ( matriceCarres2Km == null ) {
			matriceCarres2Km = new ArrayList<Carre2Km>();
			String LambertX = "ABCDEFGHKL";
			String LambertY = "0123456789";
			
	        for(int x=0; x<10; x++) {
	            for(int y=0; y<10;y++) {
	            	String dfci = subString(nomDFCIComplet, 0, 4) + LambertX.charAt(x) + LambertY.charAt(y);
	                carre2Km = new Carre2Km(dfci,this);
	                matriceCarres2Km.add(carre2Km);
	            }
	        }
		}
	}
	
	public Carre2Km carre2Km(int x, int y) {
		Carre2Km carre2Km ;
		
		performDetails();
		
		carre2Km = matriceCarres2Km.get(x*10+y);
		
		return carre2Km;
	}
	
	public void dumpWithIndentLevel(int indentLevel) {
		System.out.printf("%sCarre20Km {\n",indentWithIndentLevel(indentLevel));
		System.out.printf("%s    dfci : %s\n",indentWithIndentLevel(indentLevel),nomDFCICarre20Km);
		dumpCoordWithPrompt(coordCentre, "coordCentre", indentLevel+2);
		dumpCoordWithPrompt(coordSO, "coordSO", indentLevel+2);
		dumpCoordWithPrompt(coordNO, "coordNO", indentLevel+2);
		dumpCoordWithPrompt(coordNE, "coordNE", indentLevel+2);
		dumpCoordWithPrompt(coordSE, "coordSE", indentLevel+2);
		if ( matriceCarres2Km != null ) {
	        for(Carre2Km c2Km : matriceCarres2Km) {
	        	c2Km.dumpWithIndentLevel(indentLevel+1);
	        }
		}
		System.out.printf("%s}\n",indentWithIndentLevel(indentLevel));
	}
}
