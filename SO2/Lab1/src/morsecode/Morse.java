package morsecode;

import java.util.HashMap;
import java.util.Map;

public class Morse
{
	public static final char MORSE_CHARACTERS[] = new char[] {'_', '.', '-'};
	private static final Map<Integer, Character> lookup;
	private static final Map<Character, Integer> rLookup;
	private final char value; // representation of morse-character as ascii-char
	private final int dec; // decimal representation
	private final int terz; // terzial representation
	private final String code; // morse-code representation
	
	public Morse(char v) throws MorseException
	{
		if(v >= 'A' && v <= 'Z') v -= 'A' - 'a'; // convert from upper- to lowercase
		if(v < 'a' || v > 'z') // if the user passed a non-alpha character
		{
			throw new MorseException(String.format("ERR: Invalid character '%c'", v));
		}
		
		value = v;
		dec = doReverseLookup(value);
		terz = convert(dec, 10, 3);
		code = getMorseCode(dec);
	}
	
	public Morse(String s) throws MorseException
	{
		s = s.replaceAll("[^0-9\\.\\-_]+", ""); // clean string from all non-morsecode characters
		
		// the passed string may either be a morse-code in the form of '..-_'
		// or an integer equal to the characters decimal or terzial representation
		if(s.charAt(0) >= '0' && s.charAt(0) <= '9')
		{
			try
			{
				// try to extract the integer
				int v = Integer.parseInt(s);
				value = doLookup(v < 1000 ? convert(v, 3, 10) : v);
			}
			catch (NumberFormatException e)
			{
				// an invalid string has been passed.
				throw new MorseException(String.format("ERR: Numerical string actually isn't one: '%s'", s));
			}
		}
		else
		{
			// reconstruct character from morse-code
			value = fromString(s);
		}

		dec = doReverseLookup(value);
		terz = convert(dec, 10, 3);
		code = getMorseCode(dec);
	}
	
	public Morse(int i) throws MorseException
	{
		// in its decimal representation all morse-characters are larger than
		// 1000, so if 'i' is smaller than 1000 it is assumed to be the characters terzial representation
		value = doLookup(i < 1000 ? convert(i, 3, 10) : i);
		dec = doReverseLookup(value);
		terz = convert(dec, 10, 3);
		code = getMorseCode(dec);
	}
	
	public char getCharacter( ) { return value; }
	public int getDecimal( ) { return dec; }
	public int getTerzial( ) { return terz; }
	public String getMorseCode( ) { return code; }

	private static String getMorseCode(int v) // reconstruct the morse-code representation of the character
	{
		String s = "";
		
		for(int i = 0 ; i < 4 ; ++i)
		{
			s = MORSE_CHARACTERS[v % 10] + s;
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
		return String.format("Morse{'%c', \"%s\", %d, %d}", value, getMorseCode(), this.dec, this.terz);
	}
	
	public static Morse fromCharacter(char c) throws MorseException { return new Morse(c); }
	public static Morse fromDecimal(int d) throws MorseException { return new Morse(d); }
	public static Morse fromTerzial(int t) throws MorseException { return new Morse(t); }
	public static Morse fromCode(String c) throws MorseException { return new Morse(c); }
	
	private static int convert(int i, int sb, int tb) // converts an integer from base 10 to base 'tb'
	// `([0-sb]+)`(10) -> (`\1`(tb))(10)
	{
		int r = 0;
		int c = 1;
		
		while(i > 0)
		{
			r += (i % sb) * c;
			c *= tb;
			i /= sb;
		}
		
		return r;
	}
	
	private static char fromString(String s) throws MorseException
	// converts a morse-code to it's character equivalent
	{
		char p[] = s.toCharArray();
		int v = 0;
	
		// iterate over every character
		for(char c : p)
		{
			for(int i = 0 ; i < MORSE_CHARACTERS.length ; ++i)
			{
				if(c == MORSE_CHARACTERS[i])
				{
					// add character value ('_' =^= 0, '.' =^= 1, '-' =^= 2)
					v = 10 * v + i;
					break;
				}

				// if the current character is not a morse-code character, throw an exception
				if(i == MORSE_CHARACTERS.length - 1)
				{
					throw new MorseException(String.format("ERR: Unknown character '%c' encountered!", c));
				}
			}
		}
		
		return doLookup(v);
	}
	
	// lookup character-representation from decimal representation
	private static char doLookup(int v) throws MorseException 
	{
		if(!lookup.containsKey(v))
		{
			throw new MorseException(String.format("ERR: Unknown value '%d' encountered!", v));
		}
		
		return lookup.get(v);
	}
	
	// lookup decimal representation from character representation
	private static int doReverseLookup(char c) throws MorseException 
	{
		if(!rLookup.containsKey(c))
		{
			throw new MorseException(String.format("ERR: Unsupported character '%c'!", c));
		}
		
		return rLookup.get(c);
	}
	
	// insert new character/integer relation into lookup-tables
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
	
		// adds all valid ascii-characters to the lookup-tables
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
