package com.ren.game;
/*不支持gif，*/
public class Animation 
{
	protected String id;
	protected int x,y;
	//默认w h为零时是图片的全部 以后修改
	protected int width,height;
	public Animation(String id,int w,int h)
	{
		this(id,0,0,w,h);
	}
	//src rect
	//在这里增加查询 id的图片是否导入，如果没导入，提示
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
