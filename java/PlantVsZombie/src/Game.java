import java.awt.Graphics;
import java.awt.event.KeyEvent;

import javax.swing.*;

public class Game extends JComponent implements Runnable,java.awt.event.KeyListener
{
	private int x=100,y=100;
	private int dx=0,dy=0;
	
	//
	private boolean isPaused=false;
	public Game()
	{
		setFocusable(true);
        requestFocus();
		//×¢²á¼üÅÌ¼àÌıÊÂ¼ş
		addKeyListener(this);
		Thread thread=new Thread(this);
		thread.start();
	}
	//render
	public void paintComponent(Graphics g)
	{
		g.drawOval(x, y, 40, 40);
	}
	public java.awt.Dimension getPreferredSize()
	{
		return new java.awt.Dimension(300,300);
	}
	public void run() 
	{
		long t1,t2,dt,sleepTime;
		long period=1000/60;
		t1=System.nanoTime();
		while(true)
		{
			//ÓÎÏ·Âß¼­
			if(this.isPaused==false)
			{
				gameUpdate();
			}
			//ÓÎÏ·Ö÷²Ù×÷
			gameRender();
			//¹Ì¶¨FPS
			t2=System.nanoTime();
			dt=(t2-t1)/1000000L;
			sleepTime=period-dt;
			if(sleepTime<=0)
				sleepTime=2;
			try
			{
				Thread.sleep(sleepTime);
			}
			catch(InterruptedException ex)
			{
			}
			t1=System.nanoTime();
		}
	}
	//ÓÎÏ·Âß¼­
	public void gameUpdate()
	{
		//x+=1;
		//y+=1;
	}
	//ÓÎÏ·äÖÈ¾
	public void gameRender()
	{
		repaint();
	}
	public void reset()
	{
		x=100;y=100;
		requestFocus();
	}
	public void keyTyped(KeyEvent e) 
	{
		// TODO Auto-generated method stub	
	}
	public void keyPressed(KeyEvent e) 
	{
		int keyCode=e.getKeyCode();
		
		switch(keyCode)
		{
		case KeyEvent.VK_DOWN: y+=5;
			break;
		case KeyEvent.VK_UP:y-=5;
			break;
		case KeyEvent.VK_LEFT:x-=5;
			break;
		case KeyEvent.VK_RIGHT:x+=5;
			break;
		case KeyEvent.VK_ESCAPE:
			isPaused=!isPaused;
			System.out.println(isPaused);
			break;
		}
	}
	public void keyReleased(KeyEvent e) 
	{
		// TODO Auto-generated method stub
		
	}
}
