package testing.exception;

import testing.ICallable;

public class InvalidArgumentsException extends TestException
{
	private static final long serialVersionUID = -8569714113212297486L;

	public InvalidArgumentsException(ICallable ic, String s)
	{
		super(String.format(INVALID, ic.getCmdName(), s));
	}
	
	private static String INVALID = "ERR: '%s': Invalid arguments '%s'";
}
