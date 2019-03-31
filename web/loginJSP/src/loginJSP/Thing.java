package loginJSP;

public class Thing 
{
	private float price = 0;
	private String name="";
	public Thing(String name,float price)
	{
		this.name =name;
		this.price = price;
	}
	public String getName()
	{
		return name;
	}
	public void setName(String name)
	{
		this.name = name;
	}
	public float getPrice()
	{
		return this.price;
	}
	public void setPrice(float price)
	{
		this.price = price;
	}
	public String toString()
	{
		return new String("Ãû³Æ£º"+name+"\n¼Û¸ñ£º"+price);
	}
}
