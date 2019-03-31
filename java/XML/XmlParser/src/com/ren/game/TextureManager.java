package com.ren.game;

import java.awt.image.BufferedImage;
import java.io.IOException;

/*�����࣬Ŀǰ����֤���̰߳�ȫ*/
/*ͼƬ��*/
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
		//�鿴ͼ�����Ƿ���ڸ�id
		if(textureMap.containsKey(id))
		{
			System.out.println(id+"is existed!");
			return true;
		}
		//��·��������ͼƬ��Ŀǰ��֧��gif
		java.io.InputStream file=getClass().getResourceAsStream(path);
		try 
		{
			BufferedImage image=javax.imageio.ImageIO.read(file);
			textureMap.put(id, image);
			System.out.println("id:"+id+" image:"+path+" load success!!!");
		} catch (IOException e) 
		{
			e.printStackTrace();
		}
		return false;
	}
	/*������Ϊ��ʵ��˫���壬ֻ��Ϊ�˱��ڹ���*/
	//������(x,y)������id������ͼƬ
	public void draw(String id,int x,int y,java.awt.Graphics g)
	{
		java.awt.image.BufferedImage image=textureMap.get(id);
		if(image!=null)
			g.drawImage(image,x,y,image.getWidth(),image.getHeight(),null);
	}
	//�����ݴ���
	public void draw(String id,Rect srcRect,Rect destRect,java.awt.Graphics g)
	{
		java.awt.image.BufferedImage image=textureMap.get(id);
		if(image ==null)
		{
			throw new NullPointerException("id:"+id+" not existed!");
		}
		java.awt.image.BufferedImage subImage=image.getSubimage(srcRect.x,srcRect.y,srcRect.w,srcRect.h);
		if(subImage!=null)
			g.drawImage(subImage,destRect.x,destRect.y,destRect.w,destRect.h,null);
	}
	public void drawTile(String id,int margin,int spacing,int x,int y,int width,int height,int currentRow,int currentFrame,java.awt.Graphics g)
	{
		Rect srcRect=new Rect();
		Rect destRect=new Rect();
		srcRect.x=margin+(spacing+width)*currentFrame;
		srcRect.y=margin+(spacing+height)*currentRow;
		srcRect.w=destRect.w=width;
		srcRect.h=destRect.h=height;
		destRect.x=x;
		destRect.y=y;
		
		draw(id,srcRect,destRect,g);
	}
	public BufferedImage getBufferdImage(String id)
	{
		return textureMap.get(id);
	}
}
