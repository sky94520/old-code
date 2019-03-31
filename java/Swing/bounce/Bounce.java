import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
public class Bounce
{
	public static void main(String[] args)
	{
		EventQueue.invokeLater(new Runnable()
				{
					public void run()
					{
						JFrame frame = new BounceFrame();
						frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
						frame.setVisible(true);
					}
				});
	}
}
class BounceFrame extends JFrame
{
	private BallComponent comp;
	public static final int STEPS=1000;
	public static final int DELAY=3;
	public BounceFrame()
	{
		setTitle("Bounce");
		comp = new BallComponent();
		this.add(comp,BorderLayout.CENTER);
		JPanel panel = new JPanel();

		addButton(panel,"Start",new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				addBall();
			}
		});
		addButton(panel,"Close",new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				System.exit(0);
			}
		});
		add(panel,BorderLayout.SOUTH);
		pack();
	}
	private void addButton(Container c,String title,ActionListener listener)
	{
		JButton button = new JButton(title);
		button.addActionListener(listener);
		c.add(button);
	}
	private void addBall()
	{
		try
		{
			Ball ball = new Ball();
			comp.add(ball);
			for(int i=1;i<=STEPS;i++)
			{
				ball.move(comp.getBounds());
				comp.paint(comp.getGraphics());
				Thread.sleep(DELAY);
			}
		}
		catch(InterruptedException e)
		{}
	}
}
