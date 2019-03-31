<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>Insert title here</title>
</head>
<%
String str = request.getParameter("radius");
float radius=0;
%>
<body>
<%

if(str != null)
{
	 try
	 {
		 radius = Float.parseFloat(str);
		 %>
		 圆的周长是：<%=2*3.1415926*radius %>
		圆的面积：<%=3.1415926*radius*radius %>
<%
	 }catch(NumberFormatException e)
	 {
		 out.print("<br>输入的不是数字");
		 out.print("<br>"+"<a href='inputRadius.jsp'>返回</a>");
	 }
}
%>
</body>
</html>