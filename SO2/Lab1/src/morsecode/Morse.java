package morsecode;

import java.util.HashMap;
import java.util.Map;

public class Morse
{
	private static final Map<Integer, Character> lookup;
	private static final Map<Character, Integer> rLookup;
	private final char value;
	private final int dec;
	
	public Morse(char v) throws MorseException
	{
		if(v >= 'A' && v <= 'Z') v -= 'A' - 'a';
		if(v < 'a' || v > 'z')
		{
			throw new MorseException(String.format("ERR: Invalid character '%s'"));
		}
		
		value = v;
		dec = doReverseLookup(value);
	}
	
	public Morse(String s) throws MorseException
	{
		value = (s.charAt(0) >= '0' && s.charAt(0) <= '2') ? doLookup(Integer.parseInt(s)) : fromString(s);
		dec = doReverseLookup(value);
	}
	
	public Morse(int i) throws MorseException
	{
		value = doLookup(i < 1000 ? convert(i, 3, 10) : i);
		dec = doReverseLookup(value);
	}
	
	public char getCharacter( ) { return value; }
	public int getDecimal( ) { return dec; }
	public int getTerzial( ) { return convert(dec, 10, 3); }
	public String getMorse( )
	{
		char cs[] = new char[] {'_', '.', '-'};
		int v = dec;
		
		String s = "";
		
		for(int i = 0 ; i < 4 ; ++i)
		{
			s = cs[v % 10] + s;
			v /= 10;
		}
		
		return s;
	}
	
	@Override
	public int hashCode( )
	{
		return getDecimal();
	}
	
	@Override
	public boolean equals(Object o)
	{
		if(o instanceof Morse)
		{
			return value == ((Morse) o).value;
		}
		
		return false;
	}
	
	@Override
	public String toString( )
	{
		return String.format("Morse{'%c', \"%s\"}", value, getMorse());
	}
	
	public static Morse fromCharacter(char c) throws MorseException { return new Morse(c); }
	public static Morse fromDecimal(int i) throws MorseException { return new Morse(i); }
	public static Morse fromTerzial(int i) throws MorseException { return new Morse(i); }
	public static Morse fromCode(String s) throws MorseException { return new Morse(s); }
	
	private static int convert(int i, int tb, int sb)
	{
		int r = 0;
		int c = 1;
		
		while(i > 0)
		{
			r += c * (i % tb);

			i /= tb;
			c *= 10;
		}
		
		return r;
	}
	
	private static char fromString(String s) throws MorseException 
	{
		char p[] = s.toCharArray();
		int v = 0;
		
		for(char c : p)
		{
			switch(c)
			{
			case ' ':
			case '_':
				v = 10 * v + 0;
				break;
			case '.':
				v = 10 * v + 1;
				break;
			case '-':
				v = 10 * v + 2;
				break;
			default:
				throw new MorseException(String.format("ERR: Unknown character '%c' encountered!", c));
			}
		}
		
		return doLookup(v);
	}
	
	private static char doLookup(int v) throws MorseException 
	{
		if(!lookup.containsKey(v))
		{
			throw new MorseException(String.format("ERR: Unknown value '%d' encountered!", v));
		}
		
		return lookup.get(v);
	}
	
	private static int doReverseLookup(char c) throws MorseException 
	{
		if(!rLookup.containsKey(c))
		{
			throw new MorseException(String.format("ERR: Unsupported character '%c'!", c));
		}
		
		return rLookup.get(c);
	}
	
	private static void insert(char c, int i) throws MorseException 
	{
		if(lookup.containsKey(i) || rLookup.containsKey(c))
		{
			throw new MorseException(String.format("Tried to register duplicate %c/%d!", c, i));
		}
		
		lookup.put(i, c);
		rLookup.put(c, i);
	}
	
	static
	{
		lookup = new HashMap<Integer, Character>();
		rLookup = new HashMap<Character, Integer>();
		
		try
		{
			insert('b', 2111);
			insert('a', 1200);
			insert('c', 2121);
			insert('d', 2110);
			insert('e', 1000);
			insert('f', 1121);
			insert('g', 2210);
			insert('h', 1111);
			insert('i', 1100);
			insert('j', 1222);
			insert('k', 2120);
			insert('l', 1211);
			insert('m', 2200);
			insert('n', 2100);
			insert('o', 2220);
			insert('p', 1221);
			insert('q', 2212);
			insert('r', 1210);
			insert('s', 1110);
			insert('t', 2000);
			insert('u', 1120);
			insert('v', 1112);
			insert('w', 1220);
			insert('x', 2112);
			insert('y', 2122);
			insert('z', 2211);
		}
		catch(MorseException e)
		{
			e.printStackTrace();
			System.exit(1);
		}
	}
}
