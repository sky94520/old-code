import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JColorChooser;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JRadioButton;
import javax.swing.JSpinner;
import javax.swing.JTextField;
import javax.swing.SpinnerNumberModel;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;


public class MainFrame extends JFrame implements ActionListener
{
	JSpinner spinner;
	boolean isLoved=false;
	public MainFrame()
	{
		super("main");
		
		this.setLayout(new FlowLayout());
		
		SpinnerNumberModel spinnerModel=new SpinnerNumberModel(100,0,100,2);
		spinnerModel.setStepSize(1);
		spinner=new JSpinner(spinnerModel);
		spinner.addChangeListener(new ChangeListener()
		{
			public void stateChanged(ChangeEvent e)
			{
				System.out.println(spinner.getValue());
			}
		});
		JCheckBox loveBtn=new JCheckBox("Do you love me?");
		loveBtn.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				isLoved=!isLoved;
				//System.out.println("is love?"+isLoved);
				if(isLoved)
					//JOptionPane.showConfirmDialog(MainFrame.this,"我知道你爱我","title",JOptionPane.OK_CANCEL_OPTION);
					JColorChooser.showDialog(MainFrame.this,"color", null);
			}
		});
		JRadioButton sex1=new JRadioButton("男");
		JRadioButton sex2=new JRadioButton("女");
		ButtonGroup btnGroup=new ButtonGroup();
		sex1.addActionListener(this);
		sex2.addActionListener(this);
		btnGroup.add(sex1);
		btnGroup.add(sex2);
		this.add(sex1);
		this.add(sex2);
		this.add(spinner);
		this.add(loveBtn);
	}
	@Override
	public void actionPerformed(ActionEvent e) 
	{
		if(e.getActionCommand()=="男")
			System.out.println("男");
		else
			System.out.println("女");
	}
}
