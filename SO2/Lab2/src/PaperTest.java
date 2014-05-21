//import java.io.BufferedReader;
//import java.io.FileReader;
//import java.io.IOException;
//import java.util.ArrayList;
//import java.util.List;
//import java.util.Random;
//
//import paper.Paper;
//import paper.Papertype;
//import paper.exception.PaperReadWriteException;
//
//import testing.Logger;
//import testing.TestException;
//import testing.Testable;
//
//public class PaperTest implements Testable
//{
//	@Override
//	public boolean test(String name, Logger log, String input) throws TestException
//	{
//		if(name.equalsIgnoreCase(INIT))
//		{
//			return initialize(log);
//		}
//		else if(name.equalsIgnoreCase(REWRITE))
//		{
//			return rewrite(log);
//		}
//		
//		return false;
//	}
//	
//	private boolean rewrite(Logger log)
//	{
//		try
//		{
//			log.log("Attempting to reconstruct 'Paper' objects from file");
//			log.log("and rewrite it to another file, then comparing both files.");
//			log.incIndent();
//			
//			for(int i = 0 ; i < 6 ; ++i)
//			{
//				String name = "paper" + i + ".txt";
//				Paper p = Paper.constructFromFile(name);
//				
//				if(p == null)
//				{
//					log.log("Err: Couldn't construct paper '%s'", name);
//					
//					return false;
//				}
//				
//				p.writeToFile("_" + name);
//				
//				log.log("Reading and writing '%s' ... [%s]", 
//						name, compareFile(name, "_" + name) ? "SUCCESS" : "FAILURE");
//			}
//			
//			log.decIndent();
//			
//			return true;
//		}
//		catch(PaperReadWriteException e)
//		{
//			e.printStackTrace();
//		}
//		catch(IOException e)
//		{
//			e.printStackTrace();
//		}
//		
//		log.decIndent();
//		
//		return false;
//	}
//	
//	private boolean initialize(Logger log)
//	{
//		try
//		{
//			String[] names = new String[] {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"};
//			Random r = new Random(System.currentTimeMillis());
//			
//			for(int i = 0 ; i < 6 ; ++i)
//			{
//				Paper p = new Paper(
//						names[i], 
//						5F + 10F * r.nextFloat(), 
//						Papertype.PAPERTYPE.values()[r.nextInt(Papertype.PAPERTYPE.values().length)].name(), 
//						readFile("raw" + i + ".txt"));
//
//				p.writeToFile("paper" + i + ".txt");
//				
//				log.log("In file 'paper%d.txt':", i);
//				
//				log.incIndent();
//				
//				for(String s : p.toString().split("\n"))
//				{
//					log.log("%s", s);
//				}
//				
//				log.decIndent();
//				
//				log.println();
//			}
//		}
//		catch(Exception e)
//		{
//			e.printStackTrace();
//			return false;
//		}
//		
//		return true;
//	}
//	
//	private static boolean compareFile(String fn1, String fn2) throws IOException
//	{
//		String[] c1 = readFile(fn1), c2 = readFile(fn2);
//		
//		if(c1.length != c2.length) return false;
//		
//		for(int i = 0 ; i < c1.length ; ++i)
//		{
//			if(!c1[i].equals(c2[i])) return false;
//		}
//		
//		return true;
//	}
//	
//	private static String[] readFile(String fn) throws IOException
//	{
//		BufferedReader br = new BufferedReader(new FileReader(fn));
//		
//		String s;
//		List<String> c = new ArrayList<String>();
//		
//		while((s = br.readLine()) != null)
//		{
//			c.add(s);
//		}
//		
//		br.close();
//		
//		return c.toArray(new String[c.size()]);
//	}
//
//	@Override
//	public String[] getTestNames()
//	{
//		return new String[] {INIT, REWRITE};
//	}
//
//	@Override
//	public String getName()
//	{
//		return "SO2 Lab2 - Papers";
//	}
//
//	@Override
//	public String getModeName()
//	{
//		return "manual";
//	}
//	
//	private static final String INIT = "Initialization";
//	private static final String REWRITE = "Read/Write equivalence";
//}
