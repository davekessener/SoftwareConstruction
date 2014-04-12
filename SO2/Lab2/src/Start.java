import testing.InputStdin;
import testing.LoggerStdout;
import testing.Test;

public class Start
{
	public static void main(String[] args)
	{
		(new Test(new PaperTest(), new LoggerStdout(), new InputStdin())).doTest();
	}
}
