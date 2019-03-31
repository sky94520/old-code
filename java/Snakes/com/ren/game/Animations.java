package com.ren.game;

import java.awt.event.ActionEvent;

public class Animations
{
	//����
	private int  duration=0;
	//��֡��
	private int frame=0;
	//��ǰ֡��
	private int currentFrame=0;
	//��ʱ��
	java.util.Timer timer;
	MyTimerTask timerTask;
	
	private java.util.Vector<Animation> animationVec;
	public Animations(int d)
	{
		this.duration=d;
		animationVec=new java.util.Vector<Animation>();
		timer=new java.util.Timer();
		timerTask=new MyTimerTask();
		timer.scheduleAtFixedRate(timerTask,10, this.duration);
		
	}
	public void add(Animation animation)
	{
		if(animation==null)
			throw new java.lang.NullPointerException("animation==null");
		this.animationVec.add(animation);
		this.frame++;
	}
	public void draw(Rect destRect,java.awt.Graphics g)
	{
		Animation anim=this.animationVec.get(currentFrame);
		anim.draw(destRect, g);
	}
	public void draw(int x,int y,int w,int h,java.awt.Graphics g)
	{
		Animation anim=this.animationVec.get(currentFrame);
		anim.draw(new Rect(x,y,w,h), g);
	}
	//����ͼƬ��� �߶� Ĭ��ͼƬ�Ĵ�С�����
	public int getWidth()
	{
		if(animationVec.get(0)!=null)
			return animationVec.get(0).getWidth();
		return 0;
	}
	public int getHeight()
	{
		if(animationVec.get(0)!=null)
			return animationVec.get(0).getHeight();
		return 0;
	}
	//�ڲ���
	class MyTimerTask extends java.util.TimerTask
	{
		public void run()
		{
			currentFrame=currentFrame>=frame-1?0:currentFrame+1;
			
			//System.out.println(currentFrame);
		}
	}
}
