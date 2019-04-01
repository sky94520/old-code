import java.awt.Dimension;
import java.awt.Toolkit;

import javax.swing.JFrame;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;

public class Main 
{
	public static void main(String[] args)
	{
		JFrame frame = new PropertyEditorFrame();
		//使用一个皮肤
		try 
		{
	        UIManager.setLookAndFeel("com.pagosoft.plaf.PgsLookAndFeel");
	        // Is your UI already created? So you will have to update the component-tree
	        // of your current frame (or actually all of them...)
	        SwingUtilities.updateComponentTreeUI(frame);
		}
		catch(Exception e) 
		{
			/* Most of the time you're just going to ignore it */ 
		}

		
		javax.swing.SwingUtilities.invokeLater(new Runnable(){
			public void run()
			{
				frame.setTitle("角色属性编辑器");
				frame.setSize(900, 500);
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				frame.setVisible(true);
				//位置居中
				Toolkit kit = Toolkit.getDefaultToolkit();
				Dimension screenSize = kit.getScreenSize();
				frame.setLocation(screenSize.width / 2 - frame.getWidth() / 2,
					screenSize.height / 2 - frame.getHeight() / 2);
			}
		});
	}
}
