<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<%@ page import="java.sql.*" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>Insert title here</title>
</head>
<body>
<jsp:useBean id="connDB" scope="page" class="com.lah.toolBean.Conn"/>
<%
String id = request.getParameter("id");
String sql_delete = "delete from book where bookID='"+id+"'";
int i = connDB.executeUpdate(sql_delete);
if(i==1)
{
	connDB.closeDB();
	%>
	<script language="javascript">
	alert("删除已完成");
	location.href = "bookQuery.jsp";
	</script>
	<%
}
%>
</body>
</html>