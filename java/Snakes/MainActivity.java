import java.awt.*;
import java.io.IOException;

import javax.swing.*;


public class MainActivity 
{
	public static void main(String[] args)
	{
		EventQueue.invokeLater(new Runnable()
		{
			@SuppressWarnings("restriction")
			public void run()
			{
				MainFrame frame;
				frame = new MainFrame();
				//���ƴ��ڶ�λ���
				frame.setLocationByPlatform(true);
				frame.setTitle("̰����");
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				frame.setVisible(true);
			}
		});
	}
}
