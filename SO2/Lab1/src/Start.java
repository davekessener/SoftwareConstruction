import testing.InputNone;
import testing.InputStdin;
import testing.LoggerStdout;
import testing.Test;


public class Start
{
	public static void main(String args[])
	{
		(new Test(new MorseTest(), new LoggerStdout(), new InputStdin())).doTest();
	}
}
