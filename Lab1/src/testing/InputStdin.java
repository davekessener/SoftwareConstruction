package testing;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class InputStdin implements Input
{
	private BufferedReader in;
	
	public InputStdin( ) { this(System.in); }
	public InputStdin(InputStream is)
	{
		in = new BufferedReader(new InputStreamReader(is));
	}
	
	@Override
	public String getInputFor(String t) throws TestException
	{
		try
		{
			return in.readLine();
		}
		catch (IOException e)
		{
			throw new TestException(e);
		}
	}
	
	@Override
	public boolean needsEcho()
	{
		return false;
	}
	
	@Override
	public boolean needsPrompt()
	{
		return true;
	}
}
