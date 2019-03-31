<%@ page language="java" contentType="text/html; charset=gbk"
    pageEncoding="gbk"%>
<%@ page import="java.sql.*" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<jsp:useBean id="upFile" class="com.jspsmart.upload.SmartUpload" scope="page"/>

<head>
<title>公告</title>
</head>
<body>
<center>公告信息</center>
<table border="1">
<tr><th>标题</th><th>内容</th><th>附件</th><th>下载</th></tr>
<%
//连接数据库
try{
	Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
	String username="sa";
	String password = "94520";
	String url="jdbc:sqlserver://localhost:1433;DatabaseName=Bulletin";
	Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
	Connection connection = DriverManager.getConnection(url,username,password);
	//获取Statement
	Statement state = connection.createStatement();
	ResultSet result = state.executeQuery("select * from message");
	while(result.next())
	{
		String title = result.getString("title");
		String content = result.getString("content");
		String fileName = result.getString("filename");
		
		out.print("<tr><td>"+title+"</td>"
				+"<td>"+content+"</td>"
				+"<td>"+fileName+"</td>"
				+"<td><a href=download.jsp?filename="+fileName+">点击下载</a></td></tr>");
	}
}catch(ClassNotFoundException e)
{
	e.printStackTrace();
}
catch(SQLException e)
{
	e.printStackTrace();
}
%>
</table>
</body>
</html>