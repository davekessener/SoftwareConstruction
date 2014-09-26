package paper.exception;

import paper.Paper;

public class PaperReadWriteException extends PaperException
{
	private static final long serialVersionUID = 3324841347722951065L;

	public PaperReadWriteException(Paper p, Exception e)
	{
		super(p, e.getMessage());
	}
}
