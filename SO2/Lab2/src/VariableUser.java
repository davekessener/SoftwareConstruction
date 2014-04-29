import java.io.IOException;

import paper.User;
import paper.exception.PaperInvalidColumnException;
import paper.exception.PaperInvalidRowException;
import paper.exception.PaperReadWriteException;
import testing.IStorage;
import testing.Variable;
import testing.exception.InvalidArgumentsException;
import testing.exception.UnknownCommandException;

public class VariableUser extends Variable
{
	public VariableUser(String name, User o)
	{
		super(name, o);
	}
	
	@Override
	public boolean call(IStorage is, String cmd) throws UnknownCommandException, InvalidArgumentsException
	{
		String cn = cmd.split(" ")[0].toLowerCase();
		String args = cmd.replaceFirst("[^ ]+ ?", "");
		
		if(cn.equalsIgnoreCase(CMD_ADDA))
		{
			addAnnotation(is, args);
		}
		else if(cn.equalsIgnoreCase(CMD_ADDP))
		{
			addPaper(is, args);
		}
		else if(cn.equalsIgnoreCase(CMD_CHANGE))
		{
			change(is, args);
		}
		else if(cn.equalsIgnoreCase(CMD_SAVE))
		{
			save(is, args);
		}
		else if(cn.equalsIgnoreCase(CMD_ANN))
		{
			annotate(is, args);
		}
		else
		{
			throw new UnknownCommandException(cn);
		}
		
		return true;
	}
	
	private void annotate(IStorage is, String args) throws InvalidArgumentsException
	{
		try
		{
			String n = args.split(" ")[0];
			int r = Integer.parseInt(args.split(" ")[1]);
			int c = Integer.parseInt(args.split(" ")[2]);
			String a = args.replaceFirst("[^ ]+ [0-9]+ [0-9]+ ?", "");
			
			((User) getObject()).annotate(n, r, c, a);
		}
		catch(IndexOutOfBoundsException e)
		{
			throw new InvalidArgumentsException(this, args);
		}
		catch(NumberFormatException e)
		{
			e.printStackTrace();
		}
		catch(PaperInvalidRowException e)
		{
			e.printStackTrace();
		}
		catch(PaperInvalidColumnException e)
		{
			e.printStackTrace();
		}
	}
	
	private void save(IStorage is, String fn) throws InvalidArgumentsException
	{
		if(fn.isEmpty()) throw new InvalidArgumentsException(this, EMPTY);
		
		try
		{
			((User) getObject()).writeToFile(fn);
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
	}
	
	private void change(IStorage is, String s) throws InvalidArgumentsException
	{
		if(s.isEmpty()) throw new InvalidArgumentsException(this, EMPTY);
		
		((User) getObject()).changePaperToAnnotation(s);
	}
	
	private void addAnnotation(IStorage is, String args) throws InvalidArgumentsException
	{
		if(args.isEmpty()) throw new InvalidArgumentsException(this, EMPTY);
		
		try
		{
			((User) getObject()).addAnnotation(args);
		}
		catch(PaperReadWriteException e)
		{
			e.printStackTrace();
		}
	}
	
	private void addPaper(IStorage is, String args) throws InvalidArgumentsException
	{
		if(args.isEmpty()) throw new InvalidArgumentsException(this, EMPTY);
		
		try
		{
			((User) getObject()).addPaper(args);
		}
		catch(PaperReadWriteException e)
		{
			e.printStackTrace();
		}
	}
	
	private static final String CMD_ADDP = "addpaper";
	private static final String CMD_ADDA = "addann";
	private static final String CMD_CHANGE = "changeptoa";
	private static final String CMD_SAVE = "saveuser";
	private static final String CMD_ANN = "annotate";
	
	private static final String EMPTY = "Need to have specified a name.";
}
