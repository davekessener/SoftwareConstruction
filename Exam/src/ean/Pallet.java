package ean;

public class Pallet extends Product
{
	protected Product[] products;
	
	public Pallet() { products = new Product[0]; }
	
	public Pallet(String name, BarCode myCode)
	{
		super(name, 0.0f, myCode);
	}
	
	@Override
	public String toString()
	{
		String s = super.toString();
		for(int i = 0 ; i < products.length ; ++i)
		{
			s += "\n" + "product " + (i + 1) + ": " + products[i].toString();
		}
		return s;
	}
	
	@Override
	public Object clone()
	{
		Pallet p = (Pallet) super.clone();
		p.products = new Product[products.length];
		// for arrays of custom objects use for-each cloning
		// by iterating over the orig. array and clone each member
		for(int i = 0 ; i < p.products.length ; ++i)
		{
			p.products[i] = (Product) products[i].clone();
		}
		return p;
	}
	
	@Override
	public boolean equals(Object o)
	{
		if(!super.equals(o)) return false;
		if(o == this) return true;
		if(o instanceof Pallet)
		{
			Pallet p = (Pallet) o;
			if(p.products.length != products.length) return false;
			for(int i = 0 ; i < products.length ; ++i)
			{
				if(!p.products[i].equals(products[i])) return false;
			}
			return true;
		}
		return false;
	}

	public boolean add(Product p)
	{
		Product[] t = new Product[products.length + 1];
		for(int i = 0 ; i < products.length ; ++i)
		{
			// if the product already exists, abort and return false
			if(p.equals(products[i])) return false;
			t[i] = products[i];
		}
		t[products.length] = (Product) p.clone();
		products = t;
		price += p.price;
		return true;
	}
	
	public boolean subtract(Product p)
	{
		Product[] t = new Product[products.length - 1];
		for(int i = 0, j = 0 ; i < products.length ; ++i)
		{
			// if the currect object is the one to be subtracted, skip it.
			if(p.equals(products[i])) continue;
			// if 'j == t.length' is true, we reached the end of the source
			// array without finding the product to be subtracted.
			// abort without subtracting.
			if(j == t.length) return false;
			t[j++] = products[i];
		}
		products = t;
		price -= p.price;
		return true;
	}
}
