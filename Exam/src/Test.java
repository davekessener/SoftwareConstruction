
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

import ean.BarCode;
import ean.Country;
import ean.Pallet;
import ean.Product;

public class Test
{
	public void test() throws FileNotFoundException, IOException
	{
		// Using only one object each.
		Country c = new Country();
		BarCode bc = new BarCode();
		Product p = new Product();
		Pallet pal = new Pallet();
		
		c.readFromFile(new BufferedReader(new FileReader(PATH)));
		bc.setCountry(c);
		
		// Set test parameters
		bc.setBarcode(0000000000000l);
		pal.setName("test pallet");
		pal.setBarcode(bc);
		
		// test 'book'
		bc.setBarcode(9780672324154l);
		p.setName("book");
		p.setPrice(25.7f);
		p.setBarcode(bc);
		out("Test add: [%s]", pal.add(p) ? "SUCCESS" : "FAILURE");
		out("Test incorrect add: [%s]", !pal.add(p) ? "SUCCESS" : "FAILURE");
		
		// test 'DSL'
		bc.setBarcode(4023125016257l);
		p.setName("DSL");
		p.setPrice(123.04f);
		p.setBarcode(bc);
		out("Test add: [%s]", pal.add(p) ? "SUCCESS" : "FAILURE");
		
		// test incorrect barcode
		bc.setBarcode(4023125016259l);
		out("Checksum is " + bc.getCheck() + " [%s]", bc.getCheck() ? "FAILURE" : "SUCCESS");
		
		// test 'Router'
		bc.setBarcode(5990206956643l);
		p.setName("Router");
		p.setPrice(237.95f);
		p.setBarcode(bc);
		out("Test add: [%s]", pal.add(p) ? "SUCCESS" : "FAILURE");
		
		// output of full pallet
		out("########################################################");
		out(pal.toString());
		out("########################################################");
		
		// test subtract
		out("Test sub: [%s]", pal.subtract(p) ? "SUCCESS" : "FAILURE");
		out("Test incorrect sub: [%s]", !pal.subtract(p) ? "SUCCESS" : "FAILURE");

		// output of pallet after subtraction
		out("########################################################");
		out(pal.toString());
		out("########################################################");
	}
	
	private static void out(String s, Object ... o)
	{
		System.out.println(String.format(s, o));
	}
	
	public static final String PATH = 
			"L:\\PROF\\HOTOP\\Stud\\SoSe-14\\IE2-SOL2\\Material\\barcode.dat";
}
