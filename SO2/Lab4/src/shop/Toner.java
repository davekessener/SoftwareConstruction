package shop;

import java.io.FileInputStream;
import java.io.IOException;

public class Toner extends Cartridge
{
	protected int capacity = 0, type = 0;
	
	public Toner( ) { super(); }
	public Toner(String n) { super(n); }
	public Toner(String n, boolean s) { super(n, s); }
	public Toner(String n, String p) { super(n, p); }
	
	public void setCapacity(int c) { capacity = c; }
	public void setType(int t) { if(t >= 0 && t < Type.values().length) type = t; }
	
	public int getCapacity() { return capacity; }
	public int getType() { return type; }
	
	@Override
	public boolean equals(Object o)
	{
		if(super.equals(o) && o instanceof Toner)
		{
			Toner t = (Toner) o;
			return capacity == t.capacity && type == t.type;
		}
		
		return false;
	}
	
	@Override
	public String toString()
	{
		StringBuilder s = new StringBuilder();
		
		s.append(super.toString()).append('\n');
		s.append("capacity = ").append(capacity)
		 .append("\ttype = ").append(Type.values()[type].toString());
		
		return s.toString();
	}
	
	@Override
	public String output()
	{
		return super.output() + capacity + DELIM + type + "\n";
	}
	
	@Override
	public void readFromFile(FileInputStream fis) throws IOException
	{
		super.readFromFile(fis);
		String[] e = Utils.getline(fis).split(DELIM);
		capacity = Integer.parseInt(e[0]);
		type = Integer.parseInt(e[1]);
	}
	
	protected static enum Type
	{
		ORIGINAL,
		OTHER,
		REFILLED
	}
}
