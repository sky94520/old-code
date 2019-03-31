<%@ page language="java" contentType="text/html; charset=gbk"
    pageEncoding="gbk"%>
<%@ taglib prefix="s"  uri="/struts-tags"%>
<%@ taglib prefix="sx" uri="/struts-dojo-tags" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gbk">
<title>添加学生信息</title>
</head>
<body>
<s:form action="main" method="post">
	<table border="1">
		<caption>添加学生信息</caption>
		<tr>
			<td><s:textfield label="学号" name="student.id" size="20"/></td>
		</tr>
		<tr>
			<td><s:textfield label="姓名" name="student.name" size="20"/></td>
		</tr>
		<tr>
			<td><s:radio label="性别" list="{'男','女'}" name="student.sex"></s:radio></td>
		</tr>
		<tr>
			<td><s:textfield label="出生日期" name="student.date"/></td>
		</tr>
		
		<tr>
			<td><s:textfield label="专业" name="student.major"/></td>
		</tr>
		<tr>
			<td><s:textarea label="备注" name="student.desc"/></td>
		</tr>
		<tr>
			<td><s:submit value="添加"/>
			<s:reset value="重置"/></td>
		</tr>
	</table>
</s:form>
</body>
</html>