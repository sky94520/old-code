class HelloNativeTest
{
	public static void main(String[] args)
	{
		HelloNative.greeting();

		HelloNative.print(8, 4, 3.14);
	}
	static
	{
		System.loadLibrary("HelloNative");
	}
}