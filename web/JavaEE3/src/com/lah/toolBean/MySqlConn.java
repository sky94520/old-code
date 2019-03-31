package com.lah.toolBean;

import java.sql.*;

import java.sql.PreparedStatement;

public class MySqlConn 
{
	private Connection conn = null;
	private Statement stat = null;
	private int result = 0;
	// MySQL��JDBC URL��д��ʽ��jdbc:mysql://�������ƣ����Ӷ˿�/���ݿ������?����=ֵ
    // ������������Ҫָ��useUnicode��characterEncoding
    // ִ�����ݿ����֮ǰҪ�����ݿ����ϵͳ�ϴ���һ�����ݿ⣬�����Լ�����
    // �������֮ǰ��Ҫ�ȴ���education���ݿ�3306
    String url = "jdbc:mysql://localhost:3306/education?"
            + "user=root&password=94520&useUnicode=true&characterEncoding=UTF8";
	public MySqlConn()
	{
		//��̬����mysql����
		try 
		{
			Class.forName("com.mysql.jdbc.Driver");
			// һ��Connection����һ�����ݿ�����
			conn = DriverManager.getConnection(url);
			 // Statement������кܶ෽��������executeUpdate����ʵ�ֲ��룬���º�ɾ����
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
		//��̬����mysql����
		try 
		{
			Class.forName("com.mysql.jdbc.Driver");
			// һ��Connection����һ�����ݿ�����
			conn = DriverManager.getConnection(u);
			 // Statement������кܶ෽��������executeUpdate����ʵ�ֲ��룬���º�ɾ����
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
	//���ݸ���
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
	//�Ͽ����ݿ�
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
