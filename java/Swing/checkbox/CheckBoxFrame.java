import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class CheckBoxFrame extends JFrame implements ActionListener
{
	private JLabel label;
	private JCheckBox bold;
	private JCheckBox italic;
	private final static int FONTSIZE = 30;
	public CheckBoxFrame()
	{
		super("CheckBoxFrame");
		this.label = new JLabel("Hello World!!!");
		this.getContentPane().add(this.label,BorderLayout.CENTER);
		JPanel gridPanel = new JPanel(new GridLayout(2,1));
		bold = new JCheckBox("Bold");
		italic = new JCheckBox("Italic");
		gridPanel.add(bold);
		gridPanel.add(italic);
		this.add(gridPanel,BorderLayout.SOUTH);
		bold.addActionListener(this);
		italic.addActionListener(this);
		this.pack();
	}
	public void actionPerformed(ActionEvent ev)
	{
		int mode = Font.PLAIN;
		mode += (bold.isSelected()?Font.BOLD:Font.PLAIN);
		mode += (italic.isSelected()?Font.ITALIC:Font.PLAIN);
		this.label.setFont(new Font("Serif",mode,FONTSIZE));
	}
	public static void main(String[] args)
	{
		EventQueue.invokeLater(new Runnable()
		{
			public void run()
			{
				JFrame frame = new CheckBoxFrame();
				frame.setDefaultCloseOperation(frame.EXIT_ON_CLOSE);
				frame.setVisible(true);
			}
		}
				);
	}
}
