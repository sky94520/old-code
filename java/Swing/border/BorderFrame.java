import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;
public class BorderFrame extends JFrame
{
	private JPanel demoPanel;
	private JPanel buttonPanel;
	private ButtonGroup group;
	public BorderFrame()
	{
		demoPanel = new JPanel();
		buttonPanel = new JPanel();
		group = new ButtonGroup();

		addRadioButton("Lowered bevel",BorderFactory.createLoweredBevelBorder());
		addRadioButton("Raised bevel",BorderFactory.createRaisedBevelBorder());
		addRadioButton("Etched",BorderFactory.createEtchedBorder());
		addRadioButton("Line",BorderFactory.createLineBorder(Color.BLUE));
		addRadioButton("Matte",BorderFactory.createMatteBorder(10,10,10,10,Color.BLUE));
		addRadioButton("Empty",BorderFactory.createEmptyBorder());

		Border etched = BorderFactory.createEtchedBorder();
		Border titled = BorderFactory.createTitledBorder(etched,"Border types");
		buttonPanel.setBorder(titled);
		///this.setBorder(new TitledBorder("Person")); 
		setLayout(new GridLayout(2,1));
		add(buttonPanel);
		add(demoPanel);
		pack();
	}
	public void addRadioButton(String buttonName,final Border b)
	{
		JRadioButton button = new JRadioButton(buttonName);
		button.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent ev)
			{
				demoPanel.setBorder(b);
			}
		});
		group.add(button);
		buttonPanel.add(button);
	}
	public static void main(String[] args)
	{
		EventQueue.invokeLater(
		new Runnable()
		{
			public void run()
			{
				BorderFrame frame = new BorderFrame();
				frame.setDefaultCloseOperation(frame.EXIT_ON_CLOSE);
				frame.setVisible(true);
			}
		});
	}
}
