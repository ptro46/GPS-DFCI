package com.ptro.dfci;

public class SubString {
	public static String subString(String s, int from, int length) {
		
		if ( from+length < s.length() ) {
			return s.substring(from, from+length);
		}
		return s.substring(from);
	}
}
