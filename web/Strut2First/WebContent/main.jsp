<%@ page language="java" contentType="text/html; charset=GBK"
    pageEncoding="GBK"%>
<%@ taglib prefix="s" uri="/struts-tags" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=GBK">
<title>���԰���Ϣ</title>
</head>
<body>
	<s:set name="user" value="#session['user']"/>
	<s:property value="#user.username"/>���ã���ӭ����½���԰�
</body>
</html>