package org.test.action;

import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import com.ren.*;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Map;

import com.lah.toolBean.*;

public class MainAction extends ActionSupport
{
	private UserTable user;
	public void validate()
	{
		if(user.getUsername() == null || user.getUsername().trim().equals(""))
			addFieldError("user.username","用户名必须填");
	}
	public String execute()
	{
		String username = user.getUsername();
		String password = user.getPassword();
		//验证成功标志
		boolean validated = false;
		//使用mysql 数据库
		MySqlConn conn = new MySqlConn();
		
		ActionContext context = ActionContext.getContext();
		Map<String, Object> session = context.getSession();
		UserTable user1 = null;
		//判断用户是否是第一次进入
		user1 = (UserTable)session.get("user");
		if(user1 == null)
		{
			//在数据库中查询 在Admin
			String sql = "select *from Admin where name='"+username+"' and password='"
					+password+"'";
			ResultSet result = conn.executeQuery(sql);
			//取得结果集
			try
			{
				if(result.next())
					 validated = true;
				result.close();
			}catch(SQLException e)
			{
				e.printStackTrace();
			}
			conn.closeDB();
		}
		else//用户在之前已经登陆
		{
			validated = true;
		}
		if(validated == true)
			return "success";
		else
			return "error";
	}
	public String ret()
	{
		return "success";
	}
	public UserTable getUser()
	{
		return user;
	}
	public void setUser(UserTable user)
	{
		this.user = user;
	}
}
