package music;

import java.io.BufferedReader;
import java.io.IOException;

public class SongSet extends Song
{
	protected Song[] setOfSongs;

	public SongSet()
	{
		super();
		setOfSongs = new Song[0];
	}
	
	public SongSet(SongSet ss)
	{
		this(ss.setOfSongs);
	}
	
	public SongSet(Song[] s)
	{
		super(s[0]);
		setOfSongs = new Song[s.length];
		minutes = 0;
		content = new byte[0];
		
		for(int i = 0 ; i < s.length ; ++i)
		{
			setOfSongs[i] = new Song(s[i]);
			minutes += s[i].minutes;
		}
	}
	
	@Override
	public String toString()
	{
		StringBuilder sb = new StringBuilder();
		
		sb.append(setOfSongs.length);
		
		for(Song s : setOfSongs)
		{
			sb.append('\n').append(s.toString());
		}
		
		return sb.toString();
	}
	
	@Override
	public int hashCode()
	{
		int c = getTitle().hashCode();
		
		for(Song s : setOfSongs)
		{
			c ^= s.hashCode();
		}
		
		return c;
	}
	
	@Override
	public boolean equals(Object o)
	{
		if(o instanceof SongSet)
		{
			SongSet ss = (SongSet) o;
			
			if(super.equals(o) && ss.setOfSongs.length == setOfSongs.length)
			{
				for(int i = 0 ; i < setOfSongs.length ; ++i)
				{
					if(!setOfSongs[i].equals(ss.setOfSongs[i])) return false;
				}
				
				return true;
			}
		}
		
		return false;
	}
	
	@Override
	public void readFromFile(BufferedReader br) throws IOException
	{
		setOfSongs = new Song[Integer.parseInt(br.readLine())];
		
		for(int i = 0 ; i < setOfSongs.length ; ++i)
		{
			setOfSongs[i] = new Song();
			setOfSongs[i].readFromFile(br);
			
			if(i == 0)
			{
				id[TITLE_] = setOfSongs[i].id[TITLE_];
				id[COMPOSER_] = setOfSongs[i].id[COMPOSER_];
				id[INTERPRET_] = setOfSongs[i].id[INTERPRET_];
				type = setOfSongs[i].type;
				content = new byte[0];
				minutes = 0;
			}
			
			minutes += setOfSongs[i].minutes;
		}
	}
}
