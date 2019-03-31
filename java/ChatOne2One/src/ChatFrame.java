import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

public class ChatFrame extends JFrame implements ActionListener,WindowListener
{
	private String[] text={"上线","下线"};
	//网名
	private String name;
	private Socket socket;
	private BufferedReader in;
	private PrintWriter out;
	//聊天文字显示
	private JTextArea chatShow;
	//编辑文本
	private JTextField textEdit;
	//发送文本
	private JButton sendBtn;
	//登陆
	private JButton loginBtn;
	//定时器，定时检查资源
	private Thread thread;
	public ChatFrame(String name,Socket socket) 
	{
		//界面
		super("聊天界面:"+name);
		setBounds(300,300,400,400);
		
		chatShow=new JTextArea(10,6);
		chatShow.setEditable(false);
		this.add(new JScrollPane(chatShow),BorderLayout.NORTH);
		//输入界面
		JPanel inputPanel=new JPanel();
		inputPanel.add(textEdit=new JTextField(8));
		inputPanel.add(sendBtn=new JButton("发送"));
		inputPanel.add(loginBtn=new JButton(text[0]));
		this.add(inputPanel);
		//textEdit.addActionListener(this);
		sendBtn.addActionListener(this);
		loginBtn.addActionListener(this);
		//
		this.name=name;
		this.socket=socket;
		pack();
		setVisible(true);
		this.thread=new Thread(new Runnable()
		{
			public void run()
			{
				while(true)
				{
					if(in!=null)
					{
						try
						{
							String str=in.readLine();
							if(str!=null)
								chatShow.append(str+"\n");
						} catch (IOException e) 
						{
							e.printStackTrace();
						}
					}
				}
			}
		});
	}
	public void actionPerformed(ActionEvent ev)
	{
		Object obj=ev.getSource();
		//obj时JButton的实例
		JButton btn=(JButton)obj;
		if(btn==sendBtn)
		{
			String str=textEdit.getText();
			textEdit.setText("");
			chatShow.append("我说："+str+"\n");
			this.out.println(name+"说："+str);
		}
		else if(btn==loginBtn)
		{
			//上线
			if(btn.getText().equals(text[0]))
			{
				try 
				{
					this.in=new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
					this.out=new PrintWriter(this.socket.getOutputStream(),true);
					this.out.println(this.name);
					this.chatShow.append("连接"+this.in.readLine()+"成功\n");
					btn.setText(text[1]);
					thread.start();
				} 
				catch (IOException e) {}
			}
			//下线
			else if(btn.getText().equals(text[1]))
			{
				try 
				{
					this.out.println("对方已经下线");
					this.chatShow.append("已下线\n");
					btn.setText(text[0]);
					this.in.close();					
					this.out.close();
				} 
				catch (IOException e) {}
			}
		}//end btn
	}
	@Override
	public void windowOpened(WindowEvent e) 
	{
	}
	@Override
	public void windowClosing(WindowEvent e) 
	{
	}
	@Override
	public void windowClosed(WindowEvent e) 
	{
	}
	@Override
	public void windowIconified(WindowEvent e) 
	{
	}
	@Override
	public void windowDeiconified(WindowEvent e) 
	{
	}
	@Override
	public void windowActivated(WindowEvent e) 
	{
	}
	@Override
	public void windowDeactivated(WindowEvent e) 
	{
	}
}
