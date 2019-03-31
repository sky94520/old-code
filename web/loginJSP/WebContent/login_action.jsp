<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="java.util.*"%>
<%
	request.setCharacterEncoding("UTF-8");
	String username=request.getParameter("username");
	String passwrd = request.getParameter("passwrd");
	String message = "";
	session.setAttribute("username",username);
	//save the things of buying
	session.setAttribute("list",null);
	if(username.equals("蜡笔小新")&&passwrd.equals("hello123"))
		response.sendRedirect("shopping.jsp");
	else
		response.sendRedirect("error.jsp");
%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>

</body>
</html>