import java.awt.*;

import javax.swing.JFrame;
public class MainActivity 
{
	public static void main(String[] args)
	{
		EventQueue.invokeLater(new Runnable()
		{
			public void run()
			{
				EditorJFrame frame = new EditorJFrame();
				frame.setSize(800,600);
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				frame.setLocationRelativeTo(null);
				frame.setVisible(true);
			}
		});
	}
}
