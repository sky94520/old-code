<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<%@ page import="java.sql.*,com.personal.tool.MyTool" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>update do</title>
</head>
<body>
<%
String bookID = request.getParameter("bookID");
String bookName = MyTool.toChinese(request.getParameter("bookName"));
String bookAuth = MyTool.toChinese(request.getParameter("bookAuth"));
String bookPub = MyTool.toChinese(request.getParameter("bookPub"));
String bookPrice = request.getParameter("bookPrice");
String bookInter = MyTool.toChinese(request.getParameter("bookInter"));
%>
<jsp:useBean id="connDB" scope="page" class="com.lah.toolBean.Conn"/>
<%
String sqlUpdate = "update book set bookName='"
	+bookName+"',bookAuth='"+bookAuth+"',bookPub='"+bookPub+
	"',bookPrice="+bookPrice+",bookInter='"+bookInter+"' where bookID='"+bookID+"'";
int n = connDB.executeUpdate(sqlUpdate);
connDB.closeDB();
if(n==1)
{
	%>
	<script language="javascript">
	alert("修改成功");
	location.href="beanShowAll.jsp";
	</script>
	<%
}
else
{
	%>
	<script language="javascript">
	alert("修改失败");
	history.back(-1);
	</script>
	<%
}
%>
<%=sqlUpdate %>
</body>
</html>