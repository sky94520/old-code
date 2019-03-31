import java.awt.BorderLayout;
import java.awt.Color;
import java.io.IOException;
import javax.swing.*;
import java.awt.event.*;

@SuppressWarnings("restriction")
public class MainFrame  extends JFrame
{
	private Game game;
	@SuppressWarnings("restriction")
	public MainFrame()
	{
		super();
		game=new Game(this);
		this.getContentPane().add(this.game/*,BorderLayout.EAST*/);
		pack();
	}
	public java.awt.Dimension getPreferredSize()
	{
		return new java.awt.Dimension(900,500);
	}
}
