package com.ren;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class DataBaseServlet
 */
@WebServlet("/DataBaseServlet")
public class DataBaseServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
    private ServletConfig config = null;
    public void init(ServletConfig config) throws ServletException
    {
    	this.config = config;
    }
    public void doGet(HttpServletRequest request,HttpServletResponse response) throws IOException
    {
    	doPost(request,response);
    }
    public void doPost(HttpServletRequest request,HttpServletResponse response) throws IOException
    {
    	response.setContentType("text/html;charset=utf-8");
		request.setCharacterEncoding("utf-8");
		PrintWriter out = response.getWriter();
    	//获取邮箱
    	String mail = request.getParameter("mail");
    	//创建数据库
    	DataBaseBean db = new DataBaseBean();
    	try 
    	{
			ResultSet result = db.executeQuery("select * from subscriber where mail='"+mail+"'");
			//不存在此邮箱
			if(result.next() == false)
				out.print("0");
			else
				out.print("1");
			//关闭连接
			result.close();
			db.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    }
}
