import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

import testing.Logger;


public class BRLog extends BufferedReader
{
	private Logger log;
	private String fn;
	
	public BRLog(String fn, Logger log) throws IOException
	{
		super(new FileReader(fn));

		this.fn = fn;
		this.log = log;
	}

	@Override
	public String readLine( ) throws IOException
	{
		String line = super.readLine();
		
		log.incIndent();
		log.log("### Read from '%s': '%s'", fn, line);
		log.decIndent();
		
		return line;
	}
}
