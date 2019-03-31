import java.awt.*;
import java.awt.event.KeyEvent;

import com.ren.game.*;

public class Game extends Canvas implements Runnable,java.awt.event.KeyListener
{
	//��������
	public static final int SOUTH=1;
	public static final int NORTH=2;
	public static final int EAST=3;
	public static final int WEST=4;
	
	private boolean isPaused=false;
	
	private java.awt.Image iBuffer=null;
	private Graphics gBuffer=null;
	//�߶���
	private Snake player;
	//ʳ�����
	private Food food;
	public int direction=EAST;
	//�ߴ�
	public int width=800;
	public int height=450;
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
		TextureManager.getInstance().load("/resource/snake.png", "snake");
		//ʳ��
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
		//���� �Ժ�������ֱ���ñ���ͼƬ
		gBuffer.setColor(getBackground());
		gBuffer.fillRect(0, 0, getWidth(), getHeight());
		//��ͼ
		player.draw(gBuffer);
		food.draw(gBuffer);
		//���Ƶ���Ļ
		g.drawImage(iBuffer,0,0,this.getWidth(),this.getHeight(),null);
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
		long period=1000/2;
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
	
	//��Ϸ�߼�
	public void gameUpdate()
	{
		player.update();
		food.update();
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
	
	//�ڲ���
	/*class ResumeDialog extends JDialog
	{
		private JButton unresume=null;
		private JButton toMenu=null;
		public ResumeDialog(JFrame owner)
		{
			//����ģʽ����
			super(owner,"��ͣ",true);
			//��������
			setFocusable(true);
	        requestFocus();
	        
	        setSize(200,100);
	        
	        unresume=new JButton("��ʼ");
	        unresume.setFont(new java.awt.Font("Serif",java.awt.Font.BOLD,25));
	        unresume.addActionListener(new java.awt.event.ActionListener()
	        {	@Override
				public void actionPerformed(ActionEvent e) 
				{
	        		System.out.println("unresume");
	        		//�����߼�����
	        		isPaused=false;
	        		setVisible(false);
				}
	        });
	        toMenu=new JButton("�˵�");
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


