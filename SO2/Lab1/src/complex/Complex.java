package complex;

import java.math.BigDecimal;
import java.math.RoundingMode;

public class Complex
{
	private final Cartesian cart; // Stores number in form of Cartesian coordinates
	private final Polar polar; // Stores number in form of polar coordinates
	private final boolean is_int;
	
	public Complex(Complex c) { this(c.cart, c.polar, false); } // Copy-Constructor
	public Complex(double d) { this(new Cartesian(d, 0.0), false); } // Constructor from real number
	public Complex(Cartesian c) { this(c, c.toPolar(), false); } // Constructor from Cartesian coordinates
	public Complex(Polar p) { this(p.toCartesian(), p, false); } // Constructor from polar coordinates
	public Complex(Complex c, boolean i) { this(c.cart, c.polar, i); }
	public Complex(double d, boolean i) { this(new Cartesian(d, 0.0), i); }
	public Complex(Cartesian c, boolean i) { this(c, c.toPolar(), i); }
	public Complex(Polar p, boolean i) { this(p.toCartesian(), p, i); }
	private Complex(Cartesian c, Polar p, boolean i)
	{
		cart = c;
		polar = p;
		is_int = i;
	}
	
	// getter-methods for cartesian and polar representations
	public double getRealPart( ) { return is_int ? (int)cart.real : cart.real; }
	public double getImaginaryPart( ) { return is_int ? (int)cart.imaginary : cart.imaginary; }
	public double getMagnitude( ) { return is_int ? (int)polar.magnitude : polar.magnitude; }
	public double getAngle( ) { return is_int ? (int)polar.angle : polar.angle; }
	// complex-conjugate and absolute value
	public Complex conjugate( ) { return new Complex(new Cartesian(cart.real, -cart.imaginary), is_int); }
	public double abs( ) { return getMagnitude(); }
	
	@Override
	public int hashCode( ) // calculates a hash-code for proper 'equals'-semantics
	{
		return (int)(cart.real * cart.imaginary + polar.magnitude * polar.angle);
	}
	
	@Override
	public boolean equals(Object o) // compares two Complex objects
	{
		if(o instanceof Complex)
		{
			// two numbers are considered equal if their cartesian representation matches up
			return (new BigDecimal(cart.real)).setScale(ERR_MIN, RoundingMode.HALF_UP) == 
					(new BigDecimal(((Complex) o).cart.real)).setScale(ERR_MIN, RoundingMode.HALF_UP)
				&& (new BigDecimal(cart.imaginary)).setScale(ERR_MIN, RoundingMode.HALF_UP) == 
					(new BigDecimal(((Complex) o).cart.imaginary)).setScale(ERR_MIN, RoundingMode.HALF_UP);
		}
		
		return false;
	}
	
	@Override
	public String toString( ) // generates String containing the complex number in both Cartesian and polar form
	{
		return String.format("z{\"%s\": %f + j%f, %f * e ^ j%f}", is_int ? "int" : "double", 
				getRealPart(), getImaginaryPart(), getMagnitude(), getAngle());
	}

	public String cartesianString( )
	{
		String s;
		
		s = (new BigDecimal(getRealPart())).setScale(roundTo(), RoundingMode.HALF_UP).toPlainString() + " ";
		
		s += (getImaginaryPart() < 0 ? '-' : '+') + " ";
		
		s += "j" + (new BigDecimal(Math.abs(getImaginaryPart())))
				.setScale(roundTo(), RoundingMode.HALF_UP).toPlainString();
		
		return s;
	}
	
	public String polarString( )
	{
		String s;
		
		s = (new BigDecimal(getMagnitude())).setScale(roundTo(), RoundingMode.HALF_UP).toPlainString() + " < ";
		
		s += (new BigDecimal(getAngle() * 180D / Math.PI)).setScale(roundTo(), RoundingMode.HALF_UP).toPlainString() + "°";
		
		return s;
	}
	
	public static Complex fromCartesian(double r, double i) { return fromCartesian(r, i, false); }
	public static Complex fromCartesian(double r, double i, boolean ii) // generates Complex object from real and imaginary part
	{
		return new Complex(new Cartesian(r, i), ii);
	}
	
	public static Complex fromPolar(double m, double a) { return fromPolar(m, a, false); }
	public static Complex fromPolar(double m, double a, boolean ii) // generates Complex object from angle ang magnitude
	{
		return new Complex(new Polar(m, a), ii);
	}
	
	public Complex add(Complex ... c) { return Add(this, c); } // member-add
	public Complex sub(Complex c) { return Sub(this, c); } // member-sub
	public Complex mul(Complex ... c) { return Mul(this, c); } // member-mul
	public Complex div(Complex c) { return Div(this, c); } // member-div
	
	public static Complex Add(Complex c, Complex ... o) // add up multiple Complex numbers
	{
		double r = c.cart.real, i = c.cart.imaginary;
		boolean ii = c.is_int;
		
		// (a1 + j * b1) + (a2 + j * b2) == (a1 + a2) + j * (b1 + b2)
		// so i just add up the real and imaginary parts to get the complex sum
		
		for(Complex _c : o)
		{
			r += _c.cart.real;
			i += _c.cart.imaginary;
			
			ii = ii && _c.is_int;
		}
		
		return fromCartesian(r, i, ii); // reconstruct result from its real and imaginary parts
	}
	
	public static Complex Sub(Complex c1, Complex c2) // subtracts one complex number from another
	{
		return fromCartesian(c1.cart.real - c2.cart.real, c1.cart.imaginary - c2.cart.imaginary, c1.is_int && c2.is_int);
	}
	
	public static Complex Mul(Complex c, Complex ... o) // multiplies many complex numbers with each other
	{
		double m = c.polar.magnitude, a = c.polar.angle;
		boolean ii = c.is_int;
		
		// m1 * e ^ (j * a1) * m2 * e ^ (j * a2) == m1 * m2 * e ^ (j * (a1 + a2))
		// so i add up all angles and multiply all magnitudes to get the angle&magnitude of the result
		
		for(Complex _c : o)
		{
			m *= _c.polar.magnitude;
			a += _c.polar.angle;
			
			ii = ii && _c.is_int;
		}
		
		return fromPolar(m, a, ii); // reconstruct result from its angle and magnitude
	}
	
	public static Complex Div(Complex c1, Complex c2) // divides one complex number by another
	{
		return fromPolar(c1.polar.magnitude / c2.polar.magnitude, c1.polar.angle - c2.polar.angle, c1.is_int && c2.is_int);
	}
	
	public static class Cartesian // internal class for Cartesian representation
	{
		public final double real, imaginary;
		
		public Cartesian(double r, double i)
		{
			real = r;
			imaginary = i;
		}
		
		public Polar toPolar( ) // conversion to Polar representation
		{
			// z = a + j * b = m * e ^ (j * p)
			// m = sqrt(a^2 + b^2)  &&  p = arctan(imaginary / real)
			// ((i use Math.atan2 because it takes the real and imaginary
			//   parts seperately, taking care of special conditions such
			//   as real == 0 or real < 0 ))
			return new Polar(Math.sqrt(real * real + imaginary * imaginary), Math.atan2(imaginary, real));
		}
	}
	
	public static class Polar // internal class for Polar representation
	{
		public final double magnitude, angle;
		
		public Polar(double m, double a)
		{
			while(a >= 2.0 * Math.PI) a -= 2.0 * Math.PI; // makes sure that its angle is element of [0; 2pi)
			while(a < 0.0) a += 2.0 * Math.PI;
			
			magnitude = m;
			angle = a;
		}
		
		public Cartesian toCartesian( ) //  conversion to Cartesian representation
		{
			// z = m * e ^ (j * p) = a + j * b
			// a = cos(p) * m  &&  b = sin(p) * m
			return new Cartesian(Math.cos(angle) * magnitude, Math.sin(angle) * magnitude);
		}
	}
	
	protected int roundTo( ) { return is_int ? 0 : ROUND_TO; }
	
	// number of digits that complex numbers have to align in order to be considered equal
	private static final int ERR_MIN = 8;
	private static final int ROUND_TO = 2;
}
