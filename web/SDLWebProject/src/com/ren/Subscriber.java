package com.ren;
/*用户bean，保存到session中，来保存登陆信息*/
public class Subscriber 
{
	private String username=null;
	private String password=null;
	private String mail=null;
	
	public Subscriber(String username,String password,String mail)
	{
		this.username = username;
		this.password = password;
		this.mail = mail;
	}
	public String getUsername() {
		return username;
	}
	public void setUsername(String username) {
		this.username = username;
	}
	public String getPassword() {
		return password;
	}
	public void setPassword(String password) {
		this.password = password;
	}
	public String getMail() {
		return mail;
	}
}
