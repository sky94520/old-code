<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>结果</title>
</head>
<%
request.setCharacterEncoding("utf-8");
int number = (Integer)session.getAttribute("number");
long start = session.getCreationTime();
long end = session.getLastAccessedTime();
%>
<body>
恭喜你，猜对了<br>
共猜了<%=request.getParameter("count")%>次<br>
花费时间:<%=(end - start)%>秒<br>
这个数字就是<%=number%>
</body>
</html>