<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<%@ page import="com.ren.DataBaseBean,java.sql.*" %>
<%@ page import="com.ren.Subscriber" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>正在登陆</title>
</head>
<body>
<%
DataBaseBean db = new DataBaseBean();
String username = null;
String mail = request.getParameter("mail");
String password = request.getParameter("password");
String sql = "select * from subscriber where mail='"+mail+"' and password='"+password+"'";
ResultSet result = db.executeQuery(sql);
//如果不为空，登陆成功
if(result.next())
{
	//获取用户名
	username = result.getString(1);
	Subscriber subscriber = new Subscriber(username,password,mail);
	session.setAttribute("subscriber", subscriber);
	//跳转到主页
	response.sendRedirect("index.jsp");
}
else
{
	//返回上一界面
	%>
	<script language="javascript">
	alert("登陆失败，请检测账号和密码是否匹配");
	history.go(-1);
	</script>
	<%
}
result.close();
db.close();
%>
</body>
</html>