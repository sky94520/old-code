import java.math.BigDecimal;
//import java.text.DecimalFormat;
//import java.text.NumberFormat;

public class MyMath {
	public static double add( double num1, double num2 )
	{
		
		BigDecimal b1 = new BigDecimal(Double.valueOf(num1));
		BigDecimal b2 = new BigDecimal(Double.valueOf(num2));
		BigDecimal b3= b1.add(b2);
		return  b3.setScale(2,BigDecimal.ROUND_HALF_UP).doubleValue(); 
	}
	
	public static double subtract ( double num1, double num2 )
	{
		 BigDecimal b1 = new BigDecimal(Double.valueOf(num1));
		 BigDecimal b2 = new BigDecimal(Double.valueOf(num2));
		 BigDecimal b3= b1.subtract(b2);
         return b3.setScale(2,BigDecimal.ROUND_HALF_UP).doubleValue(); 
	}
	
	
	public static double multiply ( double num1, double num2 )
	{
		 BigDecimal b1 = new BigDecimal(Double.valueOf(num1));
		 BigDecimal b2 = new BigDecimal(Double.valueOf(num2));
		 BigDecimal b3= b1.multiply(b2);
		 return b3.setScale(2,BigDecimal.ROUND_HALF_UP).doubleValue(); 
	}
	
	
	public static double divide ( double num1, double num2 )
	{
		 BigDecimal b1 = new BigDecimal(Double.valueOf(num1));
		 BigDecimal b2 = new BigDecimal(Double.valueOf(num2));
		 BigDecimal b3= b1.divide(b2);
		 return b3.setScale(2,BigDecimal.ROUND_HALF_UP).doubleValue();   
	}
}
