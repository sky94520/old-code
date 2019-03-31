<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"
    import="java.util.*"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>购物车</title>
</head>
<body>
<%
request.setCharacterEncoding("utf-8");
String[] buyThings = request.getParameterValues("goodsName");
List<String> list = (ArrayList<String>)session.getAttribute("list");
if(list == null)
	list = new ArrayList<String>();
//add the buying thing to session
if(buyThings != null)
{
	for(int i=0;i<buyThings.length;i++)
	list.add(buyThings[i]);
}
if(buyThings != null)
{
	out.print("你购买了:<br>");
	for(String str:buyThings)
		out.print(str+"<br>");
	session.setAttribute("list", list);
}
%>
<center>
<strong>请问您还想做什么？</strong><br>
<button onclick="location.href='shopping.jsp'">继续购买物品&nbsp;&nbsp;</button>
<button onclick="location.href='pay.jsp'">到收银台结账</button>
</center>
</body>
</html>