import java.awt.*;
import java.awt.event.KeyEvent;

import com.ren.game.*;

public class Game extends Canvas implements Runnable,java.awt.event.KeyListener
{
	//按键方向
	public static final int SOUTH=1;
	public static final int NORTH=2;
	public static final int EAST=3;
	public static final int WEST=4;
	
	private boolean isPaused=false;
	
	private java.awt.Image iBuffer=null;
	private Graphics gBuffer=null;
	//蛇对象
	private Snake player;
	//食物对象
	private Food food;
	public int direction=EAST;
	//尺寸
	public int width=800;
	public int height=450;
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
		TextureManager.getInstance().load("/resource/snake.png", "snake");
		//食物
		TextureManager.getInstance().load("/resource/apple.png", "apple");

		player=new Snake(this);
		food=new Food(this,player);
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
		player.draw(gBuffer);
		food.draw(gBuffer);
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
		//因为是贪吃蛇游戏，帧数修改
		//蛇速度 500ms/s
		long period=1000/2;
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
	
	//游戏逻辑
	public void gameUpdate()
	{
		player.update();
		food.update();
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
				if(direction!=NORTH&&direction!=SOUTH)
					{
						direction=SOUTH;
					}
				break;
			case KeyEvent.VK_UP:
				if(direction!=SOUTH&&direction!=NORTH)
					{
						direction=NORTH;
					}
				break;
			case KeyEvent.VK_LEFT:
				if(direction!=EAST&&direction!=WEST)
					{
						direction=WEST;
					}
				break;
			case KeyEvent.VK_RIGHT:
				if(direction!=WEST&&direction!=EAST)
					{
						direction=EAST;
					}
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
		return this.direction;
	}
	
	//内部类
	/*class ResumeDialog extends JDialog
	{
		private JButton unresume=null;
		private JButton toMenu=null;
		public ResumeDialog(JFrame owner)
		{
			//开启模式特征
			super(owner,"暂停",true);
			//开启焦点
			setFocusable(true);
	        requestFocus();
	        
	        setSize(200,100);
	        
	        unresume=new JButton("开始");
	        unresume.setFont(new java.awt.Font("Serif",java.awt.Font.BOLD,25));
	        unresume.addActionListener(new java.awt.event.ActionListener()
	        {	@Override
				public void actionPerformed(ActionEvent e) 
				{
	        		System.out.println("unresume");
	        		//开启逻辑更新
	        		isPaused=false;
	        		setVisible(false);
				}
	        });
	        toMenu=new JButton("菜单");
	        toMenu.setFont(new java.awt.Font("Serif",java.awt.Font.BOLD,25));
	        toMenu.addActionListener(new java.awt.event.ActionListener()
	        {	@Override
				public void actionPerformed(ActionEvent e) 
				{
	        		System.out.println("to menu");
	        		setVisible(false);
				}
	        });
	        this.add(unresume);
	        this.add(toMenu);
	        setVisible(true);
		}
	}*/
}


