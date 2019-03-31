package com.lah.toolBean;

import java.sql.*;

import java.sql.PreparedStatement;

public class MySqlConn 
{
	private Connection conn = null;
	private Statement stat = null;
	private int result = 0;
	// MySQL的JDBC URL编写方式：jdbc:mysql://主机名称：连接端口/数据库的名称?参数=值
    // 避免中文乱码要指定useUnicode和characterEncoding
    // 执行数据库操作之前要在数据库管理系统上创建一个数据库，名字自己定，
    // 下面语句之前就要先创建education数据库3306
    String url = "jdbc:mysql://localhost:3306/education?"
            + "user=root&password=94520&useUnicode=true&characterEncoding=UTF8";
	public MySqlConn()
	{
		//动态加载mysql驱动
		try 
		{
			Class.forName("com.mysql.jdbc.Driver");
			// 一个Connection代表一个数据库连接
			conn = DriverManager.getConnection(url);
			 // Statement里面带有很多方法，比如executeUpdate可以实现插入，更新和删除等
			this.stat = conn.createStatement();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	public MySqlConn(String dataBase,String user,String password)
	{
		String u = "jdbc:mysql://localhost:3306/"+dataBase
				+"?user="+user+"&password="+password
				+"&useUnicode=true&characterEncoding=UTF8";
		//动态加载mysql驱动
		try 
		{
			Class.forName("com.mysql.jdbc.Driver");
			// 一个Connection代表一个数据库连接
			conn = DriverManager.getConnection(u);
			 // Statement里面带有很多方法，比如executeUpdate可以实现插入，更新和删除等
			this.stat = conn.createStatement();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	public PreparedStatement prepareStatement(String sql) throws SQLException
	{
		return this.conn.prepareStatement(sql);
	}
	public ResultSet executeQuery(String sql)
	{
		ResultSet rs = null;
		try {
			rs=stat.executeQuery(sql);
			
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
			result=stat.executeUpdate(sql);
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
			stat.close();
			conn.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
}
