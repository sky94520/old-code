<%@ page language="java" contentType="text/html; charset=GBK"
    pageEncoding="GBK"%>
<%@ page import="java.util.*,javax.mail.*,javax.mail.internet.*" %>
<%@ page import="javax.activation.*" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=GBK">
</head>
<%try{
	request.setCharacterEncoding("GBK");
	String from=request.getParameter("from");
	String to = request.getParameter("to");
	String subject = request.getParameter("subject");
	String content = request.getParameter("content");
	String password = request.getParameter("password");
	//生成smtp主机名称
	int n = from.indexOf('@');
	int m=from.length();
	String mailserver = "smtp."+from.substring(n+1,m);
	//建立邮件会话
	Properties pro = new Properties();
	pro.put("mail.smtp.host",mailserver);
	pro.put("mail.smtp.auth","true");
	
	Session sess = Session.getInstance(pro);
	//新建一个消息对象
	sess.setDebug(true);
	MimeMessage message = new MimeMessage(sess);
	//设置发件人
	InternetAddress from_mail = new InternetAddress(from);
	message.setFrom(from_mail);
	//设置收件人
	InternetAddress to_mail = new InternetAddress(to);
	message.setRecipient(Message.RecipientType.TO,to_mail);
	//设置主题
	message.setSubject(subject);
	message.setText(content);
	//设置发送时间
	message.setSentDate(new Date());
	//发送邮件
	message.saveChanges();
	Transport transport = sess.getTransport("smtp");
	transport.connect(mailserver,from,password);
	transport.sendMessage(message,message.getAllRecipients());
	transport.close();
	
	out.print("<script language='javascript'>alert('邮件已经发送');</script>");
}catch(Exception e)
{
	out.print("<script language='javascript'>alert('邮件发送失败');</script>");
}
%>
</html>