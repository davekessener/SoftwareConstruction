package music;

public class Utility {

	static <E> E[] copy(E[] a1, E[] a2)
	{
		for(int i = 0 ; i < a1.length ; ++i)
		{
			a2[i] = a1[i];
		}
		
		return a2;
	}
}
