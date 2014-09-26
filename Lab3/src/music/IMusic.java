package music;

public interface IMusic
{
	public abstract typeOfMusic getMusicType();
	
	public static enum typeOfMusic
	{
		DEFAULT,
		CLASSIC,
		POP,
		ROCK,
		TECHNO,
		DIFFERENT;
	}
}
