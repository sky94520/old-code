import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;


public class ChooseFrame extends JFrame
{
	public ChooseFrame()
	{
		super("ѡ��");
		JPanel panel=new JPanel();
		panel.setLayout(new GridLayout(2,1));
		JButton btn1=new JButton("�˻���������");
		JButton btn2=new JButton("��ʾ��");
		panel.add(btn1);
		panel.add(btn2);
		this.add(panel,BorderLayout.CENTER);
		//���¼�
		btn1.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				int x=getX();
				int y=getY();
				int width=getWidth();
				int height=getHeight();
				//���ش���
				//setVisible(false);
				dispose();
				JFrame frame = new UserInterfaceFrame();
				frame.setBounds(x,y,width,height);
				frame.setVisible(true);
			}
		});
		btn2.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				int x=getX();
				int y=getY();
				int width=getWidth();
				int height=getHeight();
				//���ش���
				//setVisible(false);
				dispose();
				JFrame frame = new ExampleFrame();
				frame.setBounds(x,y,width,height);
				frame.setVisible(true);
			}
		});
	}
}
