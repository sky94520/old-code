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
				//控制窗口定位框架
				frame.setLocationByPlatform(true);
				frame.setTitle("卷轴型图像");
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				frame.setVisible(true);
			}
		});
	}
}
