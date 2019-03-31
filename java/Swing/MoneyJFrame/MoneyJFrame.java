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
		//设置窗口
		super("金额大写转换");
		this.setBounds(500,500,400,100);
		this.setBackground(Color.lightGray);
		//不允许修改大小
		this.setResizable(false);
		//设置流式布局
		this.getContentPane().setLayout(new GridLayout(2,2));
		this.getContentPane().add(new JLabel("金额"));

		text_money = new JTextField("12345678.90",22);
		this.getContentPane().add(this.text_money);
		//绑定监听事件
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
						"\""+text_money.getText()+"\""+"不能转换成浮点数，请重新输入");
					//jDialog.show("\""+text_money.getText()+"\""+"不能转换成浮点数，请重新输入");
				}
			}
		});
		this.getContentPane().add(new JLabel("中文大写形式"));
		//text_str 输出转换字符，不支持编辑
		text_str = new JTextField("",22);
		text_str.setEditable(false);
		this.getContentPane().add(this.text_str);
		//创建对话框对象
		this.jDialog = new MessageJDialog();

		this.setDefaultCloseOperation(EXIT_ON_CLOSE);

	}
	/*在这个程序里，Dialog没有JOptionPane简单方便*/
	private class MessageJDialog extends JDialog
	{
		JLabel jLabel;
		public MessageJDialog()
		{
			//依附的窗口 窗口标题 并开启模式窗口
			super(MoneyJFrame.this,"dialog",true);
			this.setSize(300,80);
			
			jLabel = new JLabel("",JLabel.CENTER);
			this.getContentPane().add(this.jLabel);
			//单击对话框的关闭按钮时，隐藏对话框而不结束程序运行
			this.setDefaultCloseOperation(HIDE_ON_CLOSE);

		}
		private void show(String message)
		{
			jLabel.setText(message);
			//对话框显示在框架的右下方
			this.setLocation(MoneyJFrame.this.getX(),
					MoneyJFrame.this.getY()+100);
			//显示对话框
			this.setVisible(true);
		}
	}
	private String RMBtoString(double x)
	{
		String yuan = "亿千百拾万千万拾元角分";
		String digit = "零壹贰叁肆伍陆柒捌玖";
		String result = "";
		int y = (int)(x*100);
		for(int i = yuan.length()-1;y>0&&i>0;i--,y/=10)
			result = ""+digit.charAt(y%10)+yuan.charAt(i)+result;
		return result;
	}
}
