package testing;

public class InputFile implements Input
{
	@Override
	public String getInputFor(String t) throws TestException
	{
		return null;
	}

	@Override
	public boolean needsEcho()
	{
		return true;
	}

	@Override
	public boolean needsPrompt()
	{
		return true;
	}
}
