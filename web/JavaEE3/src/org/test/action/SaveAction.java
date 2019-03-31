package org.test.action;

import java.sql.PreparedStatement;
import java.sql.SQLException;

import com.lah.toolBean.MySqlConn;
import com.opensymphony.xwork2.Action;
import com.opensymphony.xwork2.ActionSupport;
import com.person.Student;

public class SaveAction extends ActionSupport
{
	private Student student = null;
	
	public String execute()
	{
		String executeString = "";
		//ʹ��mysql���ݿ�
		MySqlConn conn = new MySqlConn();
		try 
		{
			PreparedStatement stat = conn.prepareStatement("insert into Student values(?,?,?,?,?,?)");
			stat.setString(1, student.getId());
			stat.setString(2, student.getName());
			stat.setString(3, student.getSex());
			stat.setString(4, student.getDate());
			stat.setString(5, student.getMajor());
			stat.setString(6, student.getDesc());
			//���뵽���ݿ�
			int bRet = stat.executeUpdate();
			stat.close();
			if(bRet > 0)
				executeString = Action.SUCCESS;
			else
				executeString = Action.ERROR;
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			//executeString = Action.ERROR;
			e.printStackTrace();
		}
		conn.closeDB();
		return executeString;
	}
	public Student getStudent() {
		return student;
	}
	public void setStudent(Student student) {
		this.student = student;
	}
}
