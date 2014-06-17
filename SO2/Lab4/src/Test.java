import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

import shop.Ink;
import shop.Shop;
import shop.Toner;


public class Test
{
	public void run()
	{
		Ink i1 = new Ink("Epson 2010", true);
		i1.addPrinter("Canon 3450");
		i1.addColor("BLACK");
		i1.addColor("MAGENTA");
		i1.setPrice(34.67f);
		i1.setML(15);
		i1.refill();
		
		Ink i2 = new Ink("HP1320");
		i2.addColor("BLACK");
		i2.addColor("YELLOW");
		i2.setPrice(99.87f);
		i2.setML(45);
		
		Toner t1 = new Toner("HP413", true);
		t1.addPrinter("Canon 666");
		t1.addColor("BLACK");
		t1.addColor("MAGENTA");
		t1.setPrice(42);
		t1.setCapacity(200);
		
		Toner t2 = new Toner("Canon 2014", "JMarque 4e");
		t2.addColor("MAGENTA");
		t2.setPrice(1000);
		t2.setCapacity(1000);
		t2.setType(1);
		
		Shop s1 = new Shop("Lownly");
		s1.addCartridge(i1);
		s1.addCartridge(i2);
		s1.addCartridge(t1);
		s1.addCartridge(t2);
		
		System.out.println("###\n" + s1.toString() + "\n###\n" + s1.output() + "###");
		
		File log = new File("log.txt");
		
		try
		{
			FileOutputStream fos = new FileOutputStream(log);
			s1.writeToFile(fos);
			fos.close();
		}
		catch(IOException e)
		{
			e.printStackTrace();
			return;
		}
		
		Shop s2 = new Shop();
		
		try
		{
			FileInputStream fis = new FileInputStream(log);
			s2.readFromFile(fis);
			fis.close();
		}
		catch(IOException e)
		{
			e.printStackTrace();
			return;
		}
		
		if(s1.equals(s2))
		{
			System.out.println("Read/Write SUCCESS!");
		}
		else
		{
			System.out.println("Read/Write FAILURE: Object are not identical.");
		}
	}
}
