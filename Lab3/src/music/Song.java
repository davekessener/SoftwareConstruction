package music;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;

public class Song implements IMusic,Cloneable
{
	protected String[] id; // title, composer, interpreter
	protected int minutes; // length in minutes
	protected byte[] content;
	protected typeOfMusic type;
	
	public Song( ) { this("", "", null, typeOfMusic.DEFAULT, 0, new byte[0]); }
	public Song(String t, String c, typeOfMusic ty, int m, byte[] co) { this(t, c, null, ty, m, co); }
	public Song(String title, String composer, String interpreter, typeOfMusic type, int minutes, byte[] content)
	{
		this.id = new String[3];
		this.id[TITLE_] = title;
		this.id[COMPOSER_] = composer;
		this.id[INTERPRET_] = interpreter;
		this.minutes = minutes >= 0 ? minutes : 0;
		this.type = type;
		
		// deep copy of content
		this.content = new byte[content.length];
		for(int i = 0 ; i < content.length ; ++i)
		{
			this.content[i] = content[i];
		}
	}
	
	// copy-constructor
	public Song(Song s)
	{
		this(s.id[TITLE_], s.id[COMPOSER_], s.id[INTERPRET_], s.type, s.minutes, s.content);
	}
	
	@Override
	public Object clone()
	{
		try
		{
			Song s = (Song) super.clone();
			s.id = (String[]) id.clone();
			s.content = (byte[]) content.clone();
			return s;
		}
		catch(CloneNotSupportedException e)
		{
			return null;
		}
	}
	
	@Override
	public String toString()
	{
		StringBuilder s = new StringBuilder();
		
		s.append(getTitle()).append('\n');
		s.append(getComposer()).append('\n');
		s.append(getInterpreter()).append('\n');
		s.append(type.name()).append('\n');
		s.append(minutes).append('\n');
		s.append(content.length);
		
		for(int i = 0 ; i < content.length ; ++i)
		{
			s.append('\n').append(content[i]);
		}
		
		return s.toString();
	}
	
	@Override
	public int hashCode()
	{
		return getTitle().hashCode() ^ content.length;
	}
	
	@Override
	public boolean equals(Object o)
	{
		if(o == null) return false;
		else if(o == this) return true;
		else if(o instanceof Song)
		{
			Song s = (Song) o;
			
			if(s.getTitle().equals(getTitle()) &&
					s.getComposer().equals(getComposer()) &&
					s.getInterpreter().equals(getInterpreter()) &&
					s.type == type && s.minutes == minutes &&
					s.content.length == content.length)
			{
				for(int i = 0 ; i < content.length ; ++i)
				{
					if(content[i]  != s.content[i]) return false;
				}
				
				return true;
			}
		}
		
		return false;
	}
	
	public void writeToFile(BufferedWriter bw) throws IOException
	{
		bw.write(toString());
	}
	
	public void readFromFile(BufferedReader br) throws IOException
	{
		setTitle(br.readLine());
		setComposer(br.readLine());
		setInterpreter(br.readLine());
		type = typeOfMusic.valueOf(br.readLine());
		minutes = Integer.parseInt(br.readLine());
		content = new byte[Integer.parseInt(br.readLine())];
		
		for(int i = 0 ; i < content.length ; ++i)
		{
			content[i] = Byte.parseByte(br.readLine());
		}
	}
	
	public String getTitle() { return id[TITLE_]; }
	public String getComposer() { return id[COMPOSER_]; }
	public String getInterpreter() { return id[INTERPRET_] == null ? getComposer() : id[INTERPRET_]; }
	public int getLengthInMinutes() { return minutes; }
	public byte[] getContent()
	{
		byte[] c = new byte[content.length];
		
		for(int i = 0 ; i < c.length ; ++i)
		{
			c[i] = content[i];
		}
		
		return c;
	}
	
	@Override
	public typeOfMusic getMusicType()
	{
		return type;
	}
	
	public void setTitle(String title) { if(title != null) id[TITLE_] = title; }
	public void setComposer(String composer) { if(composer != null) id[COMPOSER_] = composer; }
	public void setInterpreter(String inter) { id[INTERPRET_] = id[COMPOSER_].equals(inter) ? null : inter; }
	public void setMusicType(typeOfMusic t) { if(t != null) type = t; }
	public void setLengthInMinutes(int l) { if(l >= 0) minutes = l; }
	public void setContent(byte[] c)
	{
		if(c == null) return;
		
		content = new byte[c.length];
		
		for(int i = 0 ; i < c.length ; ++i)
		{
			content[i] = c[i];
		}
	}
	
	protected static final int TITLE_ = 0;
	protected static final int COMPOSER_ = 1;
	protected static final int INTERPRET_ = 2;
}
