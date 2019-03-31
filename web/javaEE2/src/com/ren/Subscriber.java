package com.ren;

public class Subscriber 
{
	private String name = null;
	private String password = null;
	public Subscriber()
	{
	}
	public Subscriber(String name,String pwd)
	{
		this.name = name;
		this.password = pwd;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getPassword() {
		return password;
	}
	public void setPassword(String password) {
		this.password = password;
	}
}
