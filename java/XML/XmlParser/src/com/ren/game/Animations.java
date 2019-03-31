package com.ren.game;
/*ms*/
public class Animations
{
    //����ÿһ֡������
    private java.util.Vector<Animation> animationVec;
    //��֡��
    private int numImages;
    private boolean ticksStopped;
    //�Ƿ��ظ�
    private boolean isRepeating;
    //���¾��鶯������ʱ��
    private int animTime;
    private int animSpeed;
    //������ʱ��
    private int animTotalTime;
    //����ͼ���л�ʱ��
    private int showTime;
    //�������ڵ�ǰ֡��
    private int currentFrame;


    public Animations(int animSpeed,int animaTotalTime,boolean repeat) 
    {
        this.animSpeed=animSpeed;
        this.isRepeating=repeat;
        this.animTotalTime=animaTotalTime;
        
        this.numImages=0;
        this.animTime=0;
        this.currentFrame = 0;
        this.ticksStopped = true;
        this.animationVec=new java.util.Vector<Animation>();
    }
    public void add(Animation animation) throws java.lang.NullPointerException
	{
		if(animation==null)
			throw new java.lang.NullPointerException("animation==null");
		this.animationVec.add(animation);
		this.numImages++;
	}
    public void updateImage()
    {
    	if (!ticksStopped&&numImages!=0) 
    	{
    		// update total animation time, modulo the animation sequence duration
    		animTime = (animTime + animSpeed) % (1000*animTotalTime);
    		showTime = (int)(1000*animTotalTime / numImages);
    		currentFrame = (int)(animTime / showTime);   // in range 0 to num-1
    		if ((currentFrame == numImages-1) && (!isRepeating))   // at end of sequence
    			ticksStopped = true;   // stop at this image
    		//System.out.println(currentFrame+" "+numImages);
    	}
    	//System.out.println(currentFrame+" "+numImages);
    }
  public void stop()
  {
	  if(numImages!=0)
	  {
		  currentFrame=0;
		  ticksStopped = true;
	  }
	  
  }
  public boolean isStopped()
  {
	  return ticksStopped;
  }
  public void resume()
  {
    if(numImages != 0)
      ticksStopped = false;
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
}

