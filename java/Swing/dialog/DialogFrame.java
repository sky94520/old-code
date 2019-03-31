import java.awt.event.*;
import java.awt.*;
import javax.swing.*;

public class DialogFrame extends JFrame
{
	private static final int DEFAULT_WIDTH=300;
	private static final int DEFAULT_HEIGHT=200;
	private AboutDialog dialog;
	public DialogFrame()
	{
		setSize(DEFAULT_WIDTH,DEFAULT_HEIGHT);
		//Construct a File menu
		JMenuBar menuBar = new JMenuBar();
		setJMenuBar(menuBar);
		JMenu fileMenu=new JMenu("File");
		menuBar.add(fileMenu);
		//add About and Exit menu items
		//The About item shows the About dialog
		JMenuItem aboutItem=new JMenuItem("About");
		aboutItem.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent ev)
			{
				if(dialog == null)
					dialog=new AboutDialog(DialogFrame.this);
				dialog.setVisible(true);
			}
		});
		fileMenu.add(aboutItem);
		//The Exit item exits the program
		JMenuItem exitItem=new JMenuItem("Exit");
		exitItem.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent ev)
			{
				System.exit(0);
			}
		});
		fileMenu.add(exitItem);
	}
	public static void main(String[] args)
	{
		EventQueue.invokeLater(new Runnable()
		{
			public void run()
			{
				JFrame frame=new DialogFrame();
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				frame.setVisible(true);
			}
		});
	}
}
