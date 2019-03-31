import java.awt.GridLayout;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.JOptionPane;


public class UserInterfaceFrame extends SortFrame  implements KeyListener
{
	public UserInterfaceFrame()
	{
		super("人机交互界面");
		//设置3*3界面
		this.setLayout(new GridLayout(3,3));
		//响应键盘事件
		setFocusable(true);
		addKeyListener(this);
		pack();
	}
	@Override
	public void keyPressed(KeyEvent e) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void keyReleased(KeyEvent e) {
		// TODO Auto-generated method stub
		int i=-1;
		switch(e.getKeyCode())
		{
		case KeyEvent.VK_DOWN:
			i=0;
			break;
		case KeyEvent.VK_RIGHT:
			i=2;
			break;
		case KeyEvent.VK_UP:
			i=1;
			break;
		case KeyEvent.VK_LEFT:
			i=3;
			break;
		}
		if(i!=-1)
		{
			Extend(i);
			updateCanvas();
		}
		if(isWin())
			JOptionPane.showMessageDialog(this,"你赢啦，恭喜");
			
	}
	@Override
	public void keyTyped(KeyEvent e) {
		// TODO Auto-generated method stub
		
	}
	private void updateCanvas()
	{
		for(int i=0;i<9;i++)
			m_label[i].setText(""+(m_integer[i]==0?"":m_integer[i]));
	}
}
