<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"
    import="java.util.*,loginJSP.Thing"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>收银台</title>
</head>
<%
ArrayList<String> list = (ArrayList<String>)session.getAttribute("list");
ArrayList<Thing> goods = (ArrayList<Thing>)session.getAttribute("goods");
float prices = 0.f;
%>
<body>
<div>非常感谢您的光临，您本次在我们这购买了以下商品：</div>
<%
for(String str : list)
{
	for(int j=0;j<goods.size();j++)
		if(str.equals(goods.get(j).getName()))
		{
			out.print("商品："+str+"<br>价格："+goods.get(j).getPrice()+"<br>");
			prices += goods.get(j).getPrice();
		}
}
%>

您这次共消费了<%=prices %>元
</body>
</html>