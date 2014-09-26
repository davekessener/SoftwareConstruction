package shop;

import java.io.FileInputStream;
import java.io.IOException;

public final class Utils
{
	public static String getline(FileInputStream fis) throws IOException
	{
		int i = 0;
		byte[] r = new byte[0];
		
		int t;
		while((t = fis.read()) != -1 && t != '\n')
		{
			if(r.length == i)
			{
				byte[] tb = new byte[2 * r.length + 1];
				for(int j = 0 ; j < r.length ; ++j) tb[j] = r[j];
				r = tb;
			}
			
			r[i++] = (byte) t;
		}
		
		if(r.length == i) return new String(r);
		
		byte[] tb = new byte[i];
		for(int j = 0 ; j < i ; ++j) tb[j] = r[j];
		
		return new String(tb);
	}
	
	public static <T1, T2> boolean contains(T1[] a, T2 t)
	{
		for(T1 tt : a)
		{
			if(tt.toString().equals(t.toString())) return true;
		}
		
		return false;
	}
	
	public static <T> boolean arrEqual(T[] t1, T[] t2)
	{
		if(t1 == null && t2 == null) return true;
		if(t1 == null || t2 == null) return false;
		if(t1.length != t2.length) return false;
		
		for(int i = 0 ; i < t1.length ; ++i)
		{
			if(!t1[i].equals(t2[i])) return false;
		}
		
		return true;
	}
	
	public static String[] addArr(String[] a, String s)
	{
		a = copyArr(new String[a.length + 1], a);
		a[a.length  - 1] = s;
		return a;
	}
	
	public static <T> String join(T[] t, String d)
	{
		StringBuilder s = new StringBuilder();
		boolean first = true;
		
		for(T tt : t)
		{
			if(!first) s.append(d);
			s.append(tt.toString());
			first = false;
		}
		
		return s.toString();
	}
	
	public static <T> T[] copyArr(T[] t1, T[] t2) { return copyArr(t1, t2, t1.length < t2.length ? t1.length : t2.length); }
	public static <T> T[] copyArr(T[] t1, T[] t2, int l)
	{
		for(int i = 0 ; i < l ; ++i)
		{
			t1[i] = t2[i];
		}
		
		return t1;
	}
	
	private Utils( ) { }
}
