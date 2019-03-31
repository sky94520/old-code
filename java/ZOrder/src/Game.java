import java.awt.*;
import java.awt.event.KeyEvent;

import com.ren.game.*;

public class Game extends Canvas implements Runnable,java.awt.event.KeyListener
{
	
	private boolean isPaused=false;
	
	private java.awt.Image iBuffer=null;
	private Graphics gBuffer=null;
	//尺寸
	public int width=800;
	public int height=450;
	
	//背景
	private Ribbon mountains;
	private Ribbon trees;
	private Ribbon houses;
	@SuppressWarnings("restriction")
	public Game(javax.swing.JFrame frame)
	{
		//开启焦点
		setFocusable(true);
        requestFocus();
		//注册键盘监听事件
		addKeyListener(this);
		//初始化
		initlize();
		//开启游戏线程
		Thread thread=new Thread(this);
		thread.start();
		
	}
	//游戏初始化
	private void initlize()
	{
		//加载资源
		//加载图片资源
		//加载蛇资源
		TextureManager.getInstance().load("/resource/mountains.gif", "mountains");
		TextureManager.getInstance().load("/resource/trees.gif", "trees");
		TextureManager.getInstance().load("/resource/houses.gif", "houses");
		//加载背景
		mountains=new Ribbon(1,"mountains",800,450,true);
		houses=new Ribbon(2,"houses",800,450,true);
		trees=new Ribbon(3,"trees",800,450,true);
	}
	//render
	public void paint(Graphics g)
	{
		if(iBuffer==null)
		{
			iBuffer=this.createImage(getWidth(),getHeight());
			gBuffer=iBuffer.getGraphics();
		}
		//清屏 以后清屏可直接用背景图片
		gBuffer.setColor(getBackground());
		gBuffer.fillRect(0, 0, getWidth(), getHeight());
		//绘图
		//TextureManager.getInstance().draw("mountains",0,0,gBuffer);
		//mountains.draw(gBuffer);
		houses.draw(gBuffer);
		//trees.draw(gBuffer);
		//绘制到屏幕
		g.drawImage(iBuffer,0,0,this.getWidth(),this.getHeight(),null);
	}
	//游戏逻辑
	public void gameUpdate()
	{
		mountains.update();
		houses.update();
		trees.update();
	}
	//游戏渲染
	public void gameRender()
	{
		repaint();
	}
	public void reset()
	{
		//
		requestFocus();
	}
	public void update(Graphics g)
	{
		paint(g);
	}
	public void run() 
	{
		long t1,t2,dt,sleepTime;
		//因为是贪吃蛇游戏，帧数修改
		//蛇速度 500ms/s
		long period=1000/60;
		t1=System.nanoTime();
		while(true)
		{
			//游戏逻辑
			if(this.isPaused==false)
			{
				gameUpdate();
			}
			//游戏主操作
			gameRender();
			//固定FPS
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
	public void keyTyped(KeyEvent e) 
	{
		// TODO Auto-generated method stub	
	}
	public void keyPressed(KeyEvent e) 
	{
		int keyCode=e.getKeyCode();
		if(keyCode==KeyEvent.VK_ESCAPE)
		{
			isPaused=!isPaused;
		}
		//System.out.println(isPaused);
		if(this.isPaused==false)
		{
			switch(keyCode)
			{
			case KeyEvent.VK_DOWN:
				break;
			case KeyEvent.VK_UP:
				break;
			case KeyEvent.VK_LEFT:
				break;
			case KeyEvent.VK_RIGHT:
				break;	
			}
		}
	}
	public void keyReleased(KeyEvent e) 
	{
		// TODO Auto-generated method stub
		
	}
	public int getDirection()
	{
		return 0;//return this.direction;
	}
	
}


