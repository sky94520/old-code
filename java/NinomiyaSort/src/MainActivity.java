import java.awt.EventQueue;

import javax.swing.JFrame;


public class MainActivity 
{
	public static void main(String[] args)
	{
		EventQueue.invokeLater(new Runnable()
		{
			public void run()
			{
				JFrame frame=new ChooseFrame();
				frame.setBounds(300,200,300,300);
				frame.setVisible(true);
			}
		});
	}
}
