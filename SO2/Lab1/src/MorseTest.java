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
			singleWord(input, log);
			
			return true;
		}
		else if(name.equalsIgnoreCase(TEST_ONE_SENTENCE))
		{
			singleSentence(input, log);
			
			return true;
		}
		else
		{
			return false;
		}
	}
	
	private void singleWord(String input, Logger log) throws TestException
	{
			char c[] = input.toCharArray();
			
			log.log("  Morsecode  |   Decimal  |   Terzial  |  fromCode  | fromDecimal | fromTerzial ");
			log.log("-------------+------------+------------+------------+-------------+--------------");
			
			for(char t : c)
			{
				try
				{
					Morse m = Morse.fromCharacter(t);
				
					log.log("    %s     |    %d     |     %d     |    '%c'     |    '%c'      |    '%c'", 
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
	}
	
	private void singleSentence(String input, Logger log) throws TestException
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
	}

	@Override
	public String[] getTestNames()
	{
		return new String[] {TEST_ONE_WORD, TEST_ONE_SENTENCE};
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
}
