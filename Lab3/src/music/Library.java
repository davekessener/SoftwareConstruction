package music;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;

public class Library
{
	protected String name;
	protected Song[] songs;
	protected SongSet[] songSets;
	
	public Library() { this("", new Song[0], new SongSet[0]); }
	public Library(String n) { this(n, new Song[0], new SongSet[0]); }
	public Library(String n, SongSet[] s) { this(n, new Song[0], s); }
	public Library(String n, Song[] s) { this(n, s, new SongSet[0]); }
	public Library(String name, Song[] songs, SongSet[] songSets)
	{
		this.name = name;
		this.songs = new Song[songs.length];
		this.songSets = new SongSet[songSets.length];
		
		for(int i = 0 ; i < songs.length ; ++i)
		{
			this.songs[i] = new Song(songs[i]);
		}
		
		for(int i = 0 ; i < songSets.length ; ++i)
		{
			this.songSets[i] = new SongSet(songSets[i]);
		}
	}
	
	public Library(Library l)
	{
		this(l.name, l.songs, l.songSets);
	}
	
	@Override
	public String toString()
	{
		StringBuilder s = new StringBuilder();
		
		s.append(name).append('\n');

		s.append(songs.length).append('\n');
		for(int i = 0 ; i < songs.length ; ++i)
		{
			s.append(songs[i].toString()).append('\n');
		}
		
		s.append(songSets.length);
		for(int i = 0 ; i < songSets.length ; ++i)
		{
			s.append('\n').append(songSets[i].toString());
		}
		
		return s.toString();
	}
	
	@Override
	public int hashCode()
	{
		int c = name.hashCode();
		
		for(Song s : songs)
		{
			c ^= s.hashCode();
		}
		
		for(SongSet ss : songSets)
		{
			c ^= ss.hashCode();
		}
		
		return c;
	}
	
	@Override
	public boolean equals(Object o)
	{
		if(o == null) return false;
		else if(o == this) return true;
		else if(o instanceof Library)
		{
			Library l = (Library) o;
			
			if(l.name.equals(name) && 
					l.songs.length == songs.length && 
					l.songSets.length == songSets.length)
			{
				for(int i = 0 ; i < songs.length ; ++i)
				{
					if(!songs[i].equals(l.songs[i])) return false;
				}
				
				for(int i = 0 ; i < songSets.length ; ++i)
				{
					if(!songSets[i].equals(l.songSets[i])) return false;
				}
				
				return true;
			}
		}
		
		return false;
	}
	
	public int findSong(String sname)
	{
		for(int i = 0 ; i < songs.length ; ++i)
		{
			if(songs[i].getTitle().equals(sname)) return i + 1;
		}
		
		return 0;
	}
	
	public int findSongSet(String sname)
	{
		for(int i = 0 ; i < songSets.length ; ++i)
		{
			if(songSets[i].getTitle().equals(sname)) return i + 1;
		}
		
		return 0;
	}
	
	public Song getSong(int i)
	{
		return songs[i - 1];
	}
	
	public SongSet getSongSet(int i)
	{
		return songSets[i - 1];
	}
	
	public void writeToFile(BufferedWriter bw) throws IOException
	{
		bw.write(toString());
	}
	
	public void readFromFile(BufferedReader br) throws IOException
	{
		name = br.readLine();
		
		songs = new Song[Integer.parseInt(br.readLine())];
		for(int i = 0 ; i < songs.length ; ++i)
		{
			songs[i] = new Song();
			songs[i].readFromFile(br);
		}
		
		songSets = new SongSet[Integer.parseInt(br.readLine())];
		for(int i = 0 ; i < songSets.length ; ++i)
		{
			songSets[i] = new SongSet();
			songSets[i].readFromFile(br);
		}
	}
}
