<%@ page language="java" contentType="text/html; charset=GBK"
    pageEncoding="GBK"%>
<%@ taglib prefix="s" uri="/struts-tags" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=GBK">
<title>登陆</title>
</head>
<body bgcolor="#e3e3e3">
<s:form action="main" method="post">
 <table>
  <caption>用户登录</caption>
  
  <tr>
   <td>用户名:</td>
    <td><s:textfield name="user.username" size="20"/></td>
  </tr>
  <tr>
   <td>密&nbsp;&nbsp;码</td>
   <td><s:password name="user.password" size="21"/></td>
  </tr>
  
  <tr>
   <td>
    <s:submit value="登陆"/>	
   </td>
  </tr>
 </table>
</s:form>
如果没注册单击<a href="">这里</a>注册!
</body>
</html>