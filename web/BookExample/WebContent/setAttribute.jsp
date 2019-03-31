<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>Error</title>
</head>
<body>
<%request.setAttribute("error","很抱歉，您输入的用户名或密码不正确"); %>
happy
<%@ include file="error.jsp"%>
</body>
</html>