<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>登陆</title>
<link rel="stylesheet" type="text/css" href="css/common.css"/>
<script type="text/javascript" src="js/common.js"></script>
</head>
<body>
<form id="loginForm" action="login_action.jsp" method="post" onsubmit="return checkForm(this);">
	<fieldset>
		<legend>login</legend>
		<label for="username">用户名:</label>
		<input type="text" id="username" name="username">
		<span id="userNameErr" class="errorMsg"></span>
		<br/><br/>
		<label for="passwrd">密&nbsp;&nbsp;&nbsp;&nbsp;码:</label>
		<input type="password" id="passwrd" name="passwrd">
		<span id="passwrdErr" class="errorMsg"></span>
		<br/>
		</fieldset>
		<!-- button -->
		<input type="submit" value="提交">
		<input type="reset" value="重置">
</form>
</body>
</html>