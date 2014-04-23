package paper.exception;

import paper.Paper;

public class PaperWordNotFoundException extends PaperException
{
	private static final long serialVersionUID = 1274204954588587079L;

	public PaperWordNotFoundException(Paper p, String w)
	{
		super(p, String.format(WORDNOTFOUND, w));
	}
	
	private static final String WORDNOTFOUND = "Word '%s' could not be found.";
}
