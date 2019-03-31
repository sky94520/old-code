import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

public class BallsCanvas extends Canvas implements FocusListener,ActionListener
{
	private Ball balls[];
	private Timer timer;
	//image Ë«»º³å
	Image iBuffer;
	Graphics gBuffer;
	private static class Ball
	{
		int x,y;
		Color color;
		boolean up,left;
		Ball(int x,int y,Color color)
		{
			this.x = x;
			this.y = y;
			this.color = color;
		}
	}
	public BallsCanvas(Color colors[],int delay)
	{
		 this.balls = new Ball[colors.length];
		 for(int i=0,x=0;i<colors.length;i++,x+=40)
			 this.balls[i]=new Ball(x,x,colors[i]);
		 this.addFocusListener(this);
		 timer = new Timer(delay,this);
		 timer.start();
		 this.iBuffer = null;
	}
	public void paint(Graphics g)
	{
		if(this.iBuffer == null)
		{
			this.iBuffer = this.createImage(this.getWidth(),this.getHeight());
			gBuffer = this.iBuffer.getGraphics();
		}
		//clear
		gBuffer.setColor(getBackground());
		gBuffer.fillRect(0, 0, this.getSize().width,this.getSize().height);
		for(int i=0;i<balls.length;i++)
		{
			gBuffer.setColor(balls[i].color);
			balls[i].x = balls[i].left?balls[i].x-10:balls[i].x+10;
			if(balls[i].x<=0||balls[i].x+20>=this.getWidth())
				balls[i].left = !balls[i].left;
			balls[i].y = balls[i].up?balls[i].y-10:balls[i].y+10;
			if(balls[i].y<=0 || balls[i].y + 20>=this.getHeight())
				balls[i].up = !balls[i].up;
			gBuffer.drawOval(balls[i[.x,balls[i].y,20,20);
			gBuffer.fillOval(balls[i].x,balls[i].y,20,20);
		}
		//gOffScreen.dispose();
		g.drawImage(this.iBuffer, 0, 0, this);
	}
	public void update(Graphics g)
	{
		paint(g);
	}
/*	public Dimension getPreferredSize()
	{
		return new Dimension(300,200);
	}*/
	public void setDelay(int delay)
	{
		timer.setDelay(delay);
	}
	public void actionPerformed(ActionEvent ev)
	{
		repaint();
	}
	public void focusGained(FocusEvent ev)
	{
		timer.stop();
	}
	public void focusLost(FocusEvent ev)
	{
		timer.start();
	}
}
