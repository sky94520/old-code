<%@ page language="java" contentType="text/html; charset=UTF-8"
	import="java.util.*"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="refresh" content="10;url=login.jsp">
<title>登陆失败</title>
</head>
<body>
<font size="6">对不起，</font>
<font size="7" color="red">
<%=(String)session.getAttribute("username") %><br/>
<font size="6">请您确认用户名和密码！</font><br/>
</font>
</body>
</html>