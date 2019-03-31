package com.ren.game;
/*��Animation�����ƣ����ֲ�ͬ*/
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
