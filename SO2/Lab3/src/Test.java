import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintStream;

import music.CD;
import music.IMusic;
import music.Library;
import music.Song;
import music.SongSet;
import music.exception.IncompatibleTypeException;
import music.exception.MaxPermissableDurationExceededException;


public class Test
{
	private int ind;
	private PrintStream out;
	private BufferedWriter log;
	
	public Test() { this(System.out); }
	public Test(PrintStream l)
	{
		out = l;
		ind = 0;
		log = null;
	}
	
	public void run()
	{
		boolean success = false;
		try
		{
			log = new BufferedWriter(new FileWriter(LOG_FILE));
		}
		catch(IOException e)
		{
			e.printStackTrace();
			return;
		}
		
		try
		{
			success = doRun();
		}
		catch(IOException e)
		{
			e.printStackTrace();
			
			success = false;
		}
		
		try
		{
			if(!success)
			{
				resetInd();
				print("### ERR: Test failed!");
			}
		
			log.close();
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
		finally
		{
			log = null;
		}
	}
	
	protected boolean doRun() throws IOException
	{
		print("Music - Test Log");
		
// Testing class Song
		print("Test: class Song");
		incInd();
		Song s1 = new Song("ATitle", "AComposer", "AnInterpreter", IMusic.typeOfMusic.CLASSIC,
				4, new byte[] {1, 2, 3, 4, 5, 6, 7, 8});
		Song s2 = new Song("AnotherTitle", "AnotherComposer", IMusic.typeOfMusic.ROCK,
				8, new byte[] {1, 1, 2, 3, 5, 8, 13, 21, 34});
		printf("Equality: %s", s1.equals(s2) ? "[FAILURE!]" : "[SUCCESS!]");
		printf("Self-Equality: %s", s1.equals(s1) ? "[SUCCESS!]" : "[FAILURE!]");
		print("### Song.toString ###");
		print(s2.toString());
		print("###");
		decInd();
// [END]
		
// Testing class SongSet
		print("Test: class SongSet");
		incInd();
		SongSet ss = new SongSet(new Song[] {
				new Song("ASongSet", "ASSComposer", IMusic.typeOfMusic.CLASSIC, 7, new byte[] {
						1, 2, 4, 8, 16, 32, 64, -127
				}),
				new Song("ASongSet", "ASSComposer", IMusic.typeOfMusic.CLASSIC, 11, new byte[] {
						-2, -3, -5, -9, -17, -33, -65, 127
				})
		});
		print("Constructor success.");
		decInd();
// [END]
		
// Testing class Library
		print("Test: class Library");
		incInd();
		Library lib = new Library("TestLib", new Song[] {s1, s2}, new SongSet[] {ss});
		print("Constructor success.");
		decInd();
// [END]
		
// Write Library to file for later use (in CD)
		writeToFile(lib, LTMP_FILE);
		
// Testing class CD
		print("Test: class CD");
		incInd();
		
	// Constructing CD
		BufferedReader br = new BufferedReader(new FileReader(LTMP_FILE));
		CDDebug cd = new CDDebug("SomeCD", 16, br);
		br.close();
		print("Constructor success!");
	
	// Trying to add first song
		print("Adding song1 (no exceptions expected) [...]");
		try
		{
			cd.addSong(s1.getTitle());
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return false;
		}
		print("[SUCCESS!]");
	
	// Trying to add song of incompatible type
		print("Adding song2 (incompatible type. retry after failure) [...]");
		try
		{
			cd.addSong(s2.getTitle());
		}
		catch(IncompatibleTypeException e)
		{
//			e.printStackTrace();
			print(e.toString());
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return false;
		}
		cd.setTypeToDifferent();
		print("### Trying again: [...]");
		try
		{
			cd.addSong(s2.getTitle());
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return false;
		}
		print("[SUCCESS!]");
		
	// Trying to add songset that exceeds the maximum length
		print("Adding songset1 (length exceeded. no retry) [...]");
		try
		{
			cd.addSongSet(ss.getTitle());
		}
		catch(MaxPermissableDurationExceededException e)
		{
//			e.printStackTrace();
			print(e.toString());
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return false;
		}
		print("[SUCCESS!]");
		
	// Add songset anyway and test read/write equality
		print("For testing purposes, cd is resized and songset1 is added anyway.");
		cd.setMaxLength(58);
		try
		{
			cd.addSongSet(ss.getTitle());
		}
		catch(Exception e)
		{
			e.printStackTrace();
			return false;
		}
		
		printf("Self-Equality: %s", cd.equals(cd) ? "[SUCCESS!]" : "[FAILURE!]");
		printf("Read/Write check: %s", readWrite(cd) ? "[SUCCESS!]" : "[FAILURE!]");
// [END]
		
		return true;
	}
	
	private boolean readWrite(CD cd1) throws IOException
	{
		BufferedWriter bw = new BufferedWriter(new FileWriter(CTMP_FILE));
		
		cd1.writeToFile(bw);
		
		bw.close();
		
		BufferedReader br = new BufferedReader(new FileReader(CTMP_FILE));
		
		CD cd2 = new CD();
		cd2.readFromFile(br);
		
		br.close();
		
		return cd1.equals(cd2);
	}
	
	private void writeToFile(Library l, String fn) throws IOException
	{
		BufferedWriter bw = new BufferedWriter(new FileWriter(fn));
		
		l.writeToFile(bw);
		
		bw.close();
	}
	
	private void print(String line) throws IOException
	{
		StringBuilder sb = new StringBuilder();
		
		for(int i = 0 ; i < ind ; ++i) sb.append('\t');
		String pad = sb.toString();
		sb = new StringBuilder();
		
		for(String s : line.split("\n"))
		{
			sb.append(pad).append(s.trim()).append('\n');
		}
		
		String s = sb.toString();
		
		out.flush();
		out.print(s);
		log.write(s);
	}
	
	protected void printf(String s, Object ... o) throws IOException
	{
		print(String.format(s, o));
	}
	
	protected void incInd() { ind++; }
	protected void decInd() { if(ind > 0) ind--; }
	protected void resetInd() { ind = 0; }
	
	private static final String CTMP_FILE = "cd.txt";
	private static final String LTMP_FILE = "lib.txt";
	private static final String LOG_FILE = "log.txt";
}
