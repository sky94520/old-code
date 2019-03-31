<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>request</title>
</head>
<body>
<%
java.util.Locale locale = request.getLocale();
if(locale.equals(java.util.Locale.US))
	out.print("welcome to beijing!");
else if(locale.equals(java.util.Locale.CHINA))
		out.print("北京欢迎您");
else
	out.print("所在区域"+locale.toString());
%>
</body>
</html>