package testing;

import testing.exception.InvalidArgumentsException;
import testing.exception.UnknownCommandException;

public interface ICallable
{
	public String getCmdName();
	public boolean call(IStorage is, String args) throws UnknownCommandException, InvalidArgumentsException;
}
