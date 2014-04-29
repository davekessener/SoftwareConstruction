package testing;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.Map;

import testing.exception.InvalidArgumentsException;

public class CommandMake implements ICallable
{
	private Map<String, WrapperTypes> types;
	
	public CommandMake()
	{
		types = new HashMap<String, WrapperTypes>();
	}
	
	public void registerType(Class<?> type, Class<? extends Variable> wrapper)
	{
		types.put(type.getSimpleName().toLowerCase(), new WrapperTypes(type, wrapper));
	}
	
	@Override
	public String getCmdName()
	{
		return CMD_MAKE;
	}

	@Override
	public boolean call(IStorage is, String args) throws InvalidArgumentsException
	{
		String cn = args.split(" ")[0];
		String[] p = args.replaceFirst("[^ ]+ ?", "").split(" ");
		
		if(p.length == 1 && p[0].isEmpty()) p = new String[0];
		
		for(int i = 0 ; i < p.length ; ++i)
		{
			p[i] = p[i].replaceAll("%20", " ");
		}
		
		try
		{
			Class<?> t = null;
			Class<? extends Variable> wt = null;
			
			if(types.containsKey(cn.toLowerCase()))
			{
				WrapperTypes ws = types.get(cn.toLowerCase());

				wt = ws.wrapper;
				t = ws.type;
			}
			else
			{
				wt = null;
				t = Class.forName(cn);
			}
			
			if(t == null)
			{
				throw new InvalidArgumentsException(this, String.format(NAME_NOT_FOUND, cn));
			}
			
			Object o = null;
			Object[] pcs = null;
			
			if(p.length == 0)
			{
				o = t.newInstance();
			}
			else
			{
				Constructor<?>[] cs = t.getConstructors();
				
				pcs = new Object[p.length];
				
				for(int i = 0 ; i < p.length ; ++i)
				{
					char fc = p[i].charAt(0);
					
					if(fc >= '0' && fc <= '9')
					{
						if(p[i].indexOf('.') > 0)
						{
							pcs[i] = Float.parseFloat(p[i]);
						}
						else
						{
							pcs[i] = Integer.parseInt(p[i]);
						}
					}
					else if(fc == '"')
					{
						pcs[i] = p[i].substring(1, p[i].length() - 1);
					}
					else
					{
						pcs[i] = is.getObject(p[i].substring(1));
					}
					
					if(pcs[i] == null) 
					{
						throw new InvalidArgumentsException(this, String.format(CANNOT_DEFER_TYPE, p[i]));
					}
				}
			
				for(Constructor<?> c : cs)
				{
					try
					{
						o = c.newInstance(pcs);
					}
					catch (IllegalArgumentException e) { }
					catch (InstantiationException e) { }
					catch (IllegalAccessException e) { }
					catch (InvocationTargetException e) { }
					
					if(o != null) break;
				}
				
				if(o == null) throw new InvalidArgumentsException(this, String.format(CANNOT_FIND_CONS, args));
			}
			
			if(o != null)
			{
				is.setSelection(wt == null ? new Variable(Tester.UNKNOWN, o) : 
					wt.getConstructor(String.class, t).newInstance(Tester.UNKNOWN, o));
			}
		}
		catch(ClassNotFoundException e)
		{
			e.printStackTrace();
		}
		catch(IllegalAccessException e)
		{
			e.printStackTrace();
		}
		catch(InstantiationException e)
		{
			e.printStackTrace();
		}
		catch(IllegalArgumentException e)
		{
			e.printStackTrace();
		}
		catch(SecurityException e)
		{
			e.printStackTrace();
		}
		catch(InvocationTargetException e)
		{
			e.printStackTrace();
		}
		catch(NoSuchMethodException e)
		{
			e.printStackTrace();
		}

		return true;
	}
	
	private static final String CMD_MAKE = "make";
	private static final String NAME_NOT_FOUND = "'%s' is not a valid type.";
	private static final String CANNOT_DEFER_TYPE = "Cannot defer type from '%s'";
	private static final String CANNOT_FIND_CONS = "Unable to find constructor for '%s'";
	
	private static class WrapperTypes
	{
		public final Class<?> type;
		public final Class<? extends Variable> wrapper;
		
		public WrapperTypes(Class<?> c, Class<? extends Variable> w)
		{
			type = c;
			wrapper = w;
		}
	}
}
