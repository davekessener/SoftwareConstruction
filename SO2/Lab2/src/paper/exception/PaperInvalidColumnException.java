package paper.exception;

import paper.Paper;

public class PaperInvalidColumnException extends PaperException
{
	private static final long serialVersionUID = 6109750380509329274L;

	public PaperInvalidColumnException(Paper p, int r, int c) throws PaperInvalidRowException
	{
		super(p, String.format(INVALIDCOL, r, c, p.getWordCount(r)));
	}
	
	private static final String INVALIDCOL = "In row %d: '%d' is invalid. Column indices range from 0 - %d.";
}
