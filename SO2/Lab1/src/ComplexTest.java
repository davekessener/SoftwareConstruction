import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.Random;

import complex.Complex;

import testing.Logger;
import testing.TestException;
import testing.Testable;


public class ComplexTest implements Testable
{
	private static final int CONVERSION_COUNT = 1024;
	private static final int TEST_CASES = 4096;
	private static final int MAX_LENGTH = 128;
	private static final int COMP_DIGITS = 8;
	
	@Override
	public boolean test(String name, Logger log, String input)
			throws TestException
	{
		Random r = new Random(System.currentTimeMillis());
			
		if(name.equalsIgnoreCase(SINGLE_NUMBER))
		{
			return checkNumber(r.nextDouble() * r.nextInt(MAX_LENGTH), r.nextDouble() * r.nextInt(MAX_LENGTH), log);
		}
		else if(name.equalsIgnoreCase(MANY_NUMBERS))
		{
			return checkMany(r, log);
		}
		else
		{
			return false;
		}
	}
	
	private boolean checkMany(Random r, Logger log) { return checkMany(r, log, 100); }
	private boolean checkMany(Random r, Logger log, int steps)
	{
		double _r, _i;
		int d = TEST_CASES / steps;
		
		for(int i = 0 ; i < TEST_CASES ; ++i)
		{
			if(!checkNumber(_r = r.nextDouble() * r.nextInt(MAX_LENGTH), 
					_i = r.nextDouble() * r.nextInt(MAX_LENGTH), null))
			{
				log.log("Failed with numbers r=%f, i=%f at test %d of %d:", _r, _i, i, TEST_CASES);
				
				log.incIndent();
				checkNumber(_r, _i, log);
				log.decIndent();
				
				return false;
			}
			else if(i % d == 0)
			{
				log.log("[...] running %d / %d (%d%%)", i, TEST_CASES, i * 100 / TEST_CASES);
			}
		}
		
		log.log("Successfully ran %d tests.", TEST_CASES);
		
		return true;
	}
	
	private boolean checkNumber(final double r, final double i, Logger log)
	{
		Complex c = Complex.fromCartesian(r, i);
		
		if(log != null)
		{
			log.log("Check number real=%f, imaginary=%f", r, i);
			
			log.log("c.real      = %f", c.getRealPart());
			log.log("c.imaginary = %f", c.getImaginaryPart());
			log.log("c.magnitude = %f", c.getMagnitude());
			log.log("c.angle     = %f (%f pi)", c.getAngle() * 180.0 / Math.PI, c.getAngle() / Math.PI);
		}
	
		int p;
		for(p = 0 ; p < CONVERSION_COUNT ; ++p)
		{
			c = Complex.fromPolar(c.getMagnitude(), c.getAngle());
			c = Complex.fromCartesian(c.getRealPart(), c.getImaginaryPart());

			if(!comp(r, c.getRealPart()) || !comp(i, c.getImaginaryPart())) break;
		}

		if(log != null)
		{
			log.log("------------------------------------");
			log.log("After %d of %d conversions:", p, CONVERSION_COUNT);
			
			log.log("c.real      = %f", c.getRealPart());
			log.log("c.imaginary = %f", c.getImaginaryPart());
			log.log("c.magnitude = %f", c.getMagnitude());
			log.log("c.angle     = %f (%f pi)", c.getAngle() * 180.0 / Math.PI, c.getAngle() / Math.PI);
		}
		
		return comp(r, c.getRealPart()) && comp(i, c.getImaginaryPart());
	}
	
	private static boolean comp(double d1, double d2)
	{
		return (new BigDecimal(d1)).setScale(COMP_DIGITS, RoundingMode.HALF_UP).doubleValue()
				== (new BigDecimal(d2)).setScale(COMP_DIGITS, RoundingMode.HALF_UP).doubleValue();
	}

	@Override
	public String[] getTestNames()
	{
		return new String[] {SINGLE_NUMBER, MANY_NUMBERS};
	}

	@Override
	public String getName()
	{
		return "SO2 - Lab1: Complex numbers";
	}

	@Override
	public String getModeName()
	{
		return "auto random";
	}

	public static String SINGLE_NUMBER = "a single number", MANY_NUMBERS = "many numbers";
}
