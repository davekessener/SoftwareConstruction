import java.io.BufferedReader;

import music.CD;


public class CDDebug extends CD
{
	public CDDebug(String name, int maxLength, BufferedReader libFile)
	{
		super(name, maxLength, libFile);
	}

	public void setMaxLength(int i) { this.maxLength = i; }
}
