import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class DataExchangeFrame extends JFrame
{
	public static final int TEXT_ROWS = 20;
	public static final int TEXT_COLUMNS = 40;
	private PasswordChooser dialog=null;
	private JTextArea textArea;

	public DataExchangeFrame()
	{
		//construct a File menu
		JMenuBar mbar=new JMenuBar();
		setJMenuBar(mbar);
		JMenu fileMenu=new JMenu("File");
		mbar.add(fileMenu);
		//add Connect and Exit menu items
		JMenuItem connectItem=new JMenuItem("Connect");
		connectItem.addActionListener(new ConnectionAction());
		fileMenu.add(connectItem);
		//The Eixt item exits the program
		JMenuItem exitItem=new JMenuItem("Exit");
		exitItem.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent ev)
			{
				System.exit(0);
			}
		});
		fileMenu.add(exitItem);
		textArea=new JTextArea(TEXT_ROWS,TEXT_COLUMNS);
		add(new JScrollPane(textArea),BorderLayout.CENTER);
		pack();
	}
	private class ConnectionAction implements ActionListener
	{
		public void actionPerformed(ActionEvent ev)
		{
			System.out.println("ConnectionAction");
			if(dialog ==null)
				dialog=new PasswordChooser();
			//set default values
			dialog.setUser(new User("you name"));
			//pop up dialog
			if(dialog.showDialog(DataExchangeFrame.this,"Connect"))
			{
				User u=dialog.getUser();
				textArea.append("user name="+u.getName()+",password="+new String(u.getPassword())+"\n");
			}
			else
				System.out.println("action");
		}
	}
}
