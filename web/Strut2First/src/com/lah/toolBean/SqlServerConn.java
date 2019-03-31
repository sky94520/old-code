package com.lah.toolBean;

import java.sql.*;
public class SqlServerConn 
{
	Connection conn=null;
	ResultSet rs=null;
	Statement stmt=null;
	String url="jdbc:sqlserver://localhost:1433;DatabaseName=";
	int result=0;
	
	public SqlServerConn(String dataBaseName,String name,String password)
	{
		//加载驱动
		try {
			Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
			//建立连接
			conn = DriverManager.getConnection(url+dataBaseName,name,password);
			stmt=conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE,ResultSet.CONCUR_READ_ONLY,ResultSet.HOLD_CURSORS_OVER_COMMIT);
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	public ResultSet executeQuery(String sql)
	{
		try {
			rs=stmt.executeQuery(sql);
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return rs;
	}
	//数据更新
	public int executeUpdate(String sql)
	{
		try {
			result=stmt.executeUpdate(sql);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return result;
	}
	//断开数据库
	public void closeDB()
	{
		try {
			stmt.close();
			conn.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
}
