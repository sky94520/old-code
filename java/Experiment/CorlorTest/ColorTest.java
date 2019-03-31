public class ColorTest
{
	public static void main(String[] args)
	{
		Color color = new Color(0xff60ff00);
		System.out.println(color.toString());

		color.setRed(200);
		System.out.println(color.toString());

		//System.out.println(0xff00ffff>>>8);
	}
}
