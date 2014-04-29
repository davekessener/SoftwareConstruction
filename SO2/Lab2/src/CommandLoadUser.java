import java.io.IOException;

import paper.User;
import paper.exception.PaperReadWriteException;
import testing.ICallable;
import testing.IStorage;
import testing.Tester;
import testing.exception.InvalidArgumentsException;
import testing.exception.UnknownCommandException;


public class CommandLoadUser implements ICallable
{
	@Override
	public String getCmdName()
	{
		return CMD_LOAD;
	}

	@Override
	public boolean call(IStorage is, String fn) throws UnknownCommandException, InvalidArgumentsException
	{
		if(fn.isEmpty()) throw new InvalidArgumentsException(this, NEED_FNAME);
		
		try
		{
			User u = User.constructFromFile(fn);
			
			is.setSelection(new VariableUser(Tester.UNKNOWN, u));
		}
		catch(PaperReadWriteException e)
		{
			e.printStackTrace();
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
		
		return true;
	}

	private static final String CMD_LOAD = "loaduser";
	private static final String NEED_FNAME = "Cannot omit filename.";
}
