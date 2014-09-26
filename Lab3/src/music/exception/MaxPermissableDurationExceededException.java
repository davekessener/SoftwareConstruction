package music.exception;

import music.Song;

public class MaxPermissableDurationExceededException extends SongException
{
	private static final long serialVersionUID = -598600096276341545L;
	protected int max;
	protected Song song;
	
	public MaxPermissableDurationExceededException(int m, Song s)
	{
		super(String.format(_F_, s.getTitle(), m));
		max = m;
		song = s;
	}
	
	public int getMaxDuration() { return max; }
	public Song getSong() { return song; }
	
	protected static final String _F_ = "Song '%s''s addition would exceed the allowed duration of %d minutes.";
}
