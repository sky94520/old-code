<%@ page language="java" contentType="text/html; charset=gbk"
    pageEncoding="gbk"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head> 
<title>情报站</title>
</head>
<body>
<center>
<form action="upload.jsp" method="post" enctype="multipart/form-data">
<h1>添加公告信息</h1>
<table border="1">
	<tr><td>标题</td><td><input type="text" name="title"></tr>
	<tr><td>内容</td><td><textarea cols="30" rows="6" name="content"></textarea></td></tr>
	<tr><td>附件</td><td><input type="file" name="file"><br>
	注:上传的文件不能超过2M</td></tr>
	<tr><td colspan="2">
		<input type="submit" value="提交">&nbsp;
		<input type="reset" value="重置">
	</td></tr>
</table>
</form>
</center>
</body>
</html>