package com.game;

import java.io.UnsupportedEncodingException;

public class UserInfo 
{
	private String name;
	private String passwrd;
	public String getName()
	{
		if(name==null)
			return null;
		try 
		{
			byte[] names=name.getBytes("iso-8859-1");
			return new String(names,"utf-8");
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;
	}
	public void setName(String name)
	{
		this.name = name;
	}
	public String getPasswrd()
	{
		return passwrd;
	}
	public void setPasswrd(String passwrd)
	{
		this.passwrd = passwrd;
	}
}