package com.ren;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;

import javax.servlet.ServletConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class UserRegisterServlet
 */
@WebServlet("/UserRegisterServlet")
public class UserRegisterServlet extends HttpServlet 
{
	private static final long serialVersionUID = 1L;
    private ServletConfig config = null;
    public void init(ServletConfig config)
    {
    	this.config = config;
    }
    public void doPost(HttpServletRequest request,HttpServletResponse response) throws IOException
    {
    	response.setContentType("text/html;charset=utf-8");
    	request.setCharacterEncoding("utf-8");
		PrintWriter out = response.getWriter();
    	//��ȡ����
    	String username = request.getParameter("username");
    	String password = request.getParameter("password1");
    	String mail = request.getParameter("mail");
    	String sql = "insert into subscriber values('"+username+"','"+password+"','"+mail+"')";
    	try 
    	{
    		//�������ݿ�
        	DataBaseBean db = new DataBaseBean();
			int success = db.executeUpdate(sql);
			//¼�����ݿ�ɹ�,��ת����½����
			if(success == 1)
			{
				response.sendRedirect("login.html");
			}
			else/*¼��ʧ��*/
			{
				
			}
			db.close();
		} catch (SQLException e) 
    	{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    }
}
