<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<%@page import="java.sql.*" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>连接access数据库</title>
</head>
<body>
<%
Class.forName("sun.jdbc.odbc.JdbcOdbcDriver");
Connection conn = DriverManager.getConnection("jdbc:odbc:text");
Statement stat = conn.createStatement();
ResultSet result = stat.executeQuery("select * from person");
if(result.next())
{
	%>
	<table>
	<tr><th>ID</th><th>Name</th><th>Password</th></tr>
	<%
	do
	{
		String id = result.getString("ID");
		String name = result.getString("UserName");
		String password = result.getString("UserPassword");
		%>
		<tr><td><%=id %></td><td><%=name %></td><td><%=password %></td></tr>
		<%
	}while(result.next());
	%>
	</table>
	<%
}
else
{
	out.println("书库库为空");
}
result.close();
stat.close();
conn.close();
int a=3;
int b=4;
%>

</body>

</html>