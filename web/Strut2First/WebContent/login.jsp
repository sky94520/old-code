<%@ page language="java" contentType="text/html; charset=GBK"
    pageEncoding="GBK"%>
<%@ taglib prefix="s" uri="/struts-tags" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=GBK">
<title>��½</title>
</head>
<body bgcolor="#e3e3e3">
<s:form action="main" method="post">
 <table>
  <caption>�û���¼</caption>
  
  <tr>
   <td>�û���:</td>
    <td><s:textfield name="user.username" size="20"/></td>
  </tr>
  <tr>
   <td>��&nbsp;&nbsp;��</td>
   <td><s:password name="user.password" size="21"/></td>
  </tr>
  
  <tr>
   <td>
    <s:submit value="��½"/>	
   </td>
  </tr>
 </table>
</s:form>
���ûע�ᵥ��<a href="">����</a>ע��!
</body>
</html>