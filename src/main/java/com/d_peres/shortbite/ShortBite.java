package com.d_peres.shortbite;

public class ShortBite {
	
	static {
		System.loadLibrary("shortbite");
	}
	
	private static native int byte_short(byte[] in, short[] out);
	private static native int short_byte(short[] in, byte[] out);
	
	public static int byteShort(byte[] in, short[] out) {
		return byte_short(in, out);
	}
	
	public static int shortByte(short[] in, byte[] out) {
		return short_byte(in, out);
	}
}
