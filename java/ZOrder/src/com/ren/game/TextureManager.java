package com.ren.game;

import java.io.FileNotFoundException;
import java.io.IOException;

/*单例类，目前不保证多线程安全*/
/*图片类*/
public class TextureManager 
{
	private static TextureManager gInstance=null;
	private java.util.Map<String,java.awt.image.BufferedImage> textureMap;
	private TextureManager()
	{
		textureMap=new java.util.HashMap<String,java.awt.image.BufferedImage>();
	}
	public static TextureManager getInstance()
	{
		if(gInstance==null)
			{
				gInstance=new TextureManager();
			}
		return gInstance;
	}
	@SuppressWarnings("restriction")
	public boolean load(String path,String id)
	{
		//在路径下搜索图片，目前不支持gif
		java.io.InputStream file=getClass().getResourceAsStream(path);
		try 
		{
			java.awt.image.BufferedImage image=javax.imageio.ImageIO.read(file);
			textureMap.put(id, image);
		} catch (IOException e) 
		{
			System.out.println(id+"加载失败");//e.printStackTrace();
		}
		return false;
	}
	/*并不是为了实现双缓冲，只是为了便于管理*/
	public void draw(String id,int x,int y,java.awt.Graphics g)
	{
		java.awt.image.BufferedImage image=textureMap.get(id);
		if(image!=null)
			g.drawImage(image,x,y,image.getWidth(),image.getHeight(),null);
	}
	//增加容错性
	public void draw(String id,Rect srcRect,Rect destRect,java.awt.Graphics g)
	{
		java.awt.image.BufferedImage image=textureMap.get(id);
		java.awt.image.BufferedImage subImage=image.getSubimage(srcRect.x,srcRect.y,srcRect.w,srcRect.h);
		if(image!=null)
			g.drawImage(subImage,destRect.x,destRect.y,destRect.w,destRect.h,null);
	}
	public void draw(String id,
			int dx1,int dy1,int dx2,int dy2,
			int sx1,int sy1,int sx2,int sy2,
			java.awt.Graphics g)
	{
		java.awt.image.BufferedImage image=textureMap.get(id);
		if(image!=null)
			g.drawImage(image,dx1,dy1,dx2,dy2,sx1,sy1,sx2,sy2,null);
	}
	public java.awt.Dimension getDimensionById(String id)
	{
		java.awt.image.BufferedImage image=textureMap.get(id);
		
		return (image==null?null:(new java.awt.Dimension(image.getWidth(),image.getHeight())));
	}
}
