package testing;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class InputFile implements Input
{
	private BufferedReader read;
	
	public InputFile(String fn) throws FileNotFoundException
	{
		read = new BufferedReader(new FileReader(fn));
	}

	@Override
	public String readline() throws IOException
	{
		return read.readLine();
	}
}
