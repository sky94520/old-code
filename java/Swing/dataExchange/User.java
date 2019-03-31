public class User
{
	private String name;
	private char[] password;

	public User()
	{
		this(null,null);
	}
	public User(String name)
	{
		this(name,null);
	}
	public User(String name,char password[])
	{
		this.name=name;
		this.password=password;
	}
	public String getName()
	{
		return this.name;
	}
	public char[] getPassword()
	{
		return this.password;
	}
}
