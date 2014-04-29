package testing;

public interface IStorage
{
	public Variable getSelection();
	public void setSelection(Variable iw);
	public Logger getLog();
	public boolean hasObject(String name);
	public Variable getObject(String name);
}
