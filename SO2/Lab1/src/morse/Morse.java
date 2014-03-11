package morse;

import java.util.HashMap;
import java.util.Map;

public class Morse
{
	private static final Map<Integer, Character> lookup;
	private static final Map<Character, Integer> rLookup;
	private final char value;
	
	public Morse(char v)
	{
		value = v;
	}
	
	public Morse(String s)
	{
		value = (s.charAt(0) >= '0' && s.charAt(0) <= '2') ? doLookup(Integer.parseInt(s)) : fromString(s);
	}
	
	public Morse(int i)
	{
		value = doLookup(i < 1000 ? convert(i, 3, 10) : i);
	}
	
	public char getCharacter( ) { return value; }
	public int getDecimal( ) { return doReverseLookup(value); }
	public int getTerzial( ) { return convert(doReverseLookup(value), 10, 3); }
	public String getMorse( )
	{
		char cs[] = new char[] {'_', '.', '-'};
		int v = doReverseLookup(value);
		
		String s = "";
		
		for(int i = 0 ; i < 4 ; ++i)
		{
			s = cs[v % 10] + s;
			v /= 10;
		}
		
		return s;
	}
	
	public static Morse fromCharacter(char c) { return new Morse(c); }
	public static Morse fromDecimal(int i) { return new Morse(i); }
	public static Morse fromTerzial(int i) { return new Morse(i); }
	public static Morse fromCode(String s) { return new Morse(s); }
	
	private static int convert(int _i, int sb, int tb)
	{
		int r = 0;
		int i = _i;
		
		while(i > 0)
		{
			if((i % sb) >= tb)
			{
				throw new RuntimeException(
						String.format("'%d' cannot be converted from base %d to base %d", _i, sb, tb));
			}

			r = r * tb + (i % sb);
			i /= sb;
		}
		
		return r;
	}
	
	private static char fromString(String s)
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
				throw new RuntimeException(String.format("ERR: Unknown character '%c' encountered!", c));
			}
		}
		
		return doLookup(v);
	}
	
	private static char doLookup(int v)
	{
		if(!lookup.containsKey(v))
		{
			throw new RuntimeException(String.format("ERR: Unknown value '%d' encontered!", v));
		}
		
		return lookup.get(v);
	}
	
	private static int doReverseLookup(char c)
	{
		if(!rLookup.containsKey(c))
		{
			throw new RuntimeException(String.format("ERR: Unsupported character '%c'!", c));
		}
		
		return rLookup.get(c);
	}
	
	private static void insert(char c, int i)
	{
		if(lookup.containsKey(i) || rLookup.containsKey(c))
		{
			throw new RuntimeException(String.format("Tried to register duplicate %c/%d!", c, i));
		}
		
		lookup.put(i, c);
		rLookup.put(c, i);
	}
	
	static
	{
		lookup = new HashMap<Integer, Character>();
		rLookup = new HashMap<Character, Integer>();
		
		insert('a', 1200);
		insert('b', 2111);
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
}
