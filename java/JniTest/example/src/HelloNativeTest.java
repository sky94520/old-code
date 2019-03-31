
public class HelloNativeTest 
{
	//Class.forName();
	public static void main(String[] args)
	{
		HelloNative.greeting();
	}
	static
	{
		System.loadLibrary("HelloNative");
	}
}
