import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.EventQueue;
import javax.swing.*;

import com.ren.game.Game;

import java.awt.event.*;

public class MainFrame  extends JFrame
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public final static int SCREEN_WIDTH=400;
	public final static int SCREEN_HEIGHT=350;
	
	public MainFrame()
	{
		super();
		//pack();
		Game.getInstance().setScreenSize(SCREEN_WIDTH,SCREEN_HEIGHT);
		Game.getInstance().gameStart();
		this.add(Game.getInstance());
	}
	public static void main(String[] args)
	{
		EventQueue.invokeLater(new Runnable()
		{
			public void run()
			{
				MainFrame frame;
				frame = new MainFrame();
				frame.setSize(new Dimension(SCREEN_WIDTH,SCREEN_HEIGHT));
				frame.setLocationByPlatform(true);
				frame.setTitle("Tile Layer");
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				frame.setResizable(false);
				frame.setVisible(true);
			}
		});
	}
}
