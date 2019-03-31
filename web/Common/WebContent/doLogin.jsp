<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<%@ page isELIgnored="false" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>账号-密码</title>
</head>
<body>
<jsp:useBean id="person" class="com.Bean.Person" scope="page">
<jsp:setProperty name="person" property="username" param="username"/>
</jsp:useBean>
<jsp:getProperty name="person" property="username"/>

</body>
</html>