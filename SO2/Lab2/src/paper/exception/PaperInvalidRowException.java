package paper.exception;

import paper.Paper;

public class PaperInvalidRowException extends PaperException
{
	private static final long serialVersionUID = -2615056793868406859L;

	public PaperInvalidRowException(Paper p, int r)
	{
		super(p, String.format(INVALIDROW, r, p.getContent().length - 1));
	}
	
	private static final String INVALIDROW = "'%d' is invalid. Row indices range form 0 - %d.";
}
