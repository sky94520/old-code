<%@ page language="java" contentType="text/html; charset=gbk"
    pageEncoding="gbk"%>
<%@ page import="java.sql.*,java.io.*" %>
<%@ page import="com.personal.tool.MyTool" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<jsp:useBean id="upFile" class="com.jspsmart.upload.SmartUpload" scope="page"/>
<html>
<head>
<title>小新情报站</title>
</head>
<body>
<%
//request.setCharacterEncoding("utf-8");
//获取应用程序下upload文件夹的当前文件夹的物理路径，创建文件夹对象
String subPath=this.getServletContext().getRealPath("/")+"upload";
File createSub = new File(subPath);
if(!createSub.exists())
	createSub.mkdir();
//初始化，传入pageContext内置变量 
upFile.initialize(pageContext);
//upFile.setAllowedFilesList("txt,doc,xls,rar,mp3");
//设置不允许的文件
upFile.setDeniedFilesList("exe,bat,jsp");
//设置文件最大为5w b
upFile.setMaxFileSize(2000000);
//上传文件
upFile.upload();
//获取文件大小
long size = upFile.getFiles().getSize();
if(size > 2000000)
	out.println("<script>alert('您上传的文件太大，无法完成上传')</script>");
else
{
	String fileName = upFile.getFiles().getFile(0).getFileName();
	//以源文件名存储在web服务器虚拟路径下的upload下
	upFile.save("/upload");
	try{
		String username="sa";
		String password = "94520";
		String url="jdbc:sqlserver://localhost:1433;DatabaseName=Bulletin";
		Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
		Connection connection = DriverManager.getConnection(url,username,password);
		//创建Statement
		String sql="insert into message values(?,?,?)";
		PreparedStatement pstmt = connection.prepareStatement(sql);
		
		pstmt.setString(1,upFile.getRequest().getParameter("title"));
		pstmt.setString(2,upFile.getRequest().getParameter("content"));
		pstmt.setString(3,fileName);
		//执行
		pstmt.execute();
		pstmt.close();
		out.println((upFile.getRequest().getParameter("title"))+"执行成功");
		out.print("附件保存在"+subPath);
		//2s后重定向到result.jsp
		response.setHeader("refresh","2;URL=result.jsp");
	}catch(ClassNotFoundException e)
	{
		e.printStackTrace();
	}
	catch(SQLException e)
	{
		e.printStackTrace();
	}
}
%>
</body>
</html>