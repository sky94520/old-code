public class ArithmeticExpression
{
	//������ֵ���ʽ��ȷ
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
		//�жϷ���λ
		if(ch == '+'||ch == '-')
			begin = index++;
		else
			begin = index;
		//�������
		while(ch>='0'&&ch<='9')
			index++;
		num = Integer.parseInt(infix.substring(begin,index++));
		return num;

	}

}
