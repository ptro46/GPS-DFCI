package com.ptro.dfci;

public class ZoneChasseSecteur4 extends CarreDFCI {

	public		int			numeroZone;
	
	public		Coord		coordSO;
	public		Coord		coordNO;
	public		Coord		coordNEIntermediaire1;
	public		Coord		coordNEIntermediaire2;
	public		Coord		coordNEIntermediaire3;
	public		Coord		coordNE;
	public		Coord		coordSE;
	public		Coord		coordCentre;
	
	public		Carre2Km	carre2Km;

	public ZoneChasseSecteur4(int numeroZone, Carre2Km carre2Km, LambertII lambert) {
		{
			LambertII lambertIISO = new LambertII(lambert.getX() , 
					  							  lambert.getY() );
			LatLng latLngSO = latLngFromLambertII(lambertIISO);
			coordSO = new Coord(latLngSO, lambertIISO);
		}
		
		{
			LambertII lambertIISE = new LambertII(lambert.getX() + 1000, 
												  lambert.getY() );
			LatLng latLngSE = latLngFromLambertII(lambertIISE);
			coordSE = new Coord(latLngSE, lambertIISE);
		}

		{
			LambertII lambertIINE = new LambertII(lambert.getX() + 1000, 
												  lambert.getY() + 1000);
			LatLng latLngNE = latLngFromLambertII(lambertIINE);
			coordNE = new Coord(latLngNE, lambertIINE);
		}

		{
			LambertII lambertIINO = new LambertII(lambert.getX() , 
												  lambert.getY() + 1000);
			LatLng latLngNO = latLngFromLambertII(lambertIINO);
			coordNO = new Coord(latLngNO, lambertIINO);
		}

		{
			LambertII lambertIISE = new LambertII(lambert.getX() + 500, 
												  lambert.getY() + 1000);
			LatLng latLngSE = latLngFromLambertII(lambertIISE);
			coordNEIntermediaire1 = new Coord(latLngSE, lambertIISE);
		}

		{
			LambertII lambertIISE = new LambertII(lambert.getX() + 500, 
												  lambert.getY() + 500);
			LatLng latLngSE = latLngFromLambertII(lambertIISE);
			coordNEIntermediaire2 = new Coord(latLngSE, lambertIISE);
			
			coordCentre = new Coord(latLngSE, lambertIISE);
		}

		{
			LambertII lambertIISE = new LambertII(lambert.getX() + 1000, 
												  lambert.getY() + 500);
			LatLng latLngSE = latLngFromLambertII(lambertIISE);
			coordNEIntermediaire3 = new Coord(latLngSE, lambertIISE);
		}
	}
}
