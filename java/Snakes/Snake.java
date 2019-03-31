import java.awt.Point;
import java.awt.*;
import com.datastructure.*;

import com.ren.game.*;


public class Snake
{
	//蛇最大长度 default
	static final int MAXLENGTH=50;
	//蛇身体
	private  Point[] body;
	public int speed;
	//蛇头 蛇尾
	private int head;
	private int tail;
	
	public int length;
	//蛇头位置
	public int x;
	public int y;
	//蛇尺寸
	public int size;
	Game gameP;
	
	public Snake(Game comp)
	{
		gameP=comp;
		
		reset();
	}
	//逻辑更新
	public void update()
	{
		//蛇头改变
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
	//画面渲染
	public void draw(Graphics g)
	{
		//Graphics2D g2=(Graphics2D)g;
		//画出蛇头
		
		/*暂时蛇头与蛇身一样*/
		//TextureManager.getInstance().draw("snake",new Rect(50,0,size,size),new Rect(x,y,size,size),g);
		//蛇身
		//蛇尾巴暂时和蛇身一个模样，为简便
		/*int i;
		for(i=0;i<this.length;i++)
		{
			TextureManager.getInstance().draw("snake",new Rect(50,0,size,size),new Rect(body[i].x,body[i].y,size,size),g);
		}*/
		//画蛇身
		if(this.length>1)
		{
			int i=tail;
			while(i!=head)
			{
				TextureManager.getInstance().draw("snake",new Rect(50,0,size,size),new Rect(body[i].x,body[i].y,size,size),g);
				i=(i+1)%body.length;
			}
		}
		//蛇头
		TextureManager.getInstance().draw("snake",new Rect(50,0,size,size),new Rect(body[head].x,body[head].y,size,size),g);
	}
	//充值蛇的坐标
	public void reset()
	{
		//蛇
		//长度
		length=1;
		head=-1;
		tail=-1;
		//速度
		speed=50;
		//蛇头坐标
		x=400;
		y=300;
		size=50;
		//重新分配空间
		body=new Point[MAXLENGTH];
	}
}
