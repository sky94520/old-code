
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JTextField;


public class MonthCalendar 
{
	public static void main(String[] args)
	{
		/*SimpleDateFormat sdf=new SimpleDateFormat("yyyy年MM月dd日E a hh时mm分ss秒");
		System.out.println(sdf.format(new Date()));
		long lg=System.currentTimeMillis();*/
		JFrame frame=new MainFrame();
		frame.setBounds(600,400,100,100);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
		}
}
