<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<%@ page import="java.sql.*" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>所有图书</title>
</head>
<jsp:useBean id="connDB" scope="page" class="com.lah.toolBean.Conn"/>
<%
//每一页存放的行数
final int numPerPage=6;
//总个数
int allNum=0;
//页面数
int totalPage=0;
ResultSet result=connDB.executeQuery("select * from book");
//获取总行数
if(result.next())
{
	result.last();
	allNum = result.getRow();
	result.first();
}
//判断总共的页数
if(allNum%numPerPage==0)
	totalPage = allNum/numPerPage;
else
	totalPage = allNum/numPerPage + 1;
int currentPage = 0;
try{
	currentPage = Integer.parseInt(request.getParameter("currentPage"));
	if(currentPage>totalPage)
		currentPage = totalPage;
}catch(NumberFormatException e)
{
	currentPage=1;
}
//定位页面
result.absolute((currentPage-1)*numPerPage);
%>
<body>
<table width="600" border="1">
<caption >所有图书列表</caption>
<tr>
<th bgcolor="#a9d0f5" scope="col">图书编号</th>
<th bgcolor="#A9D0F5" scope="col">书名</th>
<th bgcolor="#A9D0F5" scope="col">作者</th>
<th bgcolor="#A9D0F5" scope="col">出版社</th>
</tr>
<%
for(int iPage=0;iPage<numPerPage&&result.next();iPage++)
{
	%>
	<tr>
	<td height="22" align="center"><%=result.getString("bookID") %></td>
	<td height="22" align="center"><%=result.getString("bookName") %></td>
	<td height="22" align="center"><%=result.getString("bookAuth") %></td>
	<td height="22" align="center"><%=result.getString("bookPub") %></td>
	</tr>
	<%
}
%>
</table><br>
<center><button onclick="location.href='bookAdd.jsp'">返回新增图书界面</button></center>
<%
//添加链接
//添加上一页 第一页链接
if(currentPage!=1)
{
	out.print("<a href='beanShowAll.jsp?currentPage=1'>第一页</a>");
	out.print("&nbsp;&nbsp;");
	out.print("<a href='beanShowAll.jsp?currentPage='"+(currentPage-1)+">上一页</a>");
}
else
{
	out.print("第一页");
	out.print("&nbsp;&nbsp;");
	out.print("上一页");
}
out.print("&nbsp;&nbsp;");
//添加下一页 最后一页
if(currentPage != totalPage)
{
	out.print("<a href='beanShowAll.jsp?currentPage="+(currentPage+1)+"'>下一页</a>");
	out.print("&nbsp;&nbsp;");
	out.print("<a href='beanShowAll.jsp?currentPage="+totalPage+"'>最后一页</a>");
}
else
{
	out.print("下一页");
	out.print("&nbsp;&nbsp;");
	out.print("最后一页");
}
out.print("<br>");
//实现go
%>
<form action="" method="get">
输入页面:<input type="text" name="currentPage" size="1">
<input type="submit" value="go">当前页面
<%=currentPage%>/<%=totalPage %>
&nbsp;共<%=allNum %>个结果
</form>
</body>
</html>