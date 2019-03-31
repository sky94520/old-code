<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="java.util.Date,java.text.*" %>
<%
	Date nowday=new Date();
	int hour=nowday.getHours();
	SimpleDateFormat format=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
	String time=format.format(nowday);
%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>jsp网站</title>
</head>
<body>
	<center>
	<table border="1" width="300">
		<tr height="30"><td align="center">温馨提示!</td></tr>
		<tr height="80"><td align="center">现在时间为：<%=time %></td></tr>
		<tr align="center">
		<td>
			<%
			if(hour>=24 && hour<5)
				out.print("现在是凌晨，时间还早呢，再睡会吧");
			else if(hour>=5 && hour<10)
				out.print("早上好！新的一天即将开始，你准备好了吗");
			else if(hour>=10 && hour<13)
				out.print("午休时间！正午好时光");
			else if(hour>=13&&hour<18)
				out.print("下午继续努力工作吧");
			else if(hour>=18&&hour<21)
				out.print("晚上好，自由时间");
			else if(hour>=21 && hour<24)
				out.print("早上休息吧");
			%>
		</td>
		</tr>
	</table>
	</center>
</body>
</html>