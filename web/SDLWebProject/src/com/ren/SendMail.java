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
		//�ʼ��˺� ����
		String mailFromName="a541052067@163.com";
		String mailFromPassword = "renjiwei";
		//smtp
		int n = mailFromName.indexOf('@');
		String mailServer = "smtp."+mailFromName.substring(n+1);
		//����Properties
		Properties prop = new Properties();
		prop.put("mail.smtp.host",mailServer);
		prop.put("mail.smtp.auth", "true");
		//���Session
		Session session = Session.getInstance(prop);
		session.setDebug(true);
		//��ȡ��֤��
		String verity = getVerity();
		//�½���Ϣ����
		MimeMessage message = new MimeMessage(session);
		//���÷�����
		InternetAddress fromMail;
		try {
			fromMail = new InternetAddress(mailFromName);
			message.setFrom(fromMail);
			//�����ռ���
			InternetAddress toMail = new InternetAddress(mail);
			message.setRecipient(Message.RecipientType.TO, toMail);
			//��������
			message.setSubject("SDL��������ע��");
			//message
			message.setText(verity);
			//���÷���ʱ��
			message.setSentDate(new Date());
			//�����ʼ�
			message.saveChanges();
			//��֤��ͷ��ͬ�Ự���ݱ���һ��
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
	//��ȡ��֤��
	public String getVerity()
	{
		Random random = new Random(System.currentTimeMillis());
		StringBuilder verity = new StringBuilder();
		//��ȡ4����֤��
		for(int i=0;i<4;i++)
			verity.append(Math.abs(random.nextInt()%10));
		return verity.toString();
	}
}
