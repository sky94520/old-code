import java.lang.*;
public class Color
{
	private int rgb;
	public Color(int rgb)
	{
		this.rgb = rgb;
	}
	public int getRed()
	{
		return (this.rgb>>>16)&0xff;
	}
	public void setRed(int red)
	{
		this.rgb = this.rgb&0xff00ffff|(0xff000000|red<<16);
	}
	public int getGreen()
	{
		return (this.rgb>>>8)&0xff;
	}
	public void setGreen(int green)
	{
	}
	public int getBlue()
	{
		return this.rgb&0xff;
	}
	public void setBlue(int blue)
	{
	}
	public String toString()
	{
		StringBuilder builder = new StringBuilder();
		builder.append("("+this.getRed());
		builder.append(","+this.getGreen());
		builder.append(","+this.getBlue()+")");

		return builder.toString();
	}
}
