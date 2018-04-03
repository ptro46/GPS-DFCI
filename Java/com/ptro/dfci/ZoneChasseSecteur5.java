package com.ptro.dfci;

public class ZoneChasseSecteur5 extends CarreDFCI {

	public		int			numeroZone;
	
	public		Coord		coordSO;
	public		Coord		coordNO;
	public		Coord		coordNE;
	public		Coord		coordSE;
	public		Coord		coordCentre;
	
	public		Carre2Km	carre2Km;

	public ZoneChasseSecteur5(int numeroZone, Carre2Km carre2Km, LambertII lambert) {
		{
			LambertII lambertIISO = new LambertII(lambert.getX() + 500, 
					  							  lambert.getY() + 500);
			LatLng latLngSO = latLngFromLambertII(lambertIISO);
			coordSO = new Coord(latLngSO, lambertIISO);
		}
		
		{
			LambertII lambertIISE = new LambertII(lambert.getX() + 1500, 
												  lambert.getY() + 500);
			LatLng latLngSE = latLngFromLambertII(lambertIISE);
			coordSE = new Coord(latLngSE, lambertIISE);
		}

		{
			LambertII lambertIINE = new LambertII(lambert.getX() + 1500, 
												  lambert.getY() + 1500);
			LatLng latLngNE = latLngFromLambertII(lambertIINE);
			coordNE = new Coord(latLngNE, lambertIINE);
		}

		{
			LambertII lambertIINO = new LambertII(lambert.getX() + 500, 
												  lambert.getY() + 1500);
			LatLng latLngNO = latLngFromLambertII(lambertIINO);
			coordNO = new Coord(latLngNO, lambertIINO);
		}

		{
			LambertII lambertIICentre = new LambertII(lambert.getX() + 1000, 
												  lambert.getY() + 1000);
			LatLng latLngCentre = latLngFromLambertII(lambertIICentre);
			coordCentre = new Coord(latLngCentre, lambertIICentre);
		}
	}

}
