import java.awt.Component;
import java.awt.Graphics;
import java.net.URL;

import javax.swing.Icon;
import javax.swing.ImageIcon;

public class ImageProxy implements Icon
{
	ImageIcon imageIcon;
	URL imageURL;
	Thread retrievalThread;
	boolean retrieving = false;
	
	public ImageProxy(URL url)
	{
		imageURL = url;
	}
	@Override
	public int getIconHeight() {
		// TODO Auto-generated method stub
		if(imageIcon != null)
			return imageIcon.getIconHeight();
		return 600;
	}

	@Override
	public int getIconWidth() {
		// TODO Auto-generated method stub
		if(imageIcon != null)
			return imageIcon.getIconWidth();
		return 800;
	}

	@Override
	public void paintIcon(final Component c, Graphics g, int x, int y) {
		// TODO Auto-generated method stub
		if(imageIcon != null)
			imageIcon.paintIcon(c, g, x, y);
		else
		{
			g.drawString("Loading CD cover,please wait", x+300, y+190);
			if(!retrieving)
			{
				retrieving = true;
				retrievalThread = new Thread(new Runnable()
				{
					public void run()
					{
						try{
							imageIcon = new ImageIcon(imageURL,"CD cover");
							c.repaint();
						}catch(Exception e)
						{
							e.printStackTrace();
						}
					}
				});
				retrievalThread.start();
			}
			
		}
	}

}
