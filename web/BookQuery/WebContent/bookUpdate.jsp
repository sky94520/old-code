<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<%@ page import="com.personal.tool.MyTool" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>修改</title>
</head>
<script language="javascript">
function check(form)
{
	var price = form.bookPrice;
	if(price.value==""||isNaN(price.value))
	{
		alert("请输入数字");
		price.value="";
		price.focus();
		return false;
	}
	return true;
}
</script>
<body>
<%
String bookID = request.getParameter("id");
String bookName = MyTool.toChinese(request.getParameter("bookName"));
String bookAuth = MyTool.toChinese(request.getParameter("bookAuth"));
String bookPub = MyTool.toChinese(request.getParameter("bookPub"));
float bookPrice = Float.parseFloat(request.getParameter("bookPrice"));
String bookInter = MyTool.toChinese(request.getParameter("bookInter"));
%>
<form action="bookUpdateDo.jsp" method="get" onsubmit="return check(this);">
<table align="center" border="1">
<tr><td>图书编号：</td><td height="22"><input type="text" name="bookID" value="<%=bookID%>" readonly>(必填项)</td></tr>
<tr><td>书名：</td><td><input type="text" name="bookName" value="<%=bookName%>"></td></tr>
<tr><td>作者：</td><td><input type="text" name="bookAuth" value="<%=bookAuth%>"></td></tr>
<tr><td>出版社：</td><td><input type="text" name="bookPub" value="<%=bookPub%>"></td></tr>
<tr><td>单价：</td><td><input type="text" name="bookPrice" value="<%=bookPrice%>"></td></tr>
<tr><td>内容介绍：</td><td><textarea name="bookInter" rows="6" cols="25" value="<%=bookInter%>"></textarea></td></tr>
<tr ><td colspan="2" align="center">
	<input type="submit" value="提交">&nbsp;&nbsp;&nbsp;&nbsp;
	<input type="reset" value="重置"></td></tr>
</table>
</form>
</body>
</html>