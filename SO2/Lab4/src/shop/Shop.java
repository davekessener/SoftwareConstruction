package shop;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class Shop
{
	protected String name;
	protected float value;
	protected Ink[] inks;
	protected Toner[] toners;
	
	public Shop( ) { this(""); }
	public Shop(String n)
	{
		name = n;
		value = 0.0f;
		inks = new Ink[0];
		toners = new Toner[0];
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
		if(o instanceof Shop)
		{
			Shop s = (Shop) o;
			return name.equals(s.name) && value == s.value && 
					Utils.arrEqual(inks, s.inks) && Utils.arrEqual(toners, s.toners);
		}
		
		return false;
	}
	
	@Override
	public String toString()
	{
		StringBuilder s = new StringBuilder();
		
		s.append("Shopper '").append(name).append("': total = ").append(value).append("Eur\n");
		s.append("Items:\n").append(Utils.join(inks, "\n")).append('\n').append(Utils.join(toners, "\n"));
		
		return s.toString();
	}
	
	public String output()
	{
		StringBuilder s = new StringBuilder();
		
		s.append(name).append('\n');
		s.append(value).append('\n');
		s.append(inks.length).append('\n');
		for(Ink i : inks)
		{
			s.append(i.output());
		}
		s.append(toners.length).append('\n');
		for(Toner t : toners)
		{
			s.append(t.output());
		}
		
		return s.toString();
	}
	
	public void writeToFile(FileOutputStream fos) throws IOException
	{
		fos.write(output().getBytes());
		fos.flush();
	}
	
	public void readFromFile(FileInputStream fis) throws IOException
	{
		name = Utils.getline(fis);
		value = Float.parseFloat(Utils.getline(fis));
		inks = new Ink[Integer.parseInt(Utils.getline(fis))];
		for(int i = 0 ; i < inks.length ; ++i)
		{
			inks[i] = new Ink();
			inks[i].readFromFile(fis);
		}
		toners = new Toner[Integer.parseInt(Utils.getline(fis))];
		for(int i = 0 ; i < toners.length ; ++i)
		{
			toners[i] = new Toner();
			toners[i].readFromFile(fis);
		}
	}
	
	public void addCartridge(Cartridge c)
	{
		if(c instanceof Ink) addInk((Ink) c);
		else if(c instanceof Toner) addToner((Toner) c);
	}
	
	public void addInk(Ink ink)
	{
		inks = Utils.copyArr(new Ink[inks.length + 1], inks);
		inks[inks.length - 1] = ink;
		
		value += ink.getPrice();
	}
	
	public void addToner(Toner toner)
	{
		toners = Utils.copyArr(new Toner[toners.length + 1], toners);
		toners[toners.length - 1] = toner;
		
		value += toner.getPrice();
	}
}
