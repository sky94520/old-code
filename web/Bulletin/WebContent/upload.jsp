<%@ page language="java" contentType="text/html; charset=gbk"
    pageEncoding="gbk"%>
<%@ page import="java.sql.*,java.io.*" %>
<%@ page import="com.personal.tool.MyTool" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<jsp:useBean id="upFile" class="com.jspsmart.upload.SmartUpload" scope="page"/>
<html>
<head>
<title>С���鱨վ</title>
</head>
<body>
<%
//request.setCharacterEncoding("utf-8");
//��ȡӦ�ó�����upload�ļ��еĵ�ǰ�ļ��е�����·���������ļ��ж���
String subPath=this.getServletContext().getRealPath("/")+"upload";
File createSub = new File(subPath);
if(!createSub.exists())
	createSub.mkdir();
//��ʼ��������pageContext���ñ��� 
upFile.initialize(pageContext);
//upFile.setAllowedFilesList("txt,doc,xls,rar,mp3");
//���ò�������ļ�
upFile.setDeniedFilesList("exe,bat,jsp");
//�����ļ����Ϊ5w b
upFile.setMaxFileSize(2000000);
//�ϴ��ļ�
upFile.upload();
//��ȡ�ļ���С
long size = upFile.getFiles().getSize();
if(size > 2000000)
	out.println("<script>alert('���ϴ����ļ�̫���޷�����ϴ�')</script>");
else
{
	String fileName = upFile.getFiles().getFile(0).getFileName();
	//��Դ�ļ����洢��web����������·���µ�upload��
	upFile.save("/upload");
	try{
		String username="sa";
		String password = "94520";
		String url="jdbc:sqlserver://localhost:1433;DatabaseName=Bulletin";
		Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
		Connection connection = DriverManager.getConnection(url,username,password);
		//����Statement
		String sql="insert into message values(?,?,?)";
		PreparedStatement pstmt = connection.prepareStatement(sql);
		
		pstmt.setString(1,upFile.getRequest().getParameter("title"));
		pstmt.setString(2,upFile.getRequest().getParameter("content"));
		pstmt.setString(3,fileName);
		//ִ��
		pstmt.execute();
		pstmt.close();
		out.println((upFile.getRequest().getParameter("title"))+"ִ�гɹ�");
		out.print("����������"+subPath);
		//2s���ض���result.jsp
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