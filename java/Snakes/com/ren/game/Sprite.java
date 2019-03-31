package com.ren.game;
/*和Animation、类似，但又不同*/
public class Sprite extends Animation
{
	public Sprite(String id, int w, int h) 
	{
		super(id, w, h);
	}
	public Sprite(String id,int x,int y, int w, int h) 
	{
		super(id,x,y, w, h);
	}
	public void draw(Rect destRect,java.awt.Graphics g)
	{
		TextureManager.getInstance().draw(id,new Rect(x,y,width,height),destRect,g);
	}
}
