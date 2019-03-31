package com.ren.game;

import java.awt.Point;

//精灵
public abstract class GameObject implements Colliable
{
	//坐标
	protected Point position;
	//移动速度
	protected Point velocity;
	//加速度
	protected Point acceleration;
	//类型
	protected String type;
	//高度
	protected int width;
	protected int height;
	
	public abstract void update();
	public abstract void draw(java.awt.Graphics g);
	public Point getPosition()
	{
		return position;
	}
	public void setPosition(int x,int y)
	{
		setPosition(new Point(x,y));
	}
	public void setPosition(Point p)
	{
		this.position=p;
	}
	public int getX()
	{
		return this.position.x;
	}
	public int getY()
	{
		return this.position.y;
	}
	public int getWidth()
	{
		return this.width;
	}
	public int getHeight()
	{
		return this.height;
	}
	public void setVelocity(int x,int y)
	{
		setVelocity(new Point(x,y));
	}
	public void setVelocity(Point p)
	{
		this.velocity=p;
	}
	public Point getVelocity()
	{
		return this.velocity;
	}
	public void setAcceleration(int x,int y)
	{
		setAcceleration(new Point(x,y));
	}
	public void setAcceleration(Point p)
	{
		this.acceleration=p;
	}
	public void setType(String ty)
	{
		this.type=ty;
	}
	public String getType()
	{
		return type;
	}
}
