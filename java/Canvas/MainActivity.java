import java.awt.Color;
import java.awt.EventQueue;
import javax.swing.JFrame;

public class MainActivity 
{
	public static void main(String[] args)
	{
		final Color[] colors={Color.red,Color.green,Color.blue,Color.magenta,Color.cyan};
		EventQueue.invokeLater(new Runnable()
		{
			public void run()
			{
				JFrame frame = new BallsFrame(colors);
				frame.setDefaultCloseOperation(frame.EXIT_ON_CLOSE);
				frame.setVisible(true);
			}
		});
	}
}
