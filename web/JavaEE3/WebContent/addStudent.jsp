<%@ page language="java" contentType="text/html; charset=gbk"
    pageEncoding="gbk"%>
<%@ taglib prefix="s"  uri="/struts-tags"%>
<%@ taglib prefix="sx" uri="/struts-dojo-tags" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gbk">
<title>���ѧ����Ϣ</title>
</head>
<body>
<s:form action="main" method="post">
	<table border="1">
		<caption>���ѧ����Ϣ</caption>
		<tr>
			<td><s:textfield label="ѧ��" name="student.id" size="20"/></td>
		</tr>
		<tr>
			<td><s:textfield label="����" name="student.name" size="20"/></td>
		</tr>
		<tr>
			<td><s:radio label="�Ա�" list="{'��','Ů'}" name="student.sex"></s:radio></td>
		</tr>
		<tr>
			<td><s:textfield label="��������" name="student.date"/></td>
		</tr>
		
		<tr>
			<td><s:textfield label="רҵ" name="student.major"/></td>
		</tr>
		<tr>
			<td><s:textarea label="��ע" name="student.desc"/></td>
		</tr>
		<tr>
			<td><s:submit value="���"/>
			<s:reset value="����"/></td>
		</tr>
	</table>
</s:form>
</body>
</html>