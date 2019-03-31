<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<%@ page import="java.sql.*" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>Insert title here</title>
</head>
<body>
<%
try{
	Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
	String url="jdbc:sqlserver://localhost:1433;DatabaseName=pay1";
	String name="sa";
	String passwrd="sa";
	//创建数据库连接
	Connection conn = DriverManager.getConnection(url,name,passwrd);
	//创建Statement
	Statement state = conn.createStatement();
	String strSql = "select * from person";
	ResultSet set = state.executeQuery(strSql);
	while(set.next())
	{
		String no = set.getString("No");
		String name1=set.getString("Name");
	%>
	<br><%=no %>
	<br><%=name1 %>
	<%
	}
}catch(ClassNotFoundException e)
{
	e.printStackTrace();
}
%>
</body>
</html>