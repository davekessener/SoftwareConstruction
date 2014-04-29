package testing;

import testing.exception.InvalidArgumentsException;
import testing.exception.UnknownCommandException;

public class Variable implements ICallable
{
	private String name;
	private Object o;
	
	public Variable(String name, Object o)
	{
		this.name = name;
		this.o = o;
	}
	
	@Override
	public boolean call(IStorage is, String s) throws UnknownCommandException, InvalidArgumentsException
	{
		throw new UnknownCommandException(s.split(" ")[0]);
	}
	
	public String getReferenceName()
	{
		return name;
	}
	
	public void rename(String name)
	{
		this.name = name;
	}
	
	public Object getObject()
	{
		return o;
	}

	@Override
	public String getCmdName()
	{
		return NO_NAME;
	}
	
	private static final String NO_NAME = "-member-";
}
