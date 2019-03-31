package com.ren.filter;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.annotation.WebFilter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

/**
 * Servlet Filter implementation class LoginFilter
 */
public class LoginFilter implements Filter 
{
	private FilterConfig filterConfig = null;
	private String redirectURL = null;
	private String sessionKey = null;
	private ArrayList<String> checkURLList;
    /**
     * Default constructor. 
     */
    public LoginFilter() {
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see Filter#destroy()
	 */
	public void destroy() {
		// TODO Auto-generated method stub
		checkURLList.clear();
	}

	/**
	 * @see Filter#doFilter(ServletRequest, ServletResponse, FilterChain)
	 */
	public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
		// TODO Auto-generated method stub
		HttpServletRequest request1 = (HttpServletRequest)request;
		HttpServletResponse response1 = (HttpServletResponse)response;
		//获取session
		HttpSession session = request1.getSession();
		//PrintWriter out = response.getWriter();
		//过滤链
		if(sessionKey == null)
		{
			chain.doFilter(request, response);
			return;
		}
		//out.print("<script language='javascript'>alert('filter');</script>");
		//需要过滤，并且在session中没有该sessionKey
		if(isNeedFilter(request1)&&session.getAttribute(sessionKey)==null)
		{
			response1.sendRedirect(redirectURL);
			return;
		}
		chain.doFilter(request,response);
	}
	public boolean isNeedFilter(HttpServletRequest request)
	{
		String url = request.getServletPath()
				+(request.getPathInfo()==null?"":request.getPathInfo());
		
		return this.checkURLList.contains(url);
	}
	/**
	 * @see Filter#init(FilterConfig)
	 */
	public void init(FilterConfig fConfig) throws ServletException 
	{
		// TODO Auto-generated method stub
		filterConfig = fConfig;
		//转向的url
		redirectURL = filterConfig.getInitParameter("redirectURL");
		sessionKey = filterConfig.getInitParameter("sessionKey");
		//检测的url
		checkURLList = new ArrayList<String>();
		String checkURLs = filterConfig.getInitParameter("checkURLs");
		String[] strs = checkURLs.split(";");
		for(String str:strs)
			checkURLList.add("/"+str);
	}

}

