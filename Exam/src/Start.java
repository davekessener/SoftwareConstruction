import java.io.FileNotFoundException;
import java.io.IOException;

public class Start
{
	public static void main(String args[])
	{
		try {
			(new Test()).test();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
