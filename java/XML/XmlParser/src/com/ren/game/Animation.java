package com.ren.game;
/*��֧��gif��*/
public class Animation 
{
	protected String id;
	protected int x,y;
	//Ĭ��w hΪ��ʱ��ͼƬ��ȫ�� �Ժ��޸�
	protected int width,height;
	public Animation(String id,int w,int h)
	{
		this(id,0,0,w,h);
	}
	//src rect
	//���������Ӳ�ѯ id��ͼƬ�Ƿ��룬���û���룬��ʾ
	public Animation(String id,int x,int y,int w,int h)
	{
		this.id=id;
		this.x=x;
		this.y=y;
		this.width=w;
		this.height=h;
	}
	public void draw(Rect destRect,java.awt.Graphics g)
	{
		TextureManager.getInstance().draw(id,new Rect(x,y,width,height),destRect,g);
	}
	public int getWidth()
	{
		return this.width;
	}
	public int getHeight()
	{
		return this.height;
	}
}
