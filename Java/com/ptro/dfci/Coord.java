package com.ptro.dfci;

public class Coord {
	private		LatLng			latLng;
	private		LambertII		lambertII;
	
	public Coord(LatLng latLng, LambertII lambertII) {
		super();
		this.latLng = latLng;
		this.lambertII = lambertII;
	}

	public LatLng getLatLng() {
		return latLng;
	}

	public LambertII getLambertII() {
		return lambertII;
	}
	
	
}
