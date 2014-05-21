package music;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;

import music.exception.IncompatibleTypeException;
import music.exception.MaxPermissableDurationExceededException;
import music.exception.SongNotFoundException;

public class CD
{
	protected String name;
	protected Library library;
	protected BufferedReader libFile;
	protected int duration, maxLength;
	protected IMusic.typeOfMusic type;
	protected int[][] tracks;
	protected int tc;
	
	public CD() { this("", 0, null); }
	public CD(String name, int maxLength, BufferedReader libFile)
	{
		this.name = name;
		this.maxLength = maxLength;
		this.libFile = libFile;
		library = new Library();
		duration = 0;
		type = IMusic.typeOfMusic.DEFAULT;
		tc = 0;
		tracks = new int[0][2];
		
		if(libFile != null)
			try
			{
				library.readFromFile(libFile);
			}
			catch(IOException e)
			{
				e.printStackTrace();
				this.libFile = null;
				this.library = new Library();
			}
	}
	
	@Override
	public String toString()
	{
		StringBuilder s = new StringBuilder();
		
		s.append(name).append('\n');
		s.append(maxLength).append('\n');
		s.append(library.toString()).append('\n');
		s.append(duration).append('\n');
		s.append(type.name()).append('\n');
		s.append(tc);
		
		for(int i = 0 ; i < tc ; ++i)
		{
			s.append('\n').append(tracks[i][0]);
			s.append('\n').append(tracks[i][1]);
		}
		
		return s.toString();
	}
	
	@Override
	public int hashCode()
	{
		return name.hashCode() ^ library.hashCode();
	}
	
	@Override
	public boolean equals(Object o)
	{
		if(o instanceof CD)
		{
			CD cd = (CD) o;
			
			if(cd.name.equals(name) && cd.maxLength == maxLength &&
					cd.type == type && cd.duration == duration &&
					cd.tc == tc && cd.library.equals(library))
			{
				for(int i = 0 ; i < tc ; ++i)
				{
					if(tracks[i][0] != cd.tracks[i][0] ||
							tracks[i][1] != cd.tracks[i][1]) 
						return false;
				}
				
				return true;
			}
		}
		
		return false;
	}
	
	public void setTypeToDifferent() { type = IMusic.typeOfMusic.DIFFERENT; }
	
	public void addSong(String sname) throws SongNotFoundException, 
					IncompatibleTypeException, MaxPermissableDurationExceededException
	{
		int i = library.findSong(sname);
		
		if(i == 0) throw new SongNotFoundException(sname);
		
		Song s = library.getSong(i);
		
		if(type != IMusic.typeOfMusic.DIFFERENT && type != IMusic.typeOfMusic.DEFAULT && 
				type != s.getMusicType())
			throw new IncompatibleTypeException(type, s);
		if(duration + s.getLengthInMinutes() > maxLength)
			throw new MaxPermissableDurationExceededException(maxLength, s);
		
		if(type == IMusic.typeOfMusic.DEFAULT) type = s.getMusicType();
		duration += s.getLengthInMinutes();

		resize();
		
		tracks[tc++] = new int[] {i, 0};
	}
	
	public void addSongSet(String sname) throws SongNotFoundException, 
					IncompatibleTypeException, MaxPermissableDurationExceededException
	{
		int i = library.findSongSet(sname);
		
		if(i == 0) throw new SongNotFoundException(sname);
		
		SongSet s = library.getSongSet(i);
		
		if(type != IMusic.typeOfMusic.DIFFERENT && type != IMusic.typeOfMusic.DEFAULT &&
				type != s.getMusicType())
			throw new IncompatibleTypeException(type, s);
		if(duration + s.getLengthInMinutes() > maxLength)
			throw new MaxPermissableDurationExceededException(maxLength, s);
		
		if(type == IMusic.typeOfMusic.DEFAULT) type = s.getMusicType();
		duration += s.getLengthInMinutes();

		resize();
		
		tracks[tc++] = new int[] {0, i};
	}
	
	public void writeToFile(BufferedWriter bw) throws IOException
	{
		bw.write(toString());
	}
	
	public void readFromFile(BufferedReader br) throws IOException
	{
		name = br.readLine();
		maxLength = Integer.parseInt(br.readLine());
		library.readFromFile(br);
		duration = Integer.parseInt(br.readLine());
		type = IMusic.typeOfMusic.valueOf(br.readLine());
		tc = Integer.parseInt(br.readLine());
		
		tracks = new int[tc][2];
		for(int i = 0 ; i < tc ; ++i)
		{
			tracks[i][0] = Integer.parseInt(br.readLine());
			tracks[i][1] = Integer.parseInt(br.readLine());
		}
	}
	
	protected void resize()
	{
		if(tc == tracks.length)
		{
			int[][] t = new int[tracks.length * 2 + 1][2];
			for(int i = 0 ; i < tracks.length ; ++i)
			{
				t[i] = tracks[i];
			}
			tracks = t;
		}
	}
}
