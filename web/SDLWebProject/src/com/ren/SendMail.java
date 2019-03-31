package com.ren;
import java.io.*;
import java.util.*;
import javax.mail.*;
import javax.mail.internet.*;
import javax.servlet.*;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/SendMail")
public class SendMail extends javax.servlet.http.HttpServlet 
{
	private static final long serialVersionUID = 1L;
	private ServletConfig config;
	final public void init(ServletConfig config) throws ServletException
	{
		this.config = config;
	}
	public void doGet(HttpServletRequest request,HttpServletResponse response) throws IOException
	{
		doPost(request,response);
	}
	public void doPost(HttpServletRequest request,HttpServletResponse response) throws IOException
	{	response.setContentType("text/html;charset=utf-8");
		request.setCharacterEncoding("utf-8");
		PrintWriter out = response.getWriter();

		String mail = request.getParameter("mail");
		//邮件账号 密码
		String mailFromName="a541052067@163.com";
		String mailFromPassword = "renjiwei";
		//smtp
		int n = mailFromName.indexOf('@');
		String mailServer = "smtp."+mailFromName.substring(n+1);
		//创建Properties
		Properties prop = new Properties();
		prop.put("mail.smtp.host",mailServer);
		prop.put("mail.smtp.auth", "true");
		//获得Session
		Session session = Session.getInstance(prop);
		session.setDebug(true);
		//获取验证码
		String verity = getVerity();
		//新建消息对象
		MimeMessage message = new MimeMessage(session);
		//设置发件人
		InternetAddress fromMail;
		try {
			fromMail = new InternetAddress(mailFromName);
			message.setFrom(fromMail);
			//设置收件人
			InternetAddress toMail = new InternetAddress(mail);
			message.setRecipient(Message.RecipientType.TO, toMail);
			//设置主题
			message.setSubject("SDL讨论社区注册");
			//message
			message.setText(verity);
			//设置发送时间
			message.setSentDate(new Date());
			//发送邮件
			message.saveChanges();
			//保证报头域同会话内容保持一致
			Transport transport = session.getTransport("smtp");
			transport.connect(mailServer,mailFromName,mailFromPassword);
			transport.sendMessage(message, message.getAllRecipients());
			transport.close();
			out.println(verity);
		} catch (AddressException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}catch (MessagingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	//获取验证码
	public String getVerity()
	{
		Random random = new Random(System.currentTimeMillis());
		StringBuilder verity = new StringBuilder();
		//获取4字验证码
		for(int i=0;i<4;i++)
			verity.append(Math.abs(random.nextInt()%10));
		return verity.toString();
	}
}
