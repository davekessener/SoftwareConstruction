package ean;

public class Product implements Cloneable
{
	protected String name;
	protected float price;
	protected BarCode myCode;
	
	public Product() { name = ""; price = 0.0f; }
	
	public Product(String name, float price, BarCode myCode)
	{
		setName(name);
		setPrice(price);
		setBarcode(myCode);
	}
	
	public void setName(String name) { this.name = name; }
	public void setPrice(float price) { this.price = price; }
	public void setBarcode(BarCode myCode) { this.myCode = (BarCode) myCode.clone(); }
	
	@Override
	public Object clone()
	{
		try
		{
			Product p = (Product) super.clone();
			p.myCode = (BarCode) myCode.clone();
			return p;
		}
		catch(CloneNotSupportedException e)
		{
			return null;
		}
	}
	
	@Override
	public String toString()
	{
		return name + " // " + price + "\n" + (myCode != null ? myCode.toString() : "");
	}
	
	@Override
	public int hashCode()
	{
		return name.hashCode() ^ myCode.hashCode();
	}
	
	@Override
	public boolean equals(Object o)
	{
		if(o == null) return false;
		if(o == this) return true;
		if(o instanceof Product)
		{
			Product p = (Product) o;
			return p.name.equals(name) && p.price == price &&
					p.myCode.equals(myCode);
		}
		
		return false;
	}
}
