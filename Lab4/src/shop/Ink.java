package shop;

import java.io.FileInputStream;
import java.io.IOException;

public class Ink extends Cartridge
{
	protected int ml = 0;
	protected boolean refilled = false;
	
	public Ink( ) { super(); }
	public Ink(String n) { super(n); }
	public Ink(String n, boolean s) { super(n, s); }
	public Ink(String n, String p) { super(n, p); }
	
	public void setML(int ml) { this.ml = ml; }
	public void refill( ) { refilled = true; }
	
	public int getML() { return ml; }
	public boolean isRefilled() { return refilled; }
	
	@Override
	public boolean equals(Object o)
	{
		if(super.equals(o) && o instanceof Ink)
		{
			Ink i = (Ink) o;
			return ml == i.ml && refilled == i.refilled;
		}
		
		return false;
	}
	
	@Override
	public String toString()
	{
		StringBuilder s = new StringBuilder();
		
		s.append(super.toString()).append('\n');
		s.append("contains ").append(ml).append("ml ink and is ");
		if(!refilled) s.append("not ");
		s.append("refilled.");
		
		return s.toString();
	}
	
	@Override
	public String output()
	{
		return super.output() + ml + DELIM + refilled + "\n";
	}
	
	@Override
	public void readFromFile(FileInputStream fis) throws IOException
	{
		super.readFromFile(fis);
		String[] e = Utils.getline(fis).split("\\" + DELIM);
		ml = Integer.parseInt(e[0]);
		refilled = Boolean.parseBoolean(e[1]);
	}
}
