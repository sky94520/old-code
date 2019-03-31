import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class ComboBoxFrame extends JFrame
{
	private JComboBox<String> faceCombo;
	private JLabel label;
	private static final int DEFAULT_SIZE = 24;
	public ComboBoxFrame()
	{
		String[] fontName = {"Serif","SansSerif","Monospaced","Dialog","DialogInput"};
		this.label = new JLabel("I Love You");
		this.label.setFont(new Font("Serif",Font.PLAIN,DEFAULT_SIZE));
		this.add(this.label,BorderLayout.CENTER);
		faceCombo = new JComboBox<String>();
		DefaultComboBoxModel comboModel = new DefaultComboBoxModel();
		for(String s:fontName)
			comboModel.addElement(s);
		faceCombo.setModel(comboModel);
		faceCombo.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				label.setFont(new Font(faceCombo.getItemAt(faceCombo.getSelectedIndex()),Font.PLAIN,DEFAULT_SIZE));
			}
		});
		JPanel panel = new JPanel();
		panel.add(faceCombo);
		this.add(panel,BorderLayout.SOUTH);
		pack();
	}
	public static void main(String[] args)
	{
		EventQueue.invokeLater(new Runnable()
		{
			public void run()
			{
				JFrame frame = new ComboBoxFrame();
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				frame.setVisible(true);
			}
		});
	}
}
