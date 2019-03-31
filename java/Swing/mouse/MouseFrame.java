import javax.swing.*;
public class MouseFrame extends JFrame
{
	public MouseFrame()
	{
		add(new MouseComponent());
		pack();
	}
	public static void main(String[] args)
	{
		JFrame frame = new MouseFrame();
		frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
}
