<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<script type="text/javascript" language="javascript">
function submitNumber(n)
{
	var countVar = document.getElementById("count1");

	countVar.value = parseInt(countVar.value)+1;
	
	var small="所猜的数字太小";
	var big = "所猜的数字大了";
	var input = document.getElementById("input");
	var div = document.getElementById("para");
	
	var num = parseInt(input.value);
	
	if(isNaN(num))
		return false;
	if(num > n)
		div.innerHTML = big;
	else if(num < n)
		div.innerHTML = small;
	else if(num == n)
	{
		countVar.disabled="";
		return true;
	}
	input.focus();
	input.value="";
	return false;
}
</script>
<title>猜数字</title>
</head>
<%
	int number = (int)(Math.random()*10);
	session.setAttribute("number",number);
%>
<body>
<div id="para">系统随机分给你1-10之间的数，请猜<br>输入您的所猜的数</div>
<!-- input改为disabled为禁止，即无法被request传送 -->
<form action="result.jsp" method="post" >
	猜了<input type="text" id="count1" name="count" value="0" readonly disabled>次<br>
	<input type="text" id="input"><br>
	<input type="submit" value="提交" onclick="return submitNumber(<%=number%>);">
</form>
</body>
</html>