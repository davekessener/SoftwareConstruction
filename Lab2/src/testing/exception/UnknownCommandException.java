package testing.exception;

public class UnknownCommandException extends TestException
{
	private static final long serialVersionUID = 2453877576952422833L;

	public UnknownCommandException(String s)
	{
		super(String.format(UNKNOWN, s));
	}
	
	private static final String UNKNOWN = "ERR: Command '%s' is not valid.";
}
