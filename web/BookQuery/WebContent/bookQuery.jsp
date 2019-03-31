<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>查询</title>
</head>
<body>
<h1 align="center">图书查询</h1>
<hr>
<form action="bookQueryDo.jsp" method="get">
<div align="center">图书编号：<input type="text" name="bookID">
<select name="searchMethod">
<option value="1" selected>精确查找</option>
<option value="2">模糊查找</option>
</select>
按<select name="what">
<option value="id" selected>ID</option>
<option value="name" >书名</option>
<option value="author">作者</option>
<option value="publish">出版社</option>
</select>查找
</div>
<br>
<div align="center"><input type="submit" value="提交">&nbsp;
	<input type="reset" value="重置"></div>
</form>
</body>
</html>