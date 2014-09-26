package shop;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public abstract class Cartridge
{
	protected String name;
	protected float price;
	protected String[] printers;
	protected String[] colors;
	
	public Cartridge( ) { this("", null); }
	public Cartridge(String n) { this(n, null); }
	public Cartridge(String n, boolean s) { this(n, s ? n : null); }
	public Cartridge(String n, String p)
	{
		setName(n);
		printers = new String[0];
		colors = new String[0];
		if(p != null) addPrinter(p);
	}
	
	@Override
	public String toString()
	{
		StringBuilder s = new StringBuilder();
		
		s.append(name).append("\tprice = ").append(price).append("Eur\n");
		s.append("for printers: ").append(Utils.join(printers, ", ")).append('\n');
		s.append("colors: ").append(Utils.join(colors, ", "));
		
		return s.toString();
	}
		
	protected String output()
	{
		StringBuilder s = new StringBuilder();
		
		s.append(name).append(DELIM)
		 .append(price).append(DELIM)
		 .append(printers.length).append(DELIM)
		 .append(colors.length).append('\n');
		
		if(printers.length > 0) s.append(Utils.join(printers, DELIM)).append('\n');
		if(colors.length > 0) s.append(Utils.join(colors, DELIM)).append('\n');
		
		return s.toString();
	}
	
	@Override
	public int hashCode()
	{
		return name.hashCode();
	}
	
	@Override
	public boolean equals(Object o)
	{
		if(o == null) return false;
		if(o == this) return true;
		if(o instanceof Cartridge)
		{
			Cartridge c = (Cartridge) o;
			
			return name.equals(c.name) && price == c.price && 
					Utils.arrEqual(printers, c.printers) && Utils.arrEqual(colors, c.colors);
		}
		
		return false;
	}
	
	public void addPrinter(String p)
	{
		if(!Utils.contains(printers, p)) printers = Utils.addArr(printers, p);
	}
	
	public void addColor(String c)
	{
		if(Utils.contains(PrintColorAndType.COLOR.values(), c) && 
				!Utils.contains(colors, c)) colors = Utils.addArr(colors, c);
	}
	
	public void writeToFile(FileOutputStream fos) throws IOException
	{
		fos.write(output().getBytes());
		fos.flush();
	}
	
	public void readFromFile(FileInputStream fis) throws IOException
	{
		String[] l0 = Utils.getline(fis).split("\\" + DELIM);
		name = l0[0];
		price = Float.parseFloat(l0[1]);
		printers = new String[Integer.parseInt(l0[2])];
		colors = new String[Integer.parseInt(l0[3])];
		
		if(printers.length > 0)
		{
			printers = Utils.getline(fis).split("\\" + DELIM);
		}
		if(colors.length > 0)
		{
			colors = Utils.getline(fis).split("\\" + DELIM);
		}
	}
	
	public void setName(String n) { name = n; }
	public void setPrice(float p) { price = p; }

	public String getName( ) { return name; }
	public float getPrice( ) { return price; }
	
	protected static final String DELIM = "!";
}
