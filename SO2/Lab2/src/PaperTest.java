import testing.Logger;
import testing.TestException;
import testing.Testable;

public class PaperTest implements Testable
{
	@Override
	public boolean test(String name, Logger log, String input) throws TestException
	{

		
		return false;
	}

	@Override
	public String[] getTestNames()
	{
		return new String[] {};
	}

	@Override
	public String getName()
	{
		return "SO2 Lab2 - Papers";
	}

	@Override
	public String getModeName()
	{
		return "manual";
	}
}
