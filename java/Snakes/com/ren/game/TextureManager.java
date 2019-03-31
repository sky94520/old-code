package com.ren.game;

import java.io.FileNotFoundException;
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
		//��·��������ͼƬ��Ŀǰ��֧��gif
		java.io.InputStream file=getClass().getResourceAsStream(path);
		try 
		{
			java.awt.image.BufferedImage image=javax.imageio.ImageIO.read(file);
			textureMap.put(id, image);
		} catch (IOException e) 
		{
			e.printStackTrace();
		}
		return false;
	}
	/*������Ϊ��ʵ��˫���壬ֻ��Ϊ�˱��ڹ���*/
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
		java.awt.image.BufferedImage subImage=image.getSubimage(srcRect.x,srcRect.y,srcRect.w,srcRect.h);
		if(image!=null)
			g.drawImage(subImage,destRect.x,destRect.y,destRect.w,destRect.h,null);
	}
}
