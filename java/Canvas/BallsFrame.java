import java.awt.*;
import javax.swing.*;
import javax.swing.event.*;
public class BallsFrame extends JFrame 
{
	private BallsCanvas canvas;
	private JSpinner spinner;
	public BallsFrame(Color colors[])
	{
		super("µ¯µ¯Çò");
		
		this.setBounds(300,200,400,300);
		this.canvas = new BallsCanvas(colors,100);
		this.getContentPane().add(this.canvas);
		JPanel panel = new JPanel();
		this.add(panel,"South");
		panel.add(new JLabel("Delay"));
		SpinnerNumberModel model = new SpinnerNumberModel();
		model.setStepSize(new Integer(20));
		this.spinner = new JSpinner(model);
		this.spinner.setValue(new Integer(100));
		panel.add(this.spinner);
		this.spinner.addChangeListener(new ChangeListener()
		{
			public void stateChanged(ChangeEvent e)
			{
				canvas.setDelay(Integer.parseInt(""+spinner.getValue()));
			}
		});
	}
	
}
