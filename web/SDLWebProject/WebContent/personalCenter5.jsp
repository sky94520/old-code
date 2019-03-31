<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>账号设置</title>
</head>
<link rel="stylesheet" type="text/css" href="css/personalcenter.css"/>
<body>
<!-- 首页 -->
<div class="image">
	<ul>
	<li><a href="index.jsp"><img src="image/logo.jpg"></a></li>
	</ul>
</div>
<!-- 个人中心 left-->
<div class="buttongroup">
	<ul>
	<li><a href="#">卖房委托</a></li>
	<li><a href="#">买房委托</a></li>
	<li><a href="#">出租委托</a></li>
	<li><a href="#">租房委托</a></li>
	<li><a href="#">账户设置</a></li>
	</ul>
</div>
<!-- 委托添加 -->
<div class="include">
	<form action="#" method="post">
		<table>
			<tr>
				<td><label for="oldpassword">旧密码:</label></td>
				<td><input type="password" name="oldpassword" id="oldpassword"></td>
			</tr>
			<tr>
				<td><label for="newpassword1">新密码:</label></td>
				<td><input type="password" name="newpassword1" id="newpassword1"></td>
			</tr>
			<tr>
				<td><label for="newpassword2">确认密码:</label></td>
				<td><input type="password" name="newpassword2" id="newpassword2"></td>
			</tr>
		</table>
		<input type="submit" value="确定">
		<input type="reset" value="重置">
	</form>
</div>
<%= request.getServletPath()%>
<%= request.getPathInfo() %>
<%
String checkURLs = "doLogin.jsp;personalCenter5.jsp";
String[] strs = checkURLs.split(";");
for(int i=0;i<strs.length;i++)
	out.print("  "+strs[i]);
%>
</body>
</html>