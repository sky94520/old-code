<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<%@page import="java.sql.*" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>查询结果</title>
</head>
<script language="javascript">
function confirmDeleteData(obj)
{
	if(confirm('确定要删除'+obj.name))
	{
		return true;
		//document.location = 'bookDel.jsp?name='+obj.name;
	}
	else
		return false;
	
}
</script>
<body>
<%
//获得查询结果  这里是编号，编号为数字，没有汉字，以后扩展会有
String bookID = request.getParameter("bookID");
bookID = new String(bookID.getBytes("iso-8859-1"),"utf-8");
String searchMethod=request.getParameter("searchMethod");
String what = request.getParameter("what");
//连接数据库
//加载驱动
Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
String url = "jdbc:sqlserver://localhost:1433;DatabaseName=BookLibrary";
String name="sa";
String password="94520";
//获得Connection
Connection conn = DriverManager.getConnection(url,name,password);
StringBuilder sql=new StringBuilder("select * from book where ");
//按什么查找
if(what.equals("id"))
	sql.append("bookID");
else if(what.equals("name"))
	sql.append("bookName");
else if(what.equals("author"))
	sql.append("bookAuth");
else if(what.equals("publish"))
	sql.append("bookPub");
else
	throw new SQLException(what+"not found");
/*switch(what)
{
case "id":sql +="bookID";break;
case "name":sql +="bookName";break;
case "author":sql +="bookAuth";break;
case "publish":sql += "bookPub";break;
default: throw new SQLException(what+"not found!");
}*/
//精确查找
if(searchMethod.equals("1"))
	sql.append("= '"+bookID+"'");
else
	sql.append(" like '%"+bookID+"%'");
out.println(sql);
try{
	PreparedStatement query = conn.prepareStatement(sql.toString());
	//query.setString(1,bookID);
	ResultSet result = query.executeQuery();
	%>
	<table border="1">
	<tr><th>图书编号</th><th>书名</th><th>作者</th><th>出版日期</th><th>价格</th><th>简介</th><th>修改</th><th>删除</th></tr>
	<%
	while(result.next())
	{
		String id = result.getString("bookID");
		String bookName = result.getString("bookName");
		String bookAuth = result.getString("bookAuth");
		String bookPub = result.getString("bookPub");
		String bookPrice = result.getString("bookPrice");
		String bookInter = result.getString("bookInter");
		%>
		<tr>
		 <td><%=id %></td>
		 <td><%=bookName %></td>
		 <td><%=bookAuth %></td>
		 <td><%=bookPub %></td>
		 <td><%=bookPrice %></td>
		 <td><%=bookInter %></td>
		 <td><a href="bookUpdate.jsp?id=<%=id%>&bookName=<%=bookName%>&bookAuth=<%=bookAuth%>&bookPub=<%=bookPub%>&bookPrice=<%=bookPrice%>&bookInter=<%=bookInter%>">修改</a></td>
		 <td><a href="bookDel.jsp?id=<%=id %>" onclick="return confirmDeleteData(this)">删除</a></td>
		</tr>
		<%
	}
}catch(SQLException e)
{
	out.println("ss");
}
%>
</table>
<div align="center"><input type="button" value="返回图书查询界面" onclick="location.href='bookQuery.jsp'"></div>
</body>
</html>