import testing.InputNone;
import testing.LoggerStdout;
import testing.Test;


public class Start
{
	public static void main(String args[])
	{
		(new Test(new ComplexTest(), new LoggerStdout(), new InputNone())).doTest();
	}
}
