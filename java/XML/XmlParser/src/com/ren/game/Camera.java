package com.ren.game;
import java.awt.Point;
public class Camera 
{
	private Point target;
	private Point position;
	private static Camera gInstance;
	private Rect rect=null;
	public static Camera getInstance()
	{
		if(gInstance==null)
			gInstance=new Camera();
		return gInstance;
	}
	private Camera()
	{
		position=new Point(0,0);
	}
	public void setRect(Rect rect)
	{
		this.rect=rect;
	}
	public Point getPosition()
	{
		if(target!=null)
		{
			Point pos=new Point(target.x-Game.getInstance().SCREEN_WIDTH/2,0);
			if(pos.x<0)
				pos.x=0;
			if(pos.x>rect.w-Game.getInstance().SCREEN_WIDTH)
				pos.x=rect.w-Game.getInstance().SCREEN_WIDTH;
			return pos;
		}
		return position;
	}
	public void setTarget(Point point)
	{
		target=point;
	}
}
