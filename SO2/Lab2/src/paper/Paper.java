package paper;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Paper
{
	private String title;
	private float price;
	private int factor;
	private String type;
	private String[] content;
	private int[] wpL;
	
	public Paper(String title, float price, String type, String[] content)
	{
		this.title = title;
		this.price = price;
		this.factor = searchTypeFactor(type);
		this.type = type;
		this.content = new String[content.length];
		this.wpL = new int[content.length];
		
		for(int i = 0 ; i < content.length ; ++i)
		{
			this.content[i] = content[i];
			this.wpL[i] = getWordPerLine(content[i]);
		}
	}
	
	public int[] searchWord(String w)
	{
		w = w.replaceAll("[^0-9a-zA-Z]+", "");
		
		for(int r = 0 ; r < content.length ; ++r)
		{
			String ws[] = content[r].split("[^0-9a-zA-Z]+");
			
			for(int c = 0 ; c < ws.length ; ++c)
			{
				if(w.equals(ws[c])) return new int[] {c, r};
			}
		}
		
		return null;
	}
	
	public String getWord(int c, int r)
	{
		if(r < 0 || r >= content.length) return null;
		
		String ws[] = content[r].split("[^0-9a-zA-Z]+");
		
		if(c < 0 || c >= ws.length) return null;
		
		return ws[c];
	}
	
	public void writeToFile(BufferedWriter bw) throws IOException
	{
		bw.write(toString());
	}
	
	public static Paper readFromFile(BufferedReader br)
	{
		try
		{
			String title = br.readLine();
			float price = Float.parseFloat(br.readLine());
			String type = br.readLine();
			int l = Integer.parseInt(br.readLine());
			List<String> c = new ArrayList<String>();
			
			for(int i = 0 ; i < l ; ++i)
			{
				c.add(br.readLine());
			}
			
			String[] content = c.toArray(new String[l]);
			
			return new Paper(title, price, type, content);
		}
		catch(NumberFormatException e)
		{
			e.printStackTrace();
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
		
		return null;
	}
	
	@Override
	public String toString( )
	{
		StringBuilder s = new StringBuilder();
		
		s.append(title + "\n" + price + "\n" + type + "\n" + content.length + "\n");
		
		for(String l : content)
		{
			s.append(l).append('\n');
		}
		
		for(int i : wpL)
		{
			s.append(i).append(' ');
		}
		
		return s.toString();
	}

	protected static int getWordPerLine(String line)
	{
		return line.split("[^0-9a-zA-Z]+").length;
	}
	
	protected static int searchTypeFactor(String name)
	{
		Papertype.PAPERTYPE p = Papertype.PAPERTYPE.valueOf(name);
		
		return p == null ? Papertype.PAPERTYPE.OTHER.factor : p.factor;
	}
	
	public String getTitle( ) { return title; }
	public float getPrice( ) { return price; }
	public int getCostFactor( ) { return factor; }
}
