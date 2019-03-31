package com.ren.game;

import java.awt.Graphics;
import java.awt.image.BufferedImage;

public class DialogManager 
{
	private static DialogManager gInstance=null;
	//左 立绘图
	private String leftId;
	//右立绘图
	private String rightId;
	//对话
	private String[] chatStr;
	//对话背景
	private String chatBg;
	//记录对话语句
	private int currentDialog;
	private DialogManager()
	{
	}
	public static DialogManager getInstance()
	{
		if(gInstance==null)
			gInstance=new DialogManager();
		return gInstance;
	}
	public void draw(Graphics g)
	{
		if(chatStr!=null&&currentDialog<chatStr.length)
		{
			//绘制左右
			BufferedImage leftImage=TextureManager.getInstance().getBufferdImage(leftId);
			BufferedImage rightImage=TextureManager.getInstance().getBufferdImage(rightId);
			BufferedImage chatImage=TextureManager.getInstance().getBufferdImage(chatBg);
			
			if(leftImage!=null)
			{
				int height=leftImage.getHeight();
				TextureManager.getInstance().draw(leftId,0,Game.getInstance().SCREEN_HEIGHT-height,g);
			}
			if(rightImage!=null)
			{
				int width=rightImage.getWidth();
				int height=rightImage.getHeight();
				TextureManager.getInstance().draw(rightId,Game.getInstance().SCREEN_WIDTH-width,Game.getInstance().SCREEN_HEIGHT-height,g);
			}
			if(chatBg!=null)
			{
				int height=chatImage.getHeight();
				TextureManager.getInstance().draw(chatBg,0,Game.getInstance().SCREEN_HEIGHT-height,g);
			}
			g.drawString(chatStr[currentDialog],0,300);
		}
	}
	public boolean update()
	{
		if(chatStr!=null&&currentDialog<chatStr.length)
		{
			boolean isClicked=InputHandler.getInstance().isKeyDown(InputHandler.KEY_SPACE);
			if(isClicked)
				currentDialog++;
			return true;
		}
		else
		{
			leftId=null;
			rightId=null;
			chatStr=null;
			chatBg=null;
			currentDialog=0;
		}
		return false;
	}
	//设置对话
	public void setDialog(String leftId,String rightId,String bg,String str[])
	{
		this.leftId=leftId;
		this.rightId=rightId;
		this.chatBg=bg;
		this.chatStr=str;
		this.currentDialog=0;
	}
}
