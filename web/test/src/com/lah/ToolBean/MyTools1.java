package com.lah.ToolBean;
import java.io.UnsupportedEncodingException;
public class MyTools1 {
	public static String toChinese(String str){
		if(str==null) str="";
		try{//通过string类的构造方法将指定的字符串转化为中文
			str=new String(str.getBytes("ISO-8859-1"),"utf-8");
		}
		catch(UnsupportedEncodingException e){
			str="";
			e.printStackTrace();
		}
		return str;
	}

}