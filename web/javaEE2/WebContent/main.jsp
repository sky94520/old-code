<%@ page language="java" contentType="text/html; charset=GBK"
    pageEncoding="GBK"%>
<%@ page import="java.sql.*,com.lah.toolBean.Conn" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=GBK">
<title>���԰�</title>
</head>
<%
 //�������ݿ⣬�����������Ϣ
 Conn c = new Conn("RealEstateDB","sa","sa");
 String sql = "select * from house";
 ResultSet results = c.executeQuery(sql);
%> 
<body>
<table>
 <caption>��������</caption>
 <tr><th>����������</th><th>����ʱ��</th><th>���Ա���</th><th>��������</th></tr>
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


