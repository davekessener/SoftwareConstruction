package paper;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import paper.exception.PaperInvalidColumnException;
import paper.exception.PaperInvalidRowException;
import paper.exception.PaperReadWriteException;
import paper.exception.PaperWordNotFoundException;

public class Annotation extends Paper
{
	private Map<Integer, String> annotations;
	
	protected Annotation( )
	{
		annotations = new HashMap<Integer, String>();
	}
	
	public Annotation(String n, float p, Papertype.PAPERTYPE t, String[] c) { this(n, p, t.name(), c); }
	public Annotation(String title, float price, String type, String[] content)
	{
		super(title, price, type, content);
		
		annotations = new HashMap<Integer, String>();
	}
	
	public void addAnnotation(String w, String a) throws PaperWordNotFoundException, PaperInvalidRowException, PaperInvalidColumnException
	{
		int[] xy = super.searchWord(w);
		
		addAnnotation(xy[0], xy[1], a);
	}
	
	public String showAnnotation(String w) throws PaperWordNotFoundException, PaperInvalidColumnException, PaperInvalidRowException
	{
		int[] xy = super.searchWord(w);
		
		return showAnnotation(xy[0], xy[1]);
	}
	
	public void addAnnotation(int c, int r, String a) throws PaperInvalidRowException, PaperInvalidColumnException
	{
		if(c < 0 || c >= getWordCount(r)) throw new PaperInvalidColumnException(this, r, c);
		annotations.put(toKey(r, c), a);
	}
	
	public String showAnnotation(int c, int r) throws PaperInvalidColumnException, PaperInvalidRowException
	{
		if(c < 0 || c >= getWordCount(r)) throw new PaperInvalidColumnException(this, r, c);
		return annotations.get(toKey(r, c));
	}
	
	@Override
	public String toString( )
	{
		StringBuilder s = new StringBuilder();
		
		s.append(super.toString()).append('\n').append(annotations.size());
		
		for(int p : annotations.keySet())
		{
			s.append('\n').append(p).append(' ').append(annotations.equals(p));
		}
		
		return s.toString();
	}
	
	@Override
	public void writeToFile(BufferedWriter bw) throws PaperReadWriteException
	{
		try
		{
			bw.write(toString());
		}
		catch(IOException e)
		{
			throw new PaperReadWriteException(this, e);
		}
	}
	
	public static Annotation constructFromFile(String fn) throws PaperReadWriteException
	{
		Annotation a = null;
		
		try
		{
			BufferedReader br = new BufferedReader(new FileReader(fn));
			
			a = constructFromFile(br);
			
			br.close();
		}
		catch(IOException e)
		{
			throw new PaperReadWriteException(null, e);
		}
		
		return a;
	}
	
	public static Annotation constructFromFile(BufferedReader br) throws PaperReadWriteException
	{
		Annotation a = new Annotation();
		
		a.readFromFile(br);
		
		return a;
	}
	
	@Override
	public void readFromFile(BufferedReader br) throws PaperReadWriteException
	{
		try
		{
			super.readFromFile(br);
		
			br.readLine();
		
			int l = Integer.parseInt(br.readLine());

			annotations.clear();
			
			while(l-- > 0)
			{
				String line = br.readLine();

				int p = Integer.parseInt(line.split(" ")[0]);
				String a = line.replaceFirst("[0-9]+ ", "");
				
				annotations.put(p, a);
			}
		}
		catch(IOException e)
		{
			throw new PaperReadWriteException(this, e);
		}
		catch(NumberFormatException e)
		{
			throw new PaperReadWriteException(this, e);
		}
	}
	
	protected static int toKey(int r, int c)
	{
		return r * 1000 + c;
	}
}
