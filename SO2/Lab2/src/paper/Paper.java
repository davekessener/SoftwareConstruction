package paper;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

import paper.exception.PaperInvalidColumnException;
import paper.exception.PaperInvalidRowException;
import paper.exception.PaperReadWriteException;
import paper.exception.PaperWordNotFoundException;

public class Paper
{
	private String title;
	private float price;
	private int factor;
	private String type;
	private String[] content;
	private int[] wpL;
	
	protected Paper( )
	{
	}
	
	public Paper(String n, float p, Papertype.PAPERTYPE t, String[] c) { this(n, p, t.name(), c); }
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
			this.wpL[i] = getWordsPerLine(content[i]);
		}
	}
	
	public int[] searchWord(String w) throws PaperWordNotFoundException
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
		
		throw new PaperWordNotFoundException(this, w);
	}
	
	public String getWord(int c, int r) throws PaperInvalidRowException, PaperInvalidColumnException
	{
		if(r < 0 || r >= content.length) throw new PaperInvalidRowException(this, r);
		
		String ws[] = content[r].split("[^0-9a-zA-Z]+");
		
		if(c < 0 || c >= ws.length) throw new PaperInvalidColumnException(this, r, c);
		
		return ws[c];
	}
	
	public void writeToFile(String fn) throws PaperReadWriteException
	{
		try
		{
			BufferedWriter bw = new BufferedWriter(new FileWriter(fn));
			writeToFile(bw);
			bw.close();
		}
		catch(IOException e)
		{
			throw new PaperReadWriteException(this, e);
		}
	}
	
	public static Paper constructFromFile(String fn) throws PaperReadWriteException
	{
		try
		{
			BufferedReader br = new BufferedReader(new FileReader(fn));
			
			Paper p = constructFromFile(br);
			
			br.close();
		
			return p;
		}
		catch(IOException e)
		{
			throw new PaperReadWriteException(null, e);
		}
	}
	
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
	
	public static Paper constructFromFile(BufferedReader br) throws PaperReadWriteException
	{
		Paper p = new Paper();
		
		p.readFromFile(br);
		
		return p;
	}
	
	public void readFromFile(String fn) throws PaperReadWriteException
	{
		try
		{
			BufferedReader br = new BufferedReader(new FileReader(fn));
		
			readFromFile(br);
		
			br.close();
		}
		catch(IOException e)
		{
			throw new PaperReadWriteException(this, e);
		}
	}
	
	public void readFromFile(BufferedReader br) throws PaperReadWriteException
	{
		try
		{
			title = br.readLine();
			price = Float.parseFloat(br.readLine());
			type = br.readLine();
			factor = searchTypeFactor(type);
			int l = Integer.parseInt(br.readLine());
			content = new String[l];
			wpL = new int[l];
			
			for(int i = 0 ; i < l ; ++i)
			{
				String line = br.readLine();

				content[i] = line;
				wpL[i] = getWordsPerLine(line);
			}
			
			br.readLine();
		}
		catch(NumberFormatException e)
		{
			throw new PaperReadWriteException(this, e);
		}
		catch(IOException e)
		{
			throw new PaperReadWriteException(this, e);
		}
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

	protected static int getWordsPerLine(String line)
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
	public String getPaperType( ) { return type; }
	public String[] getContent( )
	{
		String[] r = new String[content.length];
		
		for(int i = 0 ; i < content.length ; ++i)
		{
			r[i] = content[i];
		}
		
		return r;
	}
	
	public int getRowCount() { return content.length; }
	public int getWordCount(int r) throws PaperInvalidRowException
	{
		if(r < 0 || r >= content.length) throw new PaperInvalidRowException(this, r);
		
		return getWordsPerLine(content[r]);
	}
}
