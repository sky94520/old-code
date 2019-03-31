<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"
    import="java.util.*,loginJSP.Thing"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>购物</title>
</head>
<%
String username=(String)session.getAttribute("username");
String[] str ={"java程序设计","本草纲目","c语言程序设计","活着"};
float[] values={25.6f,34.5f,20,15};
List<Thing> goods=new ArrayList<Thing>();
for(int i=0;i<str.length;i++)
	goods.add(new Thing(str[i],values[i]));
//put the goods of information session
session.setAttribute("goods",goods);
%>
<body>
<div><%=username%>,欢迎您</div><br>
<form action="shopping_do.jsp" method="post">
	<%for(int i=0;i<goods.size();i++){%>
		<input type="checkbox" name="goodsName" value=<%=goods.get(i).getName() %>><%=goods.get(i).getName() %>&nbsp;￥<%=goods.get(i).getPrice() %><br>
	<%} %>
	<input type="submit" name="buy" value="购买">
	<input type="reset" name="reset" value="清空购物车"> 
</form>
</body>
</html>