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
	private String[] text={"����","����"};
	//����
	private String name;
	private Socket socket;
	private BufferedReader in;
	private PrintWriter out;
	//����������ʾ
	private JTextArea chatShow;
	//�༭�ı�
	private JTextField textEdit;
	//�����ı�
	private JButton sendBtn;
	//��½
	private JButton loginBtn;
	//��ʱ������ʱ�����Դ
	private Thread thread;
	public ChatFrame(String name,Socket socket) 
	{
		//����
		super("�������:"+name);
		setBounds(300,300,400,400);
		
		chatShow=new JTextArea(10,6);
		chatShow.setEditable(false);
		this.add(new JScrollPane(chatShow),BorderLayout.NORTH);
		//�������
		JPanel inputPanel=new JPanel();
		inputPanel.add(textEdit=new JTextField(8));
		inputPanel.add(sendBtn=new JButton("����"));
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
		//objʱJButton��ʵ��
		JButton btn=(JButton)obj;
		if(btn==sendBtn)
		{
			String str=textEdit.getText();
			textEdit.setText("");
			chatShow.append("��˵��"+str+"\n");
			this.out.println(name+"˵��"+str);
		}
		else if(btn==loginBtn)
		{
			//����
			if(btn.getText().equals(text[0]))
			{
				try 
				{
					this.in=new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
					this.out=new PrintWriter(this.socket.getOutputStream(),true);
					this.out.println(this.name);
					this.chatShow.append("����"+this.in.readLine()+"�ɹ�\n");
					btn.setText(text[1]);
					thread.start();
				} 
				catch (IOException e) {}
			}
			//����
			else if(btn.getText().equals(text[1]))
			{
				try 
				{
					this.out.println("�Է��Ѿ�����");
					this.chatShow.append("������\n");
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
