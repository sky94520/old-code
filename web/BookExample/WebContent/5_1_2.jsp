<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>5-1-2</title>
</head>
<body>
<form action="" method="get">
<p>值1：<input type="text" name="name">
<p>值2：<input type="text" name="passwrd">
<p><input type="submit"value="submit">
</form>
<jsp:useBean id="user" scope="request" class="com.game.UserInfo"/>
<jsp:setProperty name="user" property="name" param="name"/>
<jsp:setProperty name="user" property="passwrd" param="passwrd"/>
<hr>
<jsp:getProperty name="user" property="name"/>
<jsp:getProperty name="user" property="passwrd"/>
</body>
</html>