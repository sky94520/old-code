<%@ page language="java" contentType="text/html; charset=gbk"
    pageEncoding="gbk"%>
<%@ page import="java.sql.*" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<jsp:useBean id="upFile" class="com.jspsmart.upload.SmartUpload" scope="page"/>

<head>
<title>����</title>
</head>
<body>
<center>������Ϣ</center>
<table border="1">
<tr><th>����</th><th>����</th><th>����</th><th>����</th></tr>
<%
//�������ݿ�
try{
	Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
	String username="sa";
	String password = "94520";
	String url="jdbc:sqlserver://localhost:1433;DatabaseName=Bulletin";
	Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
	Connection connection = DriverManager.getConnection(url,username,password);
	//��ȡStatement
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
				+"<td><a href=download.jsp?filename="+fileName+">�������</a></td></tr>");
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