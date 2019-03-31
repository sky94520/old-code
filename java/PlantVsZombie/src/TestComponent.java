import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import javax.imageio.*;
import java.io.*;
import java.io.IOException;

import javax.swing.*;

public class TestComponent extends JComponent
{
	private BufferedImage image=null;
	private BufferedImage subImage=null;
	//定时器
	private Timer timer;
	private int x=0;
	private final int MAX_FRAME=8;
	public TestComponent() throws IOException
	{
		try
		{
			String path=getClass().getProtectionDomain().getCodeSource().getLocation().getPath();
			path += "run.png";
			image=ImageIO.read(new FileInputStream("G:\\c语言\\java\\植物大战僵尸\\src\\run2.png"));
			//subImage = image.getSubimage(0, 0, image.getWidth()/4, image.getHeight()/4);
			
			this.timer=new Timer(150,new ActionListener()
			{
				public void actionPerformed(ActionEvent e)
				{
					int w=image.getWidth()/MAX_FRAME;
					int h=image.getHeight();
					//y=x++%3;
					subImage = image.getSubimage((x++%MAX_FRAME)*w,0, w,h);
					repaint();
				}
			});
			//start
			this.timer.start();
		}
		catch(IOException ex)
		{
			ex.printStackTrace();
		}
	}
	public void paintComponent(Graphics g)
	{
		if(subImage != null)
			g.drawImage(subImage,0,0,subImage.getWidth(),subImage.getHeight(),null);
	}
}
