package testing;

public class TestException extends Exception
{
	private static final long serialVersionUID = -6925386258809280105L;
	private Exception threw;

	public TestException(Exception t)
	{
		super(t.getMessage());
		threw = t;
	}
	
	public Exception getThrowException( )
	{
		return threw;
	}
}
