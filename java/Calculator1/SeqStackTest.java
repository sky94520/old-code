import com.datastructure.*;

public class SeqStackTest
{
	public static void main(String[] args)
	{
		String infix="123+10*(45-50+20)/((35-25)*2+10)-11";
		StringBuffer postfix=toPostfix(infix);
		System.out.println(postfix.toString());
		//System.out.println("\ninfix="+infix+"\npostfix="+postfix+"\nvalue="+toValue(postfix));
		
		
		
	}
	//将中值表达式转换为后缀表达式
	public static StringBuffer toPostfix(String infix)
	{
		Stack<String> stack=new SeqStack<>(infix.length());
		StringBuffer postfix=new StringBuffer(infix.length()*2);
		int i=0;
		
		while(i<infix.length())
		{
			char ch=infix.charAt(i);
			switch(ch)
			{
				case '+':
				case '-':
					//只有前一个字符是)或者数字时才为减号
					//是减号
					while(!stack.isEmpty()&&!stack.peek().equals('('))
						postfix.append(stack.pop());
					stack.push(ch+"");
					i++;
					break;
				case '*':
				case '/':
					while(!stack.isEmpty()&&
					(stack.peek().equals("*") || stack.peek().equals("/") || stack.peek().equals("^"))
					)
					    postfix.append(stack.pop());
						stack.push(ch+"");
					i++;
					break;
				case '^':
					while(!stack.isEmpty()&&stack.peek().equals("^"))
						//postfix.append(stack.pop());
						break;
					stack.push(ch+"");
					i++;
					break;
				case '(':
					stack.push(ch+"");
					i++;
					break;
				case ')':
					String out=stack.pop();
					while(out != null&&!out.equals("("))
					{
						postfix.append(out);
						out=stack.pop();
					}
					i++;
					break;
				//遇到数字，添加到后缀表达式
				default:
				while(i<infix.length()&&(ch>='0'&&ch<='9')||ch=='.')
				{
					postfix.append(ch);
					i++;
					if(i<infix.length())
						ch=infix.charAt(i);
				}
				//添加空格作为数值之间的分隔符
				postfix.append(" ");
				break;
			}
		}
		while(!stack.isEmpty())
			postfix.append(stack.pop());
		return postfix;
	}
	public static float toValue(StringBuffer postfix)
	{
		Stack<Float> stack=new SeqStack<>();
		float value=0;
		//默认为正号
		boolean isMinusSign=false;
		
		for(int i=0;i<postfix.length();i++)
		{
			char ch=postfix.charAt(i);
			
			//是否是符号位
			if(ch>='0'&&ch<='9')
			{
				int begin=i;
				
				while(ch!=' ')
					ch=postfix.charAt(++i);
			 	float v=Float.parseFloat(postfix.substring(begin,i));
				v*=isMinusSign==true?-1:1;
				isMinusSign=false;
				stack.push(v);
			}
			else
				if(ch!=' ')
				{
					//如果是符号位，前一位必须不能是数 后一位必须是数
					//如果是符号位 判断符号
					if(i+1<postfix.length()&&postfix.charAt(i+1)>='0'&&postfix.charAt(i+1)<='9')
					{
						if((i-1>=0&&!(postfix.charAt(i-1)>='0'&&postfix.charAt(i-1)<=9))||i==0)
						{
							isMinusSign= ch=='-'?true:false;
							continue;
						}
					}
					//System.out.println("log"+i);
					//出栈两个操作数
					float y=stack.pop(),x=stack.pop();
					
					switch(ch)
					{
						case '+':value=x+y;break;
						case '-':value=x-y;break;
						case '*':value=x*y;break;
						case '/':value=x/y;break;
						case '^':value=(float)Math.pow(x,y);break;
					}
					//显示运算过程
					System.out.println(x+(ch+"")+y+"="+value+",");
					stack.push(value);
				}
		}
		return stack.pop();
	}
}
