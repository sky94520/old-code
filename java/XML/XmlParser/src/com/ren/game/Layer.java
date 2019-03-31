package com.ren.game;

import java.awt.Graphics;
import java.awt.Point;

public abstract class Layer 
{
	protected Point position;
	public abstract void update();
	public abstract void draw(Graphics g);
	public Point getPosition()
	{
		return this.position;
	}
	public void setPosition(Point p)
	{
		position=p;
	}
}
