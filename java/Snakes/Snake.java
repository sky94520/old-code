import java.awt.Point;
import java.awt.*;
import com.datastructure.*;

import com.ren.game.*;


public class Snake
{
	//����󳤶� default
	static final int MAXLENGTH=50;
	//������
	private  Point[] body;
	public int speed;
	//��ͷ ��β
	private int head;
	private int tail;
	
	public int length;
	//��ͷλ��
	public int x;
	public int y;
	//�߳ߴ�
	public int size;
	Game gameP;
	
	public Snake(Game comp)
	{
		gameP=comp;
		
		reset();
	}
	//�߼�����
	public void update()
	{
		//��ͷ�ı�
		int direction=gameP.getDirection();
		switch(direction)
		{
		case Game.SOUTH:
			y+=speed; break;
		case Game.NORTH:
			y-=speed;break;
		case Game.EAST:
			x+=speed;break;
		case Game.WEST:
			x-=speed;break;
		}
		head=(head+1)%body.length;
		tail=(head+body.length-length+1)%body.length;
		body[head]=new Point(x,y);
		
	}
	//������Ⱦ
	public void draw(Graphics g)
	{
		//Graphics2D g2=(Graphics2D)g;
		//������ͷ
		
		/*��ʱ��ͷ������һ��*/
		//TextureManager.getInstance().draw("snake",new Rect(50,0,size,size),new Rect(x,y,size,size),g);
		//����
		//��β����ʱ������һ��ģ����Ϊ���
		/*int i;
		for(i=0;i<this.length;i++)
		{
			TextureManager.getInstance().draw("snake",new Rect(50,0,size,size),new Rect(body[i].x,body[i].y,size,size),g);
		}*/
		//������
		if(this.length>1)
		{
			int i=tail;
			while(i!=head)
			{
				TextureManager.getInstance().draw("snake",new Rect(50,0,size,size),new Rect(body[i].x,body[i].y,size,size),g);
				i=(i+1)%body.length;
			}
		}
		//��ͷ
		TextureManager.getInstance().draw("snake",new Rect(50,0,size,size),new Rect(body[head].x,body[head].y,size,size),g);
	}
	//��ֵ�ߵ�����
	public void reset()
	{
		//��
		//����
		length=1;
		head=-1;
		tail=-1;
		//�ٶ�
		speed=50;
		//��ͷ����
		x=400;
		y=300;
		size=50;
		//���·���ռ�
		body=new Point[MAXLENGTH];
	}
}
