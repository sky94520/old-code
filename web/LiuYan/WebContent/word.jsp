<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>留言板</title>
</head>
<body>
<center><h2><i>欢迎使用留言板</i></h2></center><hr>
<form action="doword.jsp" method="post">
<table border="0" align="center">
	<tr>
		<td>留言者:</td>
		<td><input type="text" name="author"></td>
	</tr>
	<tr>
		<td>留言主题:</td>
		<td><input type="text" name="title"></td>
	</tr>
	<tr>
		<td>留言内容:</td>
		<td><textarea name="content" rows="6" cols="30"></textarea></td>
	</tr>
	<tr align="center">
		<td colspan="2">
		<input type="submit" value="提交">
		<input type="reset" value="重置">
		</td>
	</tr>
</table>
</form>
</body>
</html>