<%@ page language="java" contentType="text/html; charset=GBK"
    pageEncoding="GBK"%>
<%@ page import="com.ren.Subscriber" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>实验二</title>
</head>
<%
//先检测用户是否已经登陆
Subscriber user = (Subscriber)session.getAttribute("user");
if(user != null)
{
	//直接跳转到主界面
	response.sendRedirect("main.jsp");
}
%>
<body>
<form action="DoLogin" method="post">
 <table>
  <caption>用户登录</caption>
  <tr>
   <td>用户名:</td><td><input type="text" name="username" id="username"></td>
  </tr>
  <tr>
   <td>密码:</td><td><input type="password" name="userpwd" id="userpwd"></td>
  </tr>
  <tr>
   <td><input type="submit" value="登陆"></td>
   <td><input type="reset" value="重置"></td>
  </tr>
 </table>
 如果还没注册请单击<a href="">这里</a>
</form>
</body>
</html>