package testing;

public interface Input
{
	public abstract String getInputFor(String t) throws TestException;
	public abstract boolean needsEcho();
	public abstract boolean needsPrompt();
}
