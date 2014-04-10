import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

import morsecode.Morse;
import morsecode.MorseException;
import testing.Logger;
import testing.TestException;
import testing.Testable;

public class MorseTest implements Testable
{
	@Override
	public boolean test(String name, Logger log, String input) throws TestException
	{
		if(name.equalsIgnoreCase(TEST_ONE_WORD))
		{
			return singleWord(input, log);
		}
		else if(name.equalsIgnoreCase(TEST_ONE_SENTENCE))
		{
			return singleSentence(input, log);
		}
		else if(name.equalsIgnoreCase(TEST_FILE))
		{
			return testFile(input, log);
		}
		else
		{
			return false;
		}
	}
	
	private boolean testFile(String input, Logger log) throws TestException
	{
		BufferedReader r = null;
		String txt = "";
		
		try
		{
			r = new BufferedReader(new FileReader(input));
		}
		catch(FileNotFoundException e)
		{
			throw new TestException(e);
		}
		
		try
		{
			String p;
			
			while((p = r.readLine()) != null)
			{
				txt += p;
				log.log("%s", p);
			}
			
			log.log("\n");
		
			r.close();
		}
		catch(IOException e)
		{
			throw new TestException(e);
		}
			
		return singleSentence(txt, log);
	}
	
	private boolean singleWord(String input, Logger log) throws TestException
	{
			char c[] = input.toCharArray();
			
			log.log("  Morsecode  |   Decimal  |   Terzial  |  fromCode  | fromDecimal | fromTerzial ");
			log.log("-------------+------------+------------+------------+-------------+--------------");
			
			for(char t : c)
			{
				try
				{
					Morse m = Morse.fromCharacter(t);
				
					log.log("    %s     |    %d    |     %d     |    '%c'     |    '%c'      |    '%c'", 
							m.getMorseCode(), m.getDecimal(), m.getTerzial(),
						Morse.fromCode(m.getMorseCode()).getCharacter(),
						Morse.fromDecimal(m.getDecimal()).getCharacter(),
						Morse.fromTerzial(m.getTerzial()).getCharacter());
				}
				catch(MorseException e)
				{
					throw new TestException(e);
				}
			}
			
			return true;
	}
	
	private boolean singleSentence(String input, Logger log) throws TestException
	{
			String ss[] = input.replaceAll("[^ \t.,!?a-zA-Z]", "").split("[ \t!?.,]+");
			int ml = 0;
			
			for(String s : ss)
			{
				if(s.length() > ml) ml = s.length();
			}
			
			for(String s : ss)
			{
				try
				{
					char cs[] = s.toCharArray();
					String o = String.format("'%s': ", s.toLowerCase());
					
					for(int i = ml - s.length() ; i > 0 ; --i) o += ' ';
					
					for(char c : cs)
					{
						o += String.format("%s  ", Morse.fromCharacter(c).getMorseCode());
					}
				
					log.log(o);
				}
				catch(MorseException e)
				{
					throw new TestException(e);
				}
			}
			
			return true;
	}

	@Override
	public String[] getTestNames()
	{
		return new String[] {TEST_ONE_WORD, TEST_ONE_SENTENCE, TEST_FILE};
	}

	@Override
	public String getName()
	{
		return "SO2 - Lab1: Morsecode";
	}

	@Override
	public String getModeName()
	{
		return "simple input";
	}
	
	private static final String TEST_ONE_WORD = "a single word";
	private static final String TEST_ONE_SENTENCE = "a single sentence";
	private static final String TEST_FILE = "a file";
}
