package paper.exception;

import paper.Paper;

@SuppressWarnings("serial")
public abstract class PaperException extends Exception
{
	public PaperException(Paper p, String msg)
	{
		super(String.format(PEX, msg, (p == null ? STATIC : p.toString())));
	}
	
	private static final String STATIC = "--- static ---";
	private static final String PEX = "%s: in '%s'";
}
