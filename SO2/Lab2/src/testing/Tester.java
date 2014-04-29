package testing;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import testing.exception.TestException;
import testing.exception.InvalidArgumentsException;
import testing.exception.UnknownCommandException;

public abstract class Tester implements IStorage
{
	private Map<String, Variable> objects;
	private Map<String, ICallable> functions;
	private Variable select;
	private Input input;
	private Logger log;
	
	public Tester() { this(new InputStdin(), new LoggerStdout()); }
	public Tester(Input in, Logger out)
	{
		objects = new HashMap<String, Variable>();
		functions = new HashMap<String, ICallable>();
		select = null;
		input = in;
		log = out;
		
		CommandMake makeCmd = new CommandMake();
		
		registerCommands();
		registerTypes(makeCmd);
		
		register(new CQuit());
		register(new CEcho());
		register(new CToString());
		register(new CSelect());
		register(new CName());
		register(new CList());
		register(makeCmd);
	}
	
	protected abstract void registerCommands();
	protected abstract void registerTypes(CommandMake cmd);
	
	public void run()
	{
		try
		{
			while(true)
			{
				log.log_(PROMPT, select == null ? NIL : select.getReferenceName());
				String cmd = input.readline().replaceAll("[ \\t]+", " ").trim();
				
				try
				{
					if(!execute(cmd)) break;
				}
				catch(TestException e)
				{
					log.log("%s", e.getMessage());
				}
			}

			log.log("goodbye");
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
	}
	
	protected boolean execute(String cmd) throws UnknownCommandException, InvalidArgumentsException
	{
		String n = cmd.split(" ")[0].toLowerCase();
		String args = cmd.replaceFirst("[^ ]+ ?", "");
		
		if(functions.containsKey(n))
		{
			return functions.get(n).call(this, args);
		}
		else if(select != null)
		{
			return select.call(this, cmd);
		}
		else
		{
			throw new UnknownCommandException(cmd);
		}
	}
	
	protected void register(ICallable ic)
	{
		functions.put(ic.getCmdName().toLowerCase(), ic);
	}
	
	@Override
	public void setSelection(Variable iw)
	{
		if(iw != null) objects.put(iw.getReferenceName(), iw);
		select = iw;
	}
	
	@Override
	public Variable getSelection()
	{
		return select;
	}
	
	@Override
	public Logger getLog()
	{
		return log;
	}

	@Override
	public boolean hasObject(String name)
	{
		return objects.containsKey(name);
	}

	@Override
	public Variable getObject(String name)
	{
		return hasObject(name) ? objects.get(name) : null;
	}
	
	@Override
	public String[] getObjectList()
	{
		List<String> r = new ArrayList<String>(objects.size());
		
		for(String n : objects.keySet())
		{
			r.add(n);
		}
		
		return r.toArray(new String[r.size()]);
	}
	
	public static final String UNKNOWN = "?";
	public static final String PROMPT = "$'%s'> ";
	public static final String NIL = "nil";
	public static final String CMD_QUIT = "exit";
	public static final String CMD_ECHO = "echo";
	public static final String CMD_TOSTRING = "toString";
	public static final String CMD_SELECT = "select";
	public static final String CMD_NAME = "name";
	public static final String CMD_LIST = "list";
	
	private static class CQuit implements ICallable
	{
		@Override
		public String getCmdName()
		{
			return CMD_QUIT;
		}

		@Override
		public boolean call(IStorage is, String args) throws InvalidArgumentsException
		{
			return false;
		}
	}
	
	private static class CEcho implements ICallable
	{
		@Override
		public String getCmdName()
		{
			return CMD_ECHO;
		}

		@Override
		public boolean call(IStorage is, String args) throws InvalidArgumentsException
		{
			is.getLog().log("%s", args);
			
			return true;
		}
	}
	
	private static class CToString implements ICallable
	{
		@Override
		public String getCmdName()
		{
			return CMD_TOSTRING;
		}

		@Override
		public boolean call(IStorage is, String args) throws InvalidArgumentsException
		{
			Variable o = is.getSelection();
			
			is.getLog().log("%s", o == null ? NIL : o.getObject().toString());
			
			return true;
		}
	}
	
	private static class CSelect implements ICallable
	{
		@Override
		public String getCmdName()
		{
			return CMD_SELECT;
		}
		
		@Override
		public boolean call(IStorage is, String args) throws InvalidArgumentsException
		{
			if(args.isEmpty())
			{
				is.setSelection(null);
			}
			else if(is.hasObject(args))
			{
				is.setSelection(is.getObject(args));
			}
			else
			{
				throw new InvalidArgumentsException(this, String.format(NOT_FOUND, args));
			}
			
			return true;
		}
		
		private static final String NOT_FOUND = "There is no variable named '%s'.";
	}
	
	private static class CName implements ICallable
	{
		@Override
		public String getCmdName()
		{
			return CMD_NAME;
		}

		@Override
		public boolean call(IStorage is, String args) throws InvalidArgumentsException
		{
			if(args.isEmpty()) throw new InvalidArgumentsException(this, EMPTY);
			
			Variable o = is.getSelection();
			
			if(o == null) throw new InvalidArgumentsException(this, NO_SELECTION);
			
			o.rename(args);
			
			is.setSelection(o);
			
			return true;
		}
		
		private static final String EMPTY = "'Name' field cannot be empty.";
		private static final String NO_SELECTION = "An unnamed variable has to have been selected.";
	}
	
	private static class CList implements ICallable
	{
		@Override
		public String getCmdName()
		{
			return CMD_LIST;
		}
		
		@Override
		public boolean call(IStorage is, String args)
		{
			String[] n = is.getObjectList();
			int i = 0;

			is.getLog().log(LIST, i++, NIL, "null");
			
			for(String name : n)
			{
				if(name.equalsIgnoreCase(UNKNOWN)) continue;
				
				Variable v = is.getObject(name);
				
				is.getLog().log(LIST, i++, v.getReferenceName(), v.getObject().getClass().getSimpleName());
			}

			return true;
		}
		
		private static final String LIST = "%d: %s(%s)";
	}
}
