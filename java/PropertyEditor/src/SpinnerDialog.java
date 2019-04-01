import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSpinner;
import javax.swing.SpinnerNumberModel;

public class SpinnerDialog extends JDialog implements ActionListener
{
	private JSpinner m_spinner;
	private SpinnerNumberModel m_model = null;
	private boolean m_returnVal = false;
	
	public SpinnerDialog(JFrame owner, String title, boolean model)
	{
		super(owner, title, model);
		
		JPanel panel = new JPanel();
		panel.setLayout(new GridLayout(2, 1));
		this.add(panel);
		
		m_model = new SpinnerNumberModel();
		m_spinner = new JSpinner(m_model);
		panel.add(m_spinner);
		
		JButton okBtn = new JButton("确认");
		okBtn.addActionListener(this);
		panel.add(okBtn);
		//设置位置
		Rectangle bounds = owner.getBounds();
		this.setBounds(bounds.x + bounds.width / 2 - 50, bounds.y + bounds.height / 2 - 30, 150, 120);
		
		this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE); 
	}
	public boolean showDialog()
	{
		this.setVisible(true);
		boolean ret = m_returnVal;
		m_returnVal = false;
		return ret;
	}

	@Override
	public void actionPerformed(ActionEvent arg0) 
	{
		// TODO Auto-generated method stub
		this.setVisible(false);
		m_returnVal = true;
	}

	public int getValue() 
	{
		return (Integer)m_spinner.getValue();
	}

	public void setValue(int value)
	{
		m_spinner.setValue(value);
	}
	
	public void setMinimum(Comparable<?> t)
	{
		m_model.setMinimum(t);
	}
	public void setMaximum(Comparable<?> t)
	{
		m_model.setMaximum(t);
	}
}
