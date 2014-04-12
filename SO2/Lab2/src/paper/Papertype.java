package paper;

public interface Papertype
{
	enum PAPERTYPE
	{
		BELLESLETTERS(1),
		SCIENTIFIC(2),
		WORKBOOK(3),
		CD(5),
		OTHER(3);
		
		public final int factor;

		private PAPERTYPE(int f)
		{
			this.factor = f;
		}
	}
}
