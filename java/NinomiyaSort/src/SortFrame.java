import java.awt.GridLayout;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.DataInputStream;
import java.io.EOFException;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;


public class SortFrame extends JFrame
{
	protected JButton[] m_label;
	protected Integer[] m_integer;
	//结果
	protected Integer[] m_result;
	//标记 空格所在的位置
	protected int m_mark;
	//
	protected static int[] d={-3,3,-1,1};
	
	public SortFrame(String str)
	{
		super(str);
		initlize();
	}
	protected void initlize()
	{
		this.m_label=new JButton[9];
		m_integer=new Integer[9];
		m_result=new Integer[9];
		//读取文件
		File file=new File("init.txt");
		try 
		{
			DataInputStream input=new DataInputStream(new FileInputStream(file));
			int ch;
			for(int i=0;i<9;i++)
			{
				
				ch=input.readByte();
				m_integer[i]=ch-'1'+1;
				//记住0的位置
				if(m_integer[i]==0)
					m_mark=i;
				this.m_label[i]=new JButton(""+(m_integer[i]==0?"":m_integer[i]));
				this.m_label[i].setEnabled(false);
				this.add(this.m_label[i]);
				//System.out.println(m_integer[i]);
			}
			input.skipBytes(2);
			for(int i=0;i<9;i++)
			{
				
				ch=input.readByte();
				m_result[i]=ch-'1'+1;
			}
			input.close();
			
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}catch(EOFException e){
			e.printStackTrace();
		}
		catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	protected boolean isWin()
	{
		for(int i=0;i<9;i++)
			if(!m_integer[i].equals(m_result[i]))
				return false;
		return true;
	}
	protected boolean Extend(int i)
	{
		if(i==0 && m_mark<3 || i==1 && m_mark>5   
				|| i==2 && m_mark%3==0 || i==3 && m_mark%3==2)  
			return false;  
		int temp=m_mark;  
		m_mark+=d[i];
		//System.out.println("d["+i+"]="+d[i]+"spac"+spac);
		m_integer[temp]=m_integer[m_mark];  
		m_integer[m_mark]=0;
		//System.out.println(" first spac="+temp+"end spac"+spac);
		return true;  
	}
}
