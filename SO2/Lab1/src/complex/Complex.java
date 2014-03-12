package complex;

public class Complex
{
	private final Cartesian cart;
	private final Polar polar;
	
	public Complex(Complex c) { this(c.cart, c.polar); }
	public Complex(double d) { this(new Cartesian(d, 0.0)); }
	public Complex(Cartesian c) { this(c, c.toPolar()); }
	public Complex(Polar p) { this(p.toCartesian(), p); }
	public Complex(Cartesian c, Polar p)
	{
		cart = c;
		polar = p;
	}
	
	public double getRealPart( ) { return cart.real; }
	public double getImaginaryPart( ) { return cart.imaginary; }
	public double getMagnitude( ) { return polar.magnitude; }
	public double getAngle( ) { return polar.angle; }
	
	@Override
	public int hashCode( )
	{
		return (int)(cart.real * cart.imaginary + polar.magnitude * polar.angle);
	}
	
	@Override
	public boolean equals(Object o)
	{
		if(o instanceof Complex)
		{
			return cart.real - ((Complex) o).cart.real < ERR_MIN;
		}
		
		return false;
	}
	
	@Override
	public String toString( )
	{
		return String.format("z{%f + j%f, %f * e ^ j%f}", cart.real, cart.imaginary, polar.magnitude, polar.angle);
	}
	
	public static Complex fromCartesian(double r, double i)
	{
		return new Complex(new Cartesian(r, i));
	}
	
	public static Complex fromPolar(double m, double a)
	{
		return new Complex(new Polar(m, a));
	}
	
	public Complex add(Complex ... c) { return add(this, c); }
	public Complex sub(Complex c) { return sub(this, c); }
	public Complex mul(Complex ... c) { return mul(this, c); }
	public Complex div(Complex c) { return div(this, c); }
	
	public static Complex add(Complex c, Complex ... o)
	{
		double r = c.cart.real, i = c.cart.imaginary;
		
		for(Complex _c : o)
		{
			r += _c.cart.real;
			i += _c.cart.imaginary;
		}
		
		return fromCartesian(r, i);
	}
	
	public static Complex sub(Complex c1, Complex c2)
	{
		return fromCartesian(c1.cart.real - c2.cart.real, c1.cart.imaginary - c2.cart.imaginary);
	}
	
	public static Complex mul(Complex c, Complex ... o)
	{
		double m = c.polar.magnitude, a = c.polar.angle;
		
		for(Complex _c : o)
		{
			m *= _c.polar.magnitude;
			a += _c.polar.angle;
		}
		
		return fromPolar(m, a);
	}
	
	public static Complex div(Complex c1, Complex c2)
	{
		return fromPolar(c1.polar.magnitude / c2.polar.magnitude, c1.polar.angle - c2.polar.angle);
	}
	
	public static class Cartesian
	{
		public final double real, imaginary;
		
		public Cartesian(double r, double i)
		{
			real = r;
			imaginary = i;
		}
		
		public Polar toPolar( )
		{
			return new Polar(Math.sqrt(real * real + imaginary * imaginary), Math.atan2(imaginary, real));
		}
	}
	
	public static class Polar
	{
		public final double magnitude, angle;
		
		public Polar(double m, double a)
		{
			while(a >= 2.0 * Math.PI) a -= 2.0 * Math.PI;
			while(a < 0.0) a += 2.0 * Math.PI;
			
			magnitude = m;
			angle = a;
		}
		
		public Cartesian toCartesian( )
		{
			return new Cartesian(Math.cos(angle) * magnitude, Math.sin(angle) * magnitude);
		}
	}
	
	private static final double ERR_MIN = 0.000001;
}
