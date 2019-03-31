public class ArithmeticExpression
{
	//假设中值表达式正确
	private String infix;
	private int index;

	public ArithmeticExpression(String infix)
	{
		this.infix = infix;
		this.index = 0;
	}
	public int intValue()
	{
		return index;
	}
	public int term()
	{
		return index;
	}
	public int factor()
	{
		return index;
	}
	public int constant()
	{
		int num = 0;
		int begin = 0;
		char ch = infix.charAt(index);
		//判断符号位
		if(ch == '+'||ch == '-')
			begin = index++;
		else
			begin = index;
		//获得数字
		while(ch>='0'&&ch<='9')
			index++;
		num = Integer.parseInt(infix.substring(begin,index++));
		return num;

	}

}
