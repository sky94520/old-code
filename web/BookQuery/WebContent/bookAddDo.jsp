<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<%@page import="java.sql.*,com.personal.tool.MyTool" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>s</title>
</head>
<jsp:useBean id="connDB" scope="page" class="com.lah.toolBean.Conn"></jsp:useBean>
<%
String bookID=request.getParameter("bookID");
String bookName=MyTool.toChinese(request.getParameter("bookName"));
String bookAuth=MyTool.toChinese(request.getParameter("bookAuth"));
String bookPub=MyTool.toChinese( request.getParameter("bookPub"));
float bookPrice=Float.parseFloat(request.getParameter("bookPrice"));
String bookIntro=MyTool.toChinese(request.getParameter("bookInter"));
%>
<body>
<%
//查询该bookID是否存在，存在则不放入数据库
ResultSet books=connDB.executeQuery("select * from book where bookID ='"+bookID+"'");
if(books.next())
{
	%>
	<script language="javascript">
	alert("该图书编号已经存在");
	history.back();
	</script>
	<%
}
else
{
	
	String insert="insert into book values('"+bookID+"','"+bookName+"','"+bookAuth+"','"+bookPub+"',"+bookPrice+",'"+bookIntro+"');";
	int t=connDB.executeUpdate(insert);
	if(t==0)
	{
		%>
		<script language="javascript">
		alert("增加失败");
		history.back();
		</script>
		<%
	}else
	{
		//断开数据库
		connDB.closeDB();
		response.sendRedirect("beanShowAll.jsp");
	}
}
%>
</body>
</html>