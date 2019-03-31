public class Test
{
	public static void main(String[] args)
	{
	
		try
		{
			int i=Integer.parseInt("123a");
		}
		
		catch(NumberFormatException e)
		{
			System.out.println("NumberFormatException");
		}
		catch(Exception e)
		{
			System.out.println("Exception");
		}
	}
}
