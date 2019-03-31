<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<%@ page import="java.util.*" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>注册成功</title>
</head>
<%
request.setCharacterEncoding("utf-8");
String username = request.getParameter("username");
String passwrd = request.getParameter("userpwd2");
String sex = request.getParameter("sex");


String birthday = request.getParameter("birthday");
String mail = request.getParameter("mail");
String work = request.getParameter("work");
String[] strLoves = (String[])request.getParameterValues("like");
String introduction = request.getParameter("introduction");
%>
<body>
账号:<%=username%><br>
密码:<%=passwrd%><br>
性别:<%=sex%><br>
生日<%=birthday %><br>
邮箱:<%=mail %><br>
职业:<%=work %><br>
个人爱好:<%
	for(int i=0;strLoves!=null&&i<strLoves.length;i++)
		if(!strLoves[i].trim().equals(""))
			out.print(strLoves[i]);
%><br>
个人说明:<%=introduction %><br>
</body>
</html>