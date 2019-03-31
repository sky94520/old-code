<%@ page language="java" contentType="text/html; charset=GBK"
    pageEncoding="GBK"%>
<%@ page import="com.ren.Subscriber" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>ÊµÑé¶þ</title>
</head>
<%
//ÏÈ¼ì²âÓÃ»§ÊÇ·ñÒÑ¾­µÇÂ½
Subscriber user = (Subscriber)session.getAttribute("user");
if(user != null)
{
	//Ö±½ÓÌø×ªµ½Ö÷½çÃæ
	response.sendRedirect("main.jsp");
}
%>
<body>
<form action="DoLogin" method="post">
 <table>
  <caption>ÓÃ»§µÇÂ¼</caption>
  <tr>
   <td>ÓÃ»§Ãû:</td><td><input type="text" name="username" id="username"></td>
  </tr>
  <tr>
   <td>ÃÜÂë:</td><td><input type="password" name="userpwd" id="userpwd"></td>
  </tr>
  <tr>
   <td><input type="submit" value="µÇÂ½"></td>
   <td><input type="reset" value="ÖØÖÃ"></td>
  </tr>
 </table>
 Èç¹û»¹Ã»×¢²áÇëµ¥»÷<a href="">ÕâÀï</a>
</form>
</body>
</html>