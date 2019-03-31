package com.lah.valueBean;

import java.io.UnsupportedEncodingException;

public class MyTool 
{
	public static String toChinese(String str)
	{
		if(str == null)
			str="";
		
		try {
			str = new String(str.getBytes("iso-8859-1"),"utf-8");
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			str="";
		}
		return str;
	}
}
