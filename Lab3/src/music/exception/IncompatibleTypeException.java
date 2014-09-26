package music.exception;

import music.IMusic;
import music.Song;

public class IncompatibleTypeException extends SongException
{
	private static final long serialVersionUID = -5129251986588625750L;
	protected IMusic.typeOfMusic type;
	protected Song song;
	
	public IncompatibleTypeException(IMusic.typeOfMusic t, Song s)
	{
		super(String.format(_F_, s.getTitle(), t.name()));
		type = t;
		song = s;
	}
	
	public IMusic.typeOfMusic getType() { return type; }
	public Song getSong() { return song; }
	
	protected static final String _F_ = "Song '%s' is not of type '%s'.";
}
