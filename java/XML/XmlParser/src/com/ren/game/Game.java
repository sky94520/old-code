package com.ren.game;
import java.awt.*;
import java.awt.event.KeyEvent;

public class Game extends Canvas implements Runnable,java.awt.event.KeyListener
{
	private boolean isPaused=false;
	
	private java.awt.Image iBuffer=null;
	private Graphics gBuffer=null;
	
	private TiledMap tiledMap;
	
	public int SCREEN_WIDTH;
	public int SCREEN_HEIGHT;
	
	private static Game gInstance=null;
	public static Game getInstance()
	{
		if(gInstance==null)
			gInstance=new Game();
		return gInstance;
	}
	private Game()
	{
		//开启焦点
		setFocusable(true);
        requestFocus();
		//注册键盘监听事件
		addKeyListener(this);
		//初始化
		initlize();
	}
	public void setScreenSize(int width,int height)
	{
		SCREEN_WIDTH=width;
		SCREEN_HEIGHT=height;
	}
	public void gameStart()
	{
		//开启游戏线程
		Thread thread=new Thread(this);
		thread.start();
	}
	//游戏初始化
	private void initlize()
	{
		//加载资源
		tiledMap=new TiledMap("/resources/map1.tmx");
		System.out.println(tiledMap.toString());
		//图片资源
		tiledMap.loadSources("/resources/");
	}
	//游戏逻辑
	public void gameUpdate()
	{
		//if(!DialogManager.getInstance().update())
			tiledMap.update();
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
		tiledMap.draw(gBuffer);
		//DialogManager.getInstance().draw(gBuffer);
		//绘制到屏幕
		g.drawImage(iBuffer,0,0,this.getWidth(),this.getHeight(),null);
	}
	
	public void update(Graphics g)
	{
		paint(g);
	}
	public void run() 
	{
		long t1,t2,dt,sleepTime;
		//60fps
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
			InputHandler.getInstance().update(keyCode, true);
		}
	}
	public void keyReleased(KeyEvent e) 
	{
		int keyCode=e.getKeyCode();
		if(keyCode==KeyEvent.VK_ESCAPE)
		{
			isPaused=!isPaused;
		}
		//System.out.println(isPaused);
		if(this.isPaused==false)
		{
			InputHandler.getInstance().update(keyCode, false);
		}
	}
	public int getWidth()
	{
		return SCREEN_WIDTH;
	}
	public int getHeight()
	{
		return SCREEN_HEIGHT;
	}
}