package com.ren;

public class UserTable 
{
	private String username = null;
	private String password = null;
	public UserTable()
	{
		
	}
	public UserTable(String username,String password)
	{
		this.username = username;
		this.password = password;
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
}
