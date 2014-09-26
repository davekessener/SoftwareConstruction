import paper.Paper;
import paper.exception.PaperReadWriteException;
import testing.ICallable;
import testing.IStorage;
import testing.Tester;
import testing.Variable;
import testing.exception.InvalidArgumentsException;

public class CommandLoadPaper implements ICallable
{
	@Override
	public String getCmdName()
	{
		return CMD_LOADPAPER;
	}

	@Override
	public boolean call(IStorage is, String fn) throws InvalidArgumentsException
	{
		if(fn.isEmpty()) throw new InvalidArgumentsException(this, NEED_FNAME);
		
		try
		{
			Paper p = Paper.constructFromFile(fn);
			
			is.setSelection(new Variable(Tester.UNKNOWN, p));
		}
		catch(PaperReadWriteException e)
		{
			e.printStackTrace();
		}
		
		return true;
	}

	public static final String CMD_LOADPAPER = "loadpaper";
	private static final String NEED_FNAME = "Cannot omit filename.";
}
