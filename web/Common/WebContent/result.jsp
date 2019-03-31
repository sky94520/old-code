<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>三角形</title>
</head>
<%
	String first = request.getParameter("first");
	String two = request.getParameter("two");
	String three = request.getParameter("three");
%>
<body>
<%
if(first!=null && two != null && three != null)
{
	try
	{
		float a = Float.parseFloat(first);
		float b = Float.parseFloat(two);
		float c = Float.parseFloat(three);
		// the three line
		if(a + b>c && b + c > a && a+c>b)
		{
			float p = (a+b+c)/2;
			double area = Math.sqrt(p*(p-a)*(p-b)*(p-c));
			out.print("<br>三角形的面积"+area);
			
		}
		else
		{
			out.print("<br>三条边构不成三角形，请重新输入");
			out.print("<br><a href='inputTriangle.jsp'>返回</a>");
		}
	}catch(NumberFormatException e)
	{
		out.print("<br>输入有误，请重新输入<a href='inputTriangle.jsp'>返回</a>");
	}
}
%>
</body>
</html>