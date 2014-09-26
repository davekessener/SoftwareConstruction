package ean;

public class BarCode implements Cloneable
{
	protected long barcode;
	protected String country;
	protected int[] part;
	protected boolean check;
	protected Country countryCode;
	
	public String getCountry() {
		return country;
	}

	public boolean getCheck() {
		return check;
	}

	public Country getCountryCode() {
		return countryCode;
	}

	public long getBarcode() {
		return barcode;
	}

	public BarCode( ) { }
	
	public BarCode(long bc, Country c)
	{
		setCountry(c);
		setBarcode(bc);
	}
	
	@Override
	public Object clone()
	{
		try
		{
			BarCode bc = (BarCode) super.clone();
			bc.part = part.clone();
			bc.countryCode = (Country) countryCode.clone();
			return bc;
		}
		catch(CloneNotSupportedException e)
		{
			return null;
		}
	}
	
	public void setCountry(Country c) { countryCode = (Country) c.clone(); }
	
	public void setBarcode(long bc)
	{
		barcode = bc;
		part = transfer(bc);
		check = validate(bc);
		country = checkCountry(part[0]);
	}
	
	@Override
	public int hashCode()
	{
		return (int) barcode;
	}
	
	@Override
	public boolean equals(Object o)
	{
		if(o == null) return false;
		if(o == this) return true;
		if(o instanceof BarCode)
		{
			BarCode bc = (BarCode) o;
			return bc.barcode == barcode;
		}
		
		return false;
	}
	
	@Override
	public String toString()
	{
		String s = "";
		
		int[] l = new int[]{3,4,5,1};
		for(int i = 0 ; i < part.length ; ++i)
		{
			String t = "" + part[i];
			while(t.length() < l[i]) t = "0" + t; // zero padding
			
			if(i > 0) s += "-";
			s += t;
		}
		s += " // " + check + " // " + country;
		
		return s;
	}
	
	public int[] transfer(long barcode)
	{
		int[] bc = new int[4];
		bc[3] = (int) (barcode % 10); // checksum is the last digit
		barcode /= 10; // shift right 1 digit
		bc[2] = (int) (barcode % 100000); // product code is 5 digits
		barcode /= 100000; // shift right 5 digits
		bc[1] = (int) (barcode % 10000); // Mfg code is 4 digits
		barcode /= 10000; // shift right 4 digits
		bc[0] = (int) (barcode % 1000); // country code is 3 digits
		
		return bc;
	}
	
	public boolean validate(long barcode)
	{
		// barcode is assumed to be valid if the checksum is correct
		return (barcode % 10) == calcChecksum(barcode);
	}
	
	public String checkCountry(int cc)
	{
		return countryCode.getCountry(cc);
	}
	
	public int calcChecksum(long bc)
	{
		bc /= 10; // cut off given checksum. it's not needed for calculations
		int s = 0;
		for(int i = 0 ; i < 12 ; ++i)
		{
			// startig from the back add all digits together.
			// for even indices multiply with 3, for odd with 1
			s += ((i % 2) == 0 ? 3 : 1) * (int)(bc % 10);
			bc /= 10; // shift right
		}
		
		// take the last digit, subtract it from 10 to get the checksum.
		// for the special case 's % 10 == 0' use modulo 10 to get the desired '0' 
		return (10 - (s % 10)) % 10;
	}
}
