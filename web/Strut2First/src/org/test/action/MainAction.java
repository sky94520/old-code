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
			addFieldError("user.username","�û���������");
	}
	public String execute()
	{
		String username = user.getUsername();
		String password = user.getPassword();
		//��֤�ɹ���־
		boolean validated = false;
		//ʹ��mysql ���ݿ�
		MySqlConn conn = new MySqlConn();
		
		ActionContext context = ActionContext.getContext();
		Map<String, Object> session = context.getSession();
		UserTable user1 = null;
		//�ж��û��Ƿ��ǵ�һ�ν���
		user1 = (UserTable)session.get("user");
		if(user1 == null)
		{
			//�����ݿ��в�ѯ ��Admin
			String sql = "select *from Admin where name='"+username+"' and password='"
					+password+"'";
			ResultSet result = conn.executeQuery(sql);
			//ȡ�ý����
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
		else//�û���֮ǰ�Ѿ���½
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
