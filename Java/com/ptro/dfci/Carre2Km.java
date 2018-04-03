package com.ptro.dfci;

import static com.ptro.dfci.SubString.subString;

public class Carre2Km extends CarreDFCI {
	private		String				nomDFCIComplet;
	private		String				nomDFCICarre2Km;
	private		Coord				coordCentre;
	private		Coord				coordSO;
	private		Coord				coordNO;
	private		Coord				coordNE;
	private		Coord				coordSE;
	
	private		ZoneChasseSecteur1	secteur1;
	private		ZoneChasseSecteur2	secteur2;
	private		ZoneChasseSecteur3	secteur3;
	private		ZoneChasseSecteur4	secteur4;
	private		ZoneChasseSecteur5	secteur5;
	
	private		Carre100Km			carre20Km;

	public Carre2Km(String dfci, Carre20Km carre20Km) {
		nomDFCIComplet = dfci ;
		nomDFCICarre2Km = subString(dfci, 4, 2);
		
		String dfci2Km = subString(dfci, 0, 6) + ".4";
		
		LambertII lambert = lambertIIFromDFCI(dfci2Km);
		LatLng latLng = latLngFromLambertII(lambert);
		coordSO = new Coord(latLng, lambert);
		
		{
			LambertII lambertIISE = new LambertII(lambert.getX() + 2000, 
												  lambert.getY());
			LatLng latLngSE = latLngFromLambertII(lambertIISE);
			coordSE = new Coord(latLngSE, lambertIISE);
		}

		{
			LambertII lambertIINE = new LambertII(lambert.getX() + 2000, 
												  lambert.getY() + 2000);
			LatLng latLngNE = latLngFromLambertII(lambertIINE);
			coordNE = new Coord(latLngNE, lambertIINE);
		}

		{
			LambertII lambertIINO = new LambertII(lambert.getX() , 
												  lambert.getY() + 2000);
			LatLng latLngNO = latLngFromLambertII(lambertIINO);
			coordNO = new Coord(latLngNO, lambertIINO);
		}

		{
			LambertII lambertIICentre = new LambertII(lambert.getX() + 1000, 
												  	  lambert.getY() + 1000);
			LatLng latLngCentre = latLngFromLambertII(lambertIICentre);
			coordCentre = new Coord(latLngCentre, lambertIICentre);
		}
		
		secteur1 = new ZoneChasseSecteur1(1, this, lambert);
		secteur2 = new ZoneChasseSecteur2(1, this, lambert);
		secteur3 = new ZoneChasseSecteur3(1, this, lambert);
		secteur4 = new ZoneChasseSecteur4(1, this, lambert);
		secteur5 = new ZoneChasseSecteur5(1, this, lambert);
	}
	
	public void dumpWithIndentLevel(int indentLevel) {
		System.out.printf("%sCarre2Km {\n",indentWithIndentLevel(indentLevel));
		System.out.printf("%s    dfci : %s\n",indentWithIndentLevel(indentLevel),nomDFCICarre2Km);
		dumpCoordWithPrompt(coordCentre, "coordCentre", indentLevel+2);
		dumpCoordWithPrompt(coordSO, "coordSO", indentLevel+2);
		dumpCoordWithPrompt(coordNO, "coordNO", indentLevel+2);
		dumpCoordWithPrompt(coordNE, "coordNE", indentLevel+2);
		dumpCoordWithPrompt(coordSE, "coordSE", indentLevel+2);
		
		System.out.printf("%s        secteur1 {\n",indentWithIndentLevel(indentLevel));
		dumpCoordWithPrompt(secteur1.coordSO, "coordSO", indentLevel+3);
		dumpCoordWithPrompt(secteur1.coordNO, "coordNO", indentLevel+3);
		dumpCoordWithPrompt(secteur1.coordNE, "coordNE", indentLevel+3);
		dumpCoordWithPrompt(secteur1.coordSEIntermediaire1, "coordSEIntermediaire1", indentLevel+3);
		dumpCoordWithPrompt(secteur1.coordSEIntermediaire2, "coordSEIntermediaire2", indentLevel+3);
		dumpCoordWithPrompt(secteur1.coordSEIntermediaire3, "coordSEIntermediaire3", indentLevel+3);
		dumpCoordWithPrompt(secteur1.coordSE, "coordSE", indentLevel+3);
		dumpCoordWithPrompt(secteur1.coordCentre, "coordCentre", indentLevel+3);
		System.out.printf("%s        }\n",indentWithIndentLevel(indentLevel));
		
		System.out.printf("%s        secteur2 {\n",indentWithIndentLevel(indentLevel));
		dumpCoordWithPrompt(secteur2.coordSO, "coordSO", indentLevel+3);
		dumpCoordWithPrompt(secteur2.coordSOIntermediaire1, "coordSOIntermediaire1", indentLevel+3);
		dumpCoordWithPrompt(secteur2.coordSOIntermediaire2, "coordSOIntermediaire2", indentLevel+3);
		dumpCoordWithPrompt(secteur2.coordSOIntermediaire3, "coordSOIntermediaire3", indentLevel+3);
		dumpCoordWithPrompt(secteur2.coordNO, "coordNO", indentLevel+3);
		dumpCoordWithPrompt(secteur2.coordNE, "coordNE", indentLevel+3);
		dumpCoordWithPrompt(secteur2.coordSE, "coordSE", indentLevel+3);
		dumpCoordWithPrompt(secteur2.coordCentre, "coordCentre", indentLevel+3);
		System.out.printf("%s        }\n",indentWithIndentLevel(indentLevel));

		System.out.printf("%s        secteur3 {\n",indentWithIndentLevel(indentLevel));
		dumpCoordWithPrompt(secteur3.coordSO, "coordSO", indentLevel+3);
		dumpCoordWithPrompt(secteur3.coordNOIntermediaire1, "coordNOIntermediaire1", indentLevel+3);
		dumpCoordWithPrompt(secteur3.coordNOIntermediaire2, "coordNOIntermediaire2", indentLevel+3);
		dumpCoordWithPrompt(secteur3.coordNOIntermediaire3, "coordNOIntermediaire3", indentLevel+3);
		dumpCoordWithPrompt(secteur3.coordNO, "coordNO", indentLevel+3);
		dumpCoordWithPrompt(secteur3.coordNE, "coordNE", indentLevel+3);
		dumpCoordWithPrompt(secteur3.coordSE, "coordSE", indentLevel+3);
		dumpCoordWithPrompt(secteur3.coordCentre, "coordCentre", indentLevel+3);
		System.out.printf("%s        }\n",indentWithIndentLevel(indentLevel));

		System.out.printf("%s        secteur4 {\n",indentWithIndentLevel(indentLevel));
		dumpCoordWithPrompt(secteur4.coordSO, "coordSO", indentLevel+3);
		dumpCoordWithPrompt(secteur4.coordNO, "coordNO", indentLevel+3);
		dumpCoordWithPrompt(secteur4.coordNEIntermediaire1, "coordNEIntermediaire1", indentLevel+3);
		dumpCoordWithPrompt(secteur4.coordNEIntermediaire2, "coordNEIntermediaire2", indentLevel+3);
		dumpCoordWithPrompt(secteur4.coordNEIntermediaire3, "coordNEIntermediaire3", indentLevel+3);
		dumpCoordWithPrompt(secteur4.coordNE, "coordNE", indentLevel+3);
		dumpCoordWithPrompt(secteur4.coordSE, "coordSE", indentLevel+3);
		dumpCoordWithPrompt(secteur4.coordCentre, "coordCentre", indentLevel+3);
		System.out.printf("%s        }\n",indentWithIndentLevel(indentLevel));

		System.out.printf("%s        secteur5 {\n",indentWithIndentLevel(indentLevel));
		dumpCoordWithPrompt(secteur5.coordSO, "coordSO", indentLevel+3);
		dumpCoordWithPrompt(secteur5.coordNO, "coordNO", indentLevel+3);
		dumpCoordWithPrompt(secteur5.coordNE, "coordNE", indentLevel+3);
		dumpCoordWithPrompt(secteur5.coordSE, "coordSE", indentLevel+3);
		dumpCoordWithPrompt(secteur5.coordCentre, "coordCentre", indentLevel+3);
		System.out.printf("%s        }\n",indentWithIndentLevel(indentLevel));

		System.out.printf("%s}\n",indentWithIndentLevel(indentLevel));
	}
}
