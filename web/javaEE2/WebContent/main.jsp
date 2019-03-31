<%@ page language="java" contentType="text/html; charset=GBK"
    pageEncoding="GBK"%>
<%@ page import="java.sql.*,com.lah.toolBean.Conn" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=GBK">
<title>留言板</title>
</head>
<%
 //访问数据库，并获得所有信息
 Conn c = new Conn("RealEstateDB","sa","sa");
 String sql = "select * from house";
 ResultSet results = c.executeQuery(sql);
%> 
<body>
<table>
 <caption>所有留言</caption>
 <tr><th>留言人姓名</th><th>留言时间</th><th>留言标题</th><th>留言内容</th></tr>
 <tr>
 <%
 	while(results.next())
 	{
 		String name = results.getString("");
 	}
 %>
 </tr>



</table>
</body>
</html>


