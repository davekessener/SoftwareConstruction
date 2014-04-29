import paper.User;
import testing.CommandMake;
import testing.Tester;

public class PaperTester extends Tester
{
	public PaperTester()
	{
	}

	@Override
	protected void registerCommands()
	{
		register(new CommandLoadPaper());
	}

	@Override
	protected void registerTypes(CommandMake make)
	{
		make.registerType(User.class, VariableUser.class);
	}
}
