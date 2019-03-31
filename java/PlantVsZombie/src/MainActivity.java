import java.awt.*;
import java.io.IOException;

import javax.swing.*;


public class MainActivity 
{
	public static void main(String[] args)
	{
		EventQueue.invokeLater(new Runnable()
		{
			public void run()
			{
				TestFrame frame;
				try {
					frame = new TestFrame();
					frame.setLocation(300,300);
					frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
					frame.setVisible(true);
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		});
	}
}
