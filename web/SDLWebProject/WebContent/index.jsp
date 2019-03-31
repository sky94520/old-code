<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<%@ page import="com.ren.Subscriber" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>首页</title>
<link rel="stylesheet" type="text/css" href="css/basic.css"/>
<style type="text/css">
div.image
{
	display:inline;
	float:left;
}
</style>
</head>
<body>
<div class="image">
	<ul>
	<li><a href="#"><img src="image/logo.jpg"></a></li>
	</ul>
</div>
<div class="menu">
<ul>
	<li><a href="#">买房</a></li>
	<li><a href="#">租房</a></li>
	<li><a href="#">卖房</a></li>
	<li><a href="#">合租</a></li>
</ul>
</div>
<!-- 登陆或用户名 -->
<%
//获取session的用户信息

Subscriber subscriber = (Subscriber)session.getAttribute("subscriber");
if(subscriber == null)
{
	%>
	<div class="user">
	<ul>
		<li><a href="login.html">登陆</a></li>
		<li>|</li>
		<li><a href="register.html">注册</a></li>
	</ul>
	</div>
	<%
}
else//显示用户
{
	%>
	<div class="user">
	<ul>
		<li><a href="logout.jsp">退出</a></li>
		<li>&nbsp;</li>
		<li><a href="personalCenter5.jsp"><%=subscriber.getUsername() %></a></li>
	</ul>
	</div>
	<%
}
%>
</body>
</html>