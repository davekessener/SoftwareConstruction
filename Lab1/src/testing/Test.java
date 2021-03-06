package testing;

public class Test
{
	private Testable testing;
	private Logger log;
	private Input input;

	public Test(Testable t, Logger l, Input in)
	{
		testing = t;
		log = l;
		input = in;
	}

	public boolean doTest()
	{
		prepare();

		boolean success = true;
		String s[] = testing.getTestNames();

		log.log("=============================================================");
		log.log("# Testing '%s' in %s mode", testing.getName(), testing.getModeName());
		log.log("=============================================================");

		try
		{
			for(String test : s)
			{
				attempting(test);

				if(input.needsPrompt()) log.log_("%s $> ", test);

				log.incIndent();

				String prompt = input.getInputFor(test);
				boolean result = testing.test(test, log, prompt);

				if(input.needsEcho()) log.log(prompt);

				log.decIndent();

				if(result)
				{
					succeeded(test);
				}
				else
				{
					failed(test);
					success = false;
				}

				if(!success) break;
			}
		}
		catch(TestException e)
		{
			fatal(e.getThrowException());
			success = false;
		}

		cleanup();

		log.log("[DONE]");

		return success;
	}

	protected void prepare()
	{
	}

	protected void cleanup()
	{
	}

	protected void attempting(String t)
	{
		log.log("### Attempting test '%s':", t);
	}

	protected void succeeded(String t)
	{
		log.log("### Success!");
	}

	protected void failed(String t)
	{
		log.log("### Failure!");
	}

	protected void fatal(Exception e)
	{
		log.log("### ERR: FATAL FAILURE!:");
		e.printStackTrace(log);
	}
}
