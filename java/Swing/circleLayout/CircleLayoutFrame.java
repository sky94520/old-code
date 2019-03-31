import java.awt.*;
import javax.swing.*;

public class CircleLayoutFrame extends JFrame
{
	public CircleLayoutFrame()
	{
		setLayout(new CircleLayout());
		add(new JButton("Yellow"));
		add(new JButton("Blue"));
		add(new JButton("Red"));
		add(new JButton("Green"));
		add(new JButton("Orange"));
		add(new JButton("Fuchsia"));
		add(new JButton("Indigo"));
		setBounds(200,200,400,400);
	}
	public static void main(String[] args)
	{
		EventQueue.invokeLater(new Runnable()
		{
			public void run()
			{
				JFrame frame = new CircleLayoutFrame();
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				frame.setVisible(true);
			}
		});
	}
}
