import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class AboutDialog extends JDialog
{
	public AboutDialog(JFrame frame)
	{
		super(frame,"About DialogTest",true);
		//add HTML label to center
		add(
			new JLabel("<html><h1><i>Core Java</i></h1><hr>By Horstamnn and Gary Cornell</html>"),BorderLayout.CENTER);
		// Ok button closes the dialog
		JButton ok = new JButton("OK");
		ok.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				setVisible(false);
			}
		});
		JPanel panel=new JPanel();
		panel.add(ok);
		add(panel,BorderLayout.SOUTH);
		this.setLocation(frame.getX()+100,frame.getY());
		pack();
	}
}
