package paper;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import paper.exception.PaperReadWriteException;

public class User
{
	private String name;
	private List<Paper> myPapers;
	private List<Annotation> myAnnotations;
	private float total;
	
	protected User( )
	{
		this.myPapers = new ArrayList<Paper>();
		this.myAnnotations = new ArrayList<Annotation>();
	}
	
	public User(String name)
	{
		this();
		this.name = name;
		this.total = 0F;
	}
	
	@Override
	public String toString( )
	{
		StringBuilder s = new StringBuilder();
		
		s.append(name).append('\n').append(total).append('\n');
		
		s.append(myPapers.size());
		for(Paper p : myPapers)
		{
			s.append('\n').append(p.toString());
		}
		
		s.append('\n').append(myAnnotations.size());
		for(Annotation a : myAnnotations)
		{
			s.append('\n').append(a.toString());
		}
		
		return s.toString();
	}
	
	public void addPaper(String fn) throws PaperReadWriteException
	{
		Paper p = Paper.constructFromFile(fn);
		
		if(p != null)
		{
			myPapers.add(p);
			total += p.getPrice() * p.getCostFactor();
		}
	}
	
	public void addAnnotation(String fn) throws PaperReadWriteException
	{
		Annotation a = Annotation.constructFromFile(fn);
		
		if(a != null)
		{
			myAnnotations.add(a);
			
			total += a.getPrice() * a.getCostFactor();
		}
	}
	
	public void changePaperToAnnotation(String name)
	{
		for(Paper p : myPapers)
		{
			if(p.getTitle().equals(name))
			{
				myPapers.remove(p);
				myAnnotations.add(new Annotation(p.getTitle(), p.getPrice(), p.getPaperType(), p.getContent()));
				break;
			}
		}
	}
	
	public void writeToFile(String fn) throws IOException
	{
		writeToFile(new BufferedWriter(new FileWriter(fn)));
	}
	
	public void writeToFile(BufferedWriter bw) throws IOException
	{
		bw.write(toString());
	}
	
	public static User constructFromFile(String fn) throws PaperReadWriteException, IOException
	{
		return constructFromFile(new BufferedReader(new FileReader(fn)));
	}
	
	public static User constructFromFile(BufferedReader br) throws PaperReadWriteException, IOException
	{
		User u = new User();
		
		u.readFromFile(br);
			
		return u;
	}
	
	public void readFromFile(String fn) throws IOException, PaperReadWriteException
	{
		readFromFile(new BufferedReader(new FileReader(fn)));
	}
	
	public void readFromFile(BufferedReader br) throws IOException, PaperReadWriteException
	{
		try
		{
			name = br.readLine();
			br.readLine();
			
			myPapers.clear();
			myAnnotations.clear();
			
			total = 0F;
			
			int pc = Integer.parseInt(br.readLine());
			while(pc-- > 0)
			{
				Paper p = Paper.constructFromFile(br);
				myPapers.add(p);
				total += p.getPrice() * p.getCostFactor();
			}
			
			int ac = Integer.parseInt(br.readLine());
			while(ac-- > 0)
			{
				Annotation a = Annotation.constructFromFile(br);
				myAnnotations.add(a);
				total += a.getPrice() * a.getCostFactor();
			}
		}
		catch(NumberFormatException e)
		{
			throw new IllegalArgumentException(e.getMessage());
		}
	}
	
	public String getName( ) { return name; }
	public float getTotal( ) { return total; }
}
