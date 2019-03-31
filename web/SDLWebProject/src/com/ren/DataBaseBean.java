package com.ren;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import javax.naming.Context;
import javax.naming.InitialContext;
import javax.naming.NamingException;
import javax.sql.DataSource;

public class DataBaseBean 
{
	private Connection connection;
	private Statement statement = null;
	public DataBaseBean()
	{
		//获取连接池对象
		try {
			Context context = new InitialContext();
			context = (Context)context.lookup("java:comp/env");
			DataSource ds = (DataSource)context.lookup("TestJNDI");
			connection = ds.getConnection();
			statement = connection.createStatement();
		} catch (NamingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	public ResultSet executeQuery(String sql) throws SQLException
	{
		return statement.executeQuery(sql);
	}
	public int executeUpdate(String sql) throws SQLException
	{
		return statement.executeUpdate(sql);
	}
	public void close() throws SQLException
	{
		statement.close();
		connection.close();
	}
}
