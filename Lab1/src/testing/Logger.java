package testing;

import java.io.OutputStream;
import java.io.PrintStream;

public abstract class Logger extends PrintStream
{
	private int indent = 0;
	
	public Logger(OutputStream out)
	{
		super(out);
	}

	protected abstract void out(String s);
	
	public void log(String s, Object ... o)
	{
		log_(s + '\n', o);
	}
	
	public void log_(String s, Object ... o)
	{
		String idt = "";
		for(int i = 0 ; i < indent ; ++i) idt += '\t';
		out(String.format(idt + s, o));
	}
	
	public void incIndent() { ++indent; }
	public void decIndent() { --indent; }
}
