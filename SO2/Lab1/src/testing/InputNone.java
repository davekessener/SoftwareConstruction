package testing;

public class InputNone implements Input
{
	@Override
	public String getInputFor(String t) throws TestException
	{
		return "";
	}

	@Override
	public boolean needsEcho()
	{
		return false;
	}

	@Override
	public boolean needsPrompt()
	{
		return false;
	}
}
