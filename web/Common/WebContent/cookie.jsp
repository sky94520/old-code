<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>cookie</title>
</head>
<body>
<%
	Cookie[] cookies = request.getCookies();

	Cookie cookie_response = null;
	if(cookies != null&&cookies.length>1)
			cookie_response = cookies[1];
	
	String time = new java.util.Date().toLocaleString();
	
	out.print("本次访问时间"+time);
	if(cookie_response != null)
	{
		out.print("上次访问时间"+cookie_response.getValue());
		cookie_response.setValue(time);
	}
	else
	{
		cookie_response = new Cookie("AccessTime","");
		cookie_response.setValue(time);
		cookie_response.setMaxAge(10);
		response.addCookie(cookie_response);
	}
%>
</body>
</html>