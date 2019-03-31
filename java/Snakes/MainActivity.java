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
				//¿ØÖÆ´°¿Ú¶¨Î»¿ò¼Ü
				frame.setLocationByPlatform(true);
				frame.setTitle("Ì°³ÔÉß");
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				frame.setVisible(true);
			}
		});
	}
}
