import paper.Paper;
import paper.exception.PaperWordNotFoundException;
import testing.ICallable;
import testing.IStorage;
import testing.Variable;
import testing.exception.InvalidArgumentsException;
import testing.exception.UnknownCommandException;

public class CommandFindWord implements ICallable
{
	@Override
	public String getCmdName()
	{
		return CMD_FIND;
	}

	@Override
	public boolean call(IStorage is, String args) throws UnknownCommandException, InvalidArgumentsException
	{
		if(args.isEmpty()) throw new InvalidArgumentsException(this, NO_WORD);

		Variable v = is.getSelection();
		
		if(v == null) throw new InvalidArgumentsException(this, NO_SELECT);
		if(!(v.getObject() instanceof Paper)) throw new InvalidArgumentsException(this, WRONG_TYPE);
		
		try
		{
			int[] l = ((Paper) v.getObject()).searchWord(args);

			is.getLog().log("%d %d", l[0], l[1]);
		}
		catch(PaperWordNotFoundException e)
		{
			is.getLog().log(e.getMessage());
		}
		
		return true;
	}
	
	private static final String CMD_FIND = "findword";
	private static final String NO_WORD = "Need to specify a word to search for.";
	private static final String NO_SELECT = "No object of type 'Paper' selected.";
	private static final String WRONG_TYPE = "Selected object is of incorrect type.";
}
