<%@ page language="java" contentType="text/html; charset=gbk"
    pageEncoding="gbk"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head> 
<title>�鱨վ</title>
</head>
<body>
<center>
<form action="upload.jsp" method="post" enctype="multipart/form-data">
<h1>��ӹ�����Ϣ</h1>
<table border="1">
	<tr><td>����</td><td><input type="text" name="title"></tr>
	<tr><td>����</td><td><textarea cols="30" rows="6" name="content"></textarea></td></tr>
	<tr><td>����</td><td><input type="file" name="file"><br>
	ע:�ϴ����ļ����ܳ���2M</td></tr>
	<tr><td colspan="2">
		<input type="submit" value="�ύ">&nbsp;
		<input type="reset" value="����">
	</td></tr>
</table>
</form>
</center>
</body>
</html>