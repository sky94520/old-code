import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class TextComponentFrame extends JFrame
{
	private static final int TEXTAREA_ROWS = 8;
	private static final int TEXTAREA_COLUMNS = 20;
	public TextComponentFrame()
	{
		final JTextField textField = new JTextField();
		final JPasswordField passwordField = new JPasswordField();

		JPanel northPanel = new JPanel();
		northPanel.setLayout(new GridLayout(2,2));
		northPanel.add(new JLabel("User Name:",SwingConstants.RIGHT));
		northPanel.add(textField);
		northPanel.add(new JLabel("Password:",SwingConstants.RIGHT));
		northPanel.add(passwordField);

		this.add(northPanel,BorderLayout.NORTH);
		final JTextArea textArea = new JTextArea(TEXTAREA_ROWS,TEXTAREA_COLUMNS);
		JScrollPane scrollPane = new JScrollPane(textArea);
		add(scrollPane,BorderLayout.CENTER);
		//add button to append text into the text area
		JPanel southPanel = new JPanel();
		JButton insertButton = new JButton("Insert");
		southPanel.add(insertButton);
		insertButton.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent ev)
			{
				textArea.append("User name:"+textField.getText()+" Password:"+new String(passwordField.getPassword())+"\n");
			}
		});
		add(southPanel,BorderLayout.SOUTH);
		pack();
	}
	public static void main(String[] args)
	{
		EventQueue.invokeLater(new Runnable()
				{
					public void run()
					{
						JFrame frame = new TextComponentFrame();
						frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
						frame.setVisible(true);
					}
				});
	}
}
