package paper;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class Annotation extends Paper
{
	private Map<Integer, String> annotations;
	
	protected Annotation( )
	{
	}
	
	public Annotation(String title, float price, String type, String[] content)
	{
		super(title, price, type, content);
		
		annotations = new HashMap<Integer, String>();
	}
	
	public void addAnnotation(String w, String a)
	{
		int[] xy = super.searchWord(w);
		
		addAnnotation(xy[0], xy[1], a);
	}
	
	public String showAnnotation(String w)
	{
		int[] xy = super.searchWord(w);
		
		return showAnnotation(xy[0], xy[1]);
	}
	
	public void addAnnotation(int c, int r, String a)
	{
		annotations.put(toKey(r, c), a);
	}
	
	public String showAnnotation(int c, int r)
	{
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
	public void writeToFile(BufferedWriter bw) throws IOException
	{
		bw.write(toString());
	}
	
	public static Annotation constructFromFile(BufferedReader br)
	{
		try
		{
			Annotation a = new Annotation();
		
			a.readFromFile(br);
		
			return a;
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
		
		return null;
	}
	
	@Override
	public void readFromFile(BufferedReader br) throws IOException
	{
		try
		{
			super.readFromFile(br);
		
			br.readLine();
		
			int l = Integer.parseInt(br.readLine());
			
			while(l-- > 0)
			{
				String line = br.readLine();

				int p = Integer.parseInt(line.split(" ")[0]);
				String a = line.replaceFirst("[0-9]+ ", "");
				
				annotations.put(p, a);
			}
		}
		catch(NumberFormatException e)
		{
			throw new IllegalArgumentException(e.getMessage());
		}
	}
	
	protected static int toKey(int r, int c)
	{
		return r * 1000 + c;
	}
}
