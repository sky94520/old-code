<%@ page language="java" contentType="text/html; charset=gbk"
    pageEncoding="gbk"%>
<%@ page import="java.sql.*,java.io.*" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gbk">
<title>Insert title here</title>
</head>
<jsp:useBean id="upFile" class="com.jspsmart.upload.SmartUpload"/>
<body>
<%try{
	response.reset();
	out.clear();
	out = pageContext.pushBody();
	upFile.initialize(pageContext);
	
	upFile.setContentDisposition(null);
	
	String fileName = request.getParameter("filename");
	//判断是否有这个文件
/*	if(fileName.equals(""))
		out.print("<script>alert('文件为空');window.history.back(-1);</script>");*/

	fileName = new String(fileName.getBytes("iso-8859-1"),"gb2312");
	//设置下载路径
	String download = "/upload/"+fileName;
	upFile.downloadFile(download);
}catch(FileNotFoundException e)
{
	//2s后重定向到result.jsp
	out.print("the file not existed文件");
	response.setHeader("refresh","1;URL=result.jsp");
}catch(Exception e)
{
	//2s后重定向到result.jsp
	response.setHeader("refresh","1;URL=result.jsp");
}
%>
</body>
</html>