package com.Servlet.ren;

import java.io.IOException;
import java.sql.ResultSet;
import java.sql.SQLException;

import com.personal.tool.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.lah.toolBean.*;
/**
 * Servlet implementation class DoLogin
 */
@WebServlet("/DoLogin")
public class DoLogin extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public DoLogin() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		response.getWriter().append("Served at: ").append(request.getContextPath());
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException 
	{
		// TODO Auto-generated method stub
		//获取用户的账号与密码
		String username = MyTool.toChinese(request.getParameter("username"));
		String userpwd = request.getParameter("userpwd");
		//System.out.println("username:"+username);
		//System.out.println("userpwd:"+userpwd);
		//使用数据库
		Conn conn = new Conn("RealEstateDB","sa","sa");
		String sql = "select * from subscriber where name='"+username+"' and password='"
				+userpwd+"'";
		ResultSet results = conn.executeQuery(sql);
		
		try
		{	//成功
			if(results.next())
			{
				//跳转到成功页面
				response.sendRedirect("main.jsp");
			}
			else
			{
				response.sendRedirect("login.jsp");
			}
			results.close();
		}catch(SQLException e)
		{
			System.out.println(e.getMessage());
		}
		conn.closeDB();
	}

}
