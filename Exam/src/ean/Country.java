package ean;

import java.io.BufferedReader;
import java.io.IOException;

public class Country implements Cloneable
{
	protected String[] myCountry;
	protected int[] code;
	
	public Country( ) { }
	public Country(BufferedReader br) throws IOException
	{
		readFromFile(br);
	}
	
	@Override
	public Object clone()
	{
		try
		{
			Country c = (Country) super.clone();
			c.myCountry = myCountry.clone();
			c.code = code.clone();
			return c;
		}
		catch(CloneNotSupportedException e)
		{
			return null;
		}
	}
	
	public void readFromFile(BufferedReader br) throws IOException
	{
		String c = "";
		while(br.ready()) c += br.readLine() + "\n"; // the the entire file
		String[] l = c.split("\n"); // split on newline
		myCountry = new String[l.length];
		code = new int[l.length];
		for(int i = 0 ; i < l.length ; ++i)
		{
			// remove leading country-code and assign name
			myCountry[i] = l[i].replaceFirst("^[^ \\t]+[ \\t]+", "");
			
			// parse country code
			code[i] = Integer.parseInt(l[i].split("[ \\t]+")[0]);
		}
	}
	
	public String getCountry(int cc)
	{
		for(int i = 0 ; i < code.length ; ++i)
		{
			if(code[i] == cc) return myCountry[i];
		}
		
		return null;
	}
}
