
public class CalService {
	private boolean isSecondNum;
	private String lastOp,firstNum,secondNum;
	private double store;
	private String numString="0123456789.";
	private String opString="+-*/";
	
	public String catNum( String cmd, String text ) {
		String result = cmd;
		//���Ŀǰ��text������0
		if( !text.equals("0") )	{
			if( isSecondNum ) {
				//��isSecondNum��־Ϊfalse
				isSecondNum = false;
			} 
		    else {
				//�շ��ؽ��ΪĿǰ��text�����µ��������
				result = text + cmd;
			}
		}
		//�����.��ͷ������ǰ�油0
		if( result.indexOf(".") == 0 ) {
			result = "0" + result;
		}
		return result;
	}
	
	
	
	public String setOp( String cmd , String text ) {
		//���˲�����������Ϊ�ϴεĲ���
		this.lastOp = cmd;
		//���õ�һ����������ֵ
		this.firstNum = text;
		//���ڶ�����������ֵΪ��
		this.secondNum = null;
		//��isSecondNum��־Ϊtrue
		this.isSecondNum = true;
		//���ؿ�ֵ
		return null;
	}
	
	
	public String cal( String text , boolean isPercent )throws Exception {
			//��ʼ���ڶ���������
			double secondResult = secondNum == null ? Double.valueOf( text ).doubleValue() : Double.valueOf( secondNum ).doubleValue();
			//�������Ϊ0��������
			if( secondResult == 0 && this.lastOp.equals("/") ) {
				return "0";
			}
			//�����"%"��������ڶ���������������������ٳ���100
			if( isPercent ) {
				secondResult = MyMath.multiply( Double.valueOf( firstNum ), MyMath.divide( secondResult, 100 ) ); 
			}
			//�������㣬���ؽ��������һ��������
			if( this.lastOp.equals("+") ) {
				firstNum = String.valueOf(MyMath.add( Double.valueOf( firstNum ), secondResult ) );	
			}
			else if( this.lastOp.equals("-") )	{
				firstNum = String.valueOf(MyMath.subtract( Double.valueOf( firstNum ), secondResult ) );				
			} else if( this.lastOp.equals("*") ) {
				firstNum = String.valueOf(MyMath.multiply( Double.valueOf( firstNum ), secondResult ) );
			}
			else if( this.lastOp.equals("/") ) {
				firstNum = String.valueOf(MyMath.divide( Double.valueOf( firstNum ),  secondResult ) );				
			}
			//���ڶ������������¸�ֵ
			secondNum = secondNum == null ? text : secondNum;
			//��isSecondNum��־Ϊtrue
			this.isSecondNum = true;
			return firstNum;
		}
	
	
	
	public String mCmd( String cmd, String text ) {
		
		if( cmd.equals( "M+" ) ) {
			//�����"M+"����,�հѼ������ۻ���store��
			store = MyMath.add( store, Double.valueOf( text ) );
		} else if( cmd.equals( "MC" ) ) {
			//�����"MC"�����������store
			store = 0;
		} else if( cmd.equals( "MR" ) ) {
			//�����"MR"���������store��ֵ������
			isSecondNum = true;
			return String.valueOf( store );
		} else if( cmd.equals( "MS" ) ) {
			//�����"MS"��������Ѽ��������浽store
			store = Double.valueOf( text ).doubleValue();
		}
		return null;
	}
	
	
	
	public String sqrt(String text) {
		// ��isSecondNum��־Ϊtrue
		this.isSecondNum = true;
		// ������������
		return String.valueOf(Math.sqrt(Double.valueOf(text)));
	}
	
	
	
	
	public String setReciprocal(String text) {
		// ���textΪ0��������
		if (text.equals("0")) {
			return text;
		} else {
			// ��isSecondNum��־Ϊtrue
			this.isSecondNum = true;
			// ������������
			return String.valueOf(MyMath.divide(1, Double.valueOf(text)));
		}
	}

	
	
	public String backSpace(String text) {
		return text.equals("0") || text.equals("") ? "0" : text.substring(0,text.length() - 1);
	}
	
	public String clearAll() {
		// ����һ�ڶ��������ָ�ΪĬ��ֵ
		this.firstNum = "0";
		this.secondNum = "0";
		return this.firstNum;
	}
	
	public String clear() {
		
		return "0";
	}
	//ȡ��
	public String setNegative(String text) {
		double d=Double.valueOf(text).doubleValue();
		double dd=(-1)*d;
		String str=Double.toString(dd);
		return str;
	}
	//��ȡMֵ
	 public double getStore(){
		 return store;
	 }
	 
	public String callMethod(String cmd, String text) throws Exception {
		if (cmd.equals("C")) {
			return clearAll();
		} 
		else if (cmd.equals("CE")) {
			return clear();
		} 
		else if (cmd.equals("Back")) {
			return backSpace(text);
		} 
		else if (numString.indexOf(cmd) != -1) {
			return catNum(cmd, text);
		} 
		else if (opString.indexOf(cmd) != -1) {
			return setOp(cmd, text);
		} 
		else if (cmd.equals("=")) {
			return cal(text, false);
		} 
		else if (cmd.equals("+/-")) {
			return setNegative(text);
		} 
		else if (cmd.equals("1/x")) {
			return setReciprocal(text);
		} 
		else if (cmd.equals("sqrt")) {
			return sqrt(text);
		} 
		else if (cmd.equals("%")) {
			return cal(text, true);
		} 
		else {
			return mCmd(cmd, text);
		}
	}



	



	







}
