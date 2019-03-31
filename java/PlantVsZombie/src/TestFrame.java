import java.awt.BorderLayout;
import java.awt.Color;
import java.io.IOException;
import javax.swing.*;
import java.awt.event.*;

public class TestFrame  extends JFrame
{
	private Game game;
	private JButton button;
	public TestFrame() throws IOException
	{
		//JComponent comp = new TestComponent();
		//this.add(comp);
		button=new JButton("get");
		game=new Game();
		button.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e) 
			{
				game.reset();
			}
		});
		this.add(button,BorderLayout.NORTH);
		this.add(game,BorderLayout.SOUTH);
		pack();
	}
	public java.awt.Dimension getPreferredSize()
	{
		return new java.awt.Dimension(300,300);
	}
}
