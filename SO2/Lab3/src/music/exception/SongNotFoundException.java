package music.exception;

public class SongNotFoundException extends SongException
{
	private static final long serialVersionUID = 456404509032820363L;
	protected String name;

	public SongNotFoundException(String s)
	{
		super(String.format(_F_, s));
		name = s;
	}
	
	public String getSongName() { return name; }
	
	protected static final String _F_ = "Song '%s' could not be found.";
}
