<%@ page language="java" contentType="text/html; charset=GBK"
    pageEncoding="GBK"%>
<%@ page import="com.ren.Subscriber" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>ʵ���</title>
</head>
<%
//�ȼ���û��Ƿ��Ѿ���½
Subscriber user = (Subscriber)session.getAttribute("user");
if(user != null)
{
	//ֱ����ת��������
	response.sendRedirect("main.jsp");
}
%>
<body>
<form action="DoLogin" method="post">
 <table>
  <caption>�û���¼</caption>
  <tr>
   <td>�û���:</td><td><input type="text" name="username" id="username"></td>
  </tr>
  <tr>
   <td>����:</td><td><input type="password" name="userpwd" id="userpwd"></td>
  </tr>
  <tr>
   <td><input type="submit" value="��½"></td>
   <td><input type="reset" value="����"></td>
  </tr>
 </table>
 �����ûע���뵥��<a href="">����</a>
</form>
</body>
</html>