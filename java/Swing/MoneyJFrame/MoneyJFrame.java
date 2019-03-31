import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import java.util.*;

public class MoneyJFrame extends JFrame
{
	private JTextField text_money,text_str;
	private MessageJDialog jDialog;
	public MoneyJFrame()
	{
		//���ô���
		super("����дת��");
		this.setBounds(500,500,400,100);
		this.setBackground(Color.lightGray);
		//�������޸Ĵ�С
		this.setResizable(false);
		//������ʽ����
		this.getContentPane().setLayout(new GridLayout(2,2));
		this.getContentPane().add(new JLabel("���"));

		text_money = new JTextField("12345678.90",22);
		this.getContentPane().add(this.text_money);
		//�󶨼����¼�
		this.text_money.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent ev)
			{
				try
				{ 
					double x = Double.parseDouble(text_money.getText());
					text_str.setText(RMBtoString(x));
				}
				catch(NumberFormatException nfex)
				{
					JOptionPane.showMessageDialog(MoneyJFrame.this,
						"\""+text_money.getText()+"\""+"����ת���ɸ�����������������");
					//jDialog.show("\""+text_money.getText()+"\""+"����ת���ɸ�����������������");
				}
			}
		});
		this.getContentPane().add(new JLabel("���Ĵ�д��ʽ"));
		//text_str ���ת���ַ�����֧�ֱ༭
		text_str = new JTextField("",22);
		text_str.setEditable(false);
		this.getContentPane().add(this.text_str);
		//�����Ի������
		this.jDialog = new MessageJDialog();

		this.setDefaultCloseOperation(EXIT_ON_CLOSE);

	}
	/*����������Dialogû��JOptionPane�򵥷���*/
	private class MessageJDialog extends JDialog
	{
		JLabel jLabel;
		public MessageJDialog()
		{
			//�����Ĵ��� ���ڱ��� ������ģʽ����
			super(MoneyJFrame.this,"dialog",true);
			this.setSize(300,80);
			
			jLabel = new JLabel("",JLabel.CENTER);
			this.getContentPane().add(this.jLabel);
			//�����Ի���Ĺرհ�ťʱ�����ضԻ������������������
			this.setDefaultCloseOperation(HIDE_ON_CLOSE);

		}
		private void show(String message)
		{
			jLabel.setText(message);
			//�Ի�����ʾ�ڿ�ܵ����·�
			this.setLocation(MoneyJFrame.this.getX(),
					MoneyJFrame.this.getY()+100);
			//��ʾ�Ի���
			this.setVisible(true);
		}
	}
	private String RMBtoString(double x)
	{
		String yuan = "��ǧ��ʰ��ǧ��ʰԪ�Ƿ�";
		String digit = "��Ҽ��������½��ƾ�";
		String result = "";
		int y = (int)(x*100);
		for(int i = yuan.length()-1;y>0&&i>0;i--,y/=10)
			result = ""+digit.charAt(y%10)+yuan.charAt(i)+result;
		return result;
	}
}
