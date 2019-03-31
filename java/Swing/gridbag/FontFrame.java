import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.beans.*;
public class FontFrame extends JFrame
{
	public static final int TEXT_ROWS = 10;
	public static final int TEXT_COLUMNS=20;
	private JComboBox<String> face;
	private JComboBox<Integer> size;
	private JCheckBox bold;
	private JCheckBox italic;
	private JTextArea sample;

	public FontFrame()
	{
		//get font name
		String[] fontNames = GraphicsEnvironment
			.getLocalGraphicsEnvironment()
			.getAvailableFontFamilyNames();
		GridBagLayout layout = new GridBagLayout();
		this.setLayout(layout);
		//???
		ActionListener listener=EventHandler.create(ActionListener.class,this,
				"updateSample");
		//construct components
		JLabel faceLabel = new JLabel("Face:");
		face = new JComboBox<String>(fontNames);
		face.addActionListener(listener);

		JLabel sizeLabel = new JLabel("size:");
		sizeLabel.setFont(new Font("Serif",0,24));
		size = new JComboBox<Integer>(new Integer[]{8,10,12,15,18,24,36,48});
		size.addActionListener(listener);

		bold = new JCheckBox("Bold");
		bold.addActionListener(listener);

		italic = new JCheckBox("italic");
		italic.addActionListener(listener);

		sample = new JTextArea(TEXT_ROWS,TEXT_COLUMNS);
		sample.setText("The quick brown for jumps over the lazy dog");
		sample.setEditable(true);
		//??
		sample.setLineWrap(true);
		sample.setBorder(BorderFactory.createEtchedBorder());
		//add component to grid,using GBC convenience class
		add(faceLabel,new GBC(0,0).setAnchor(GBC.EAST));
		add(face,new GBC(1,0).setFill(GBC.HORIZONTAL).setWeight(100,0).setInsets(1));
		add(sizeLabel,new GBC(0,1).setAnchor(GBC.EAST));
		add(size,new GBC(1,1).setFill(GBC.HORIZONTAL).setWeight(100,0).setInsets(1));
		add(bold,new GBC(0,2,2,1).setAnchor(GBC.CENTER).setWeight(100,100));
		add(italic,new GBC(0,3,2,1).setAnchor(GBC.CENTER).setWeight(100,100));
		add(sample,new GBC(2,0,1,4).setFill(GBC.BOTH).setWeight(100,100));
		pack();
		//?
		updateSample();
	}
	public void updateSample()
	{
		String fontFace=(String)face.getSelectedItem();
		int fontStyle = (bold.isSelected()?Font.BOLD:0)
			+(italic.isSelected()?Font.ITALIC:0);
		int fontSize = size.getItemAt(size.getSelectedIndex());
		Font font = new Font(fontFace,fontStyle,fontSize);
		sample.setFont(font);
		sample.repaint();
	}
}
