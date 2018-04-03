package com.ptro.dfci;

public class ZoneChasseSecteur1 extends CarreDFCI {
	
	public		int			numeroZone;
	
	public		Coord		coordSO;
	public		Coord		coordNO;
	public		Coord		coordNE;
	public		Coord		coordSEIntermediaire1;
	public		Coord		coordSEIntermediaire2;
	public		Coord		coordSEIntermediaire3;
	public		Coord		coordSE;
	public		Coord		coordCentre;
	
	public		Carre2Km	carre2Km;

	public ZoneChasseSecteur1(int numeroZone, Carre2Km carre2Km, LambertII lambert) {
		this.carre2Km = carre2Km ;
		this.numeroZone = numeroZone;
		
		{
			LambertII lambertIISO = new LambertII(lambert.getX() , 
					  							  lambert.getY() + 1000);
			LatLng latLngSO = latLngFromLambertII(lambertIISO);
			coordSO = new Coord(latLngSO, lambertIISO);
		}
		
		{
			LambertII lambertIISE = new LambertII(lambert.getX() + 1000, 
												  lambert.getY() + 1000);
			LatLng latLngSE = latLngFromLambertII(lambertIISE);
			coordSE = new Coord(latLngSE, lambertIISE);
		}

		{
			LambertII lambertIINE = new LambertII(lambert.getX() + 1000, 
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
			LambertII lambertIISE = new LambertII(lambert.getX() + 1000, 
												  lambert.getY() + 1500);
			LatLng latLngSE = latLngFromLambertII(lambertIISE);
			coordSEIntermediaire1 = new Coord(latLngSE, lambertIISE);
		}

		{
			LambertII lambertIISE = new LambertII(lambert.getX() + 500, 
												  lambert.getY() + 1500);
			LatLng latLngSE = latLngFromLambertII(lambertIISE);
			coordSEIntermediaire2 = new Coord(latLngSE, lambertIISE);
			
			coordCentre = new Coord(latLngSE, lambertIISE);
		}

		{
			LambertII lambertIISE = new LambertII(lambert.getX() + 500, 
												  lambert.getY() + 1000);
			LatLng latLngSE = latLngFromLambertII(lambertIISE);
			coordSEIntermediaire3 = new Coord(latLngSE, lambertIISE);
		}
	}
	
}
