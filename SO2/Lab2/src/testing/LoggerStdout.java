package testing;

public class LoggerStdout extends Logger
{
	public LoggerStdout( )
	{
		super(System.out);
	}

	@Override
	protected void out(String s)
	{
		System.out.print(s);
	}
}
