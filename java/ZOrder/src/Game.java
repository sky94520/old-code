import java.awt.*;
import java.awt.event.KeyEvent;

import com.ren.game.*;

public class Game extends Canvas implements Runnable,java.awt.event.KeyListener
{
	
	private boolean isPaused=false;
	
	private java.awt.Image iBuffer=null;
	private Graphics gBuffer=null;
	//�ߴ�
	public int width=800;
	public int height=450;
	
	//����
	private Ribbon mountains;
	private Ribbon trees;
	private Ribbon houses;
	@SuppressWarnings("restriction")
	public Game(javax.swing.JFrame frame)
	{
		//��������
		setFocusable(true);
        requestFocus();
		//ע����̼����¼�
		addKeyListener(this);
		//��ʼ��
		initlize();
		//������Ϸ�߳�
		Thread thread=new Thread(this);
		thread.start();
		
	}
	//��Ϸ��ʼ��
	private void initlize()
	{
		//������Դ
		//����ͼƬ��Դ
		//��������Դ
		TextureManager.getInstance().load("/resource/mountains.gif", "mountains");
		TextureManager.getInstance().load("/resource/trees.gif", "trees");
		TextureManager.getInstance().load("/resource/houses.gif", "houses");
		//���ر���
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
		//���� �Ժ�������ֱ���ñ���ͼƬ
		gBuffer.setColor(getBackground());
		gBuffer.fillRect(0, 0, getWidth(), getHeight());
		//��ͼ
		//TextureManager.getInstance().draw("mountains",0,0,gBuffer);
		//mountains.draw(gBuffer);
		houses.draw(gBuffer);
		//trees.draw(gBuffer);
		//���Ƶ���Ļ
		g.drawImage(iBuffer,0,0,this.getWidth(),this.getHeight(),null);
	}
	//��Ϸ�߼�
	public void gameUpdate()
	{
		mountains.update();
		houses.update();
		trees.update();
	}
	//��Ϸ��Ⱦ
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
		//��Ϊ��̰������Ϸ��֡���޸�
		//���ٶ� 500ms/s
		long period=1000/60;
		t1=System.nanoTime();
		while(true)
		{
			//��Ϸ�߼�
			if(this.isPaused==false)
			{
				gameUpdate();
			}
			//��Ϸ������
			gameRender();
			//�̶�FPS
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


