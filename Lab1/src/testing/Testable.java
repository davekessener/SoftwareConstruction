package testing;

public interface Testable
{
	public abstract boolean test(String name, Logger log, String input) throws TestException;
	public abstract String[] getTestNames( );
	public abstract String getName( );
	public abstract String getModeName( );
}
