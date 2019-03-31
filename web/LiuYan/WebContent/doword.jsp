<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<%@ page import="com.lah.valueBean.*" %>
<%@ page import="com.lah.valueBean.MyTool" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>显示留言信息</title>
</head>
<jsp:useBean id="myWord" class="com.lah.valueBean.WordSingle" scope="request"/>
<jsp:setProperty name="myWord" property="*"/>

<body>
<center><b>查看留言信息</b></center><hr>
<table border="0" align="center">
	<tr>
		<td>留言者:</td>
		<td><%=MyTool.toChinese(myWord.getAuthor()) %></td>
	</tr>
	<tr>
		<td>留言主题:</td>
		<td><%=MyTool.toChinese(myWord.getTitle()) %></td>
	</tr>
	<tr>
		<td>留言内容:</td>
		<td><textarea name="content" rows="6" cols="30" readonly>
		<%=MyTool.toChinese(myWord.getContent()) %></textarea></td>
	</tr>
	<tr>
		<td><a href="word.jsp">返回留言界面</a></td>
	</tr>
</table>
</body>
</html>