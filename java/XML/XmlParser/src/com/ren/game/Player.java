package com.ren.game;

import java.awt.Graphics;
import java.awt.Point;
import java.util.Vector;

public class Player extends GameObject
{
	//����ͼ
	private Animations rightAnim;
	private Animations leftAnim;
	private Animations upAnim;
	private Animations downAnim;
	//��ǰ״̬
	private Animations currentAnim=null;
	private Vector<ColliableLayer> colliableLayers=null;
	//�ٶ�
	private Point speed=new Point(1,1);
	public Player()
	{
		this(0,0);
	}
	public Player(int x,int y)
	{
		this.position=new Point(x,y);
		this.velocity=new Point(0,0);
		this.acceleration=new Point(0,0);
		
		initlize();
	}
	@Override
	public void draw(Graphics g)
	{
		currentAnim.draw(position.x-Camera.getInstance().getPosition().x,
				position.y-Camera.getInstance().getPosition().y,36,36,g);
	}
	@Override
	public void collision() 
	{
	}
	//��ʼ��
	public void initlize()
	{
		downAnim=new Animations(70,3,true);
		upAnim=new Animations(70,3,true);
		leftAnim=new Animations(70,3,true);
		rightAnim=new Animations(70,3,true);
		for(int i=0;i<4;i++)
		{
			downAnim.add(new Animation("player",36*i,0,36,36));
			upAnim.add(new Animation("player",36*i,36*3,36,36));
			leftAnim.add(new Animation("player",36*i,36,36,36));
			rightAnim.add(new Animation("player",36*i,72,36,36));
		}
		//Ĭ�϶���
		currentAnim=downAnim;
		width=36;
		height=36;
		//����camera
		Camera.getInstance().setTarget(position);
	}
	@Override
	public void update()
	{
		handleEvent();
		//����
		if(currentAnim!=null)
			currentAnim.updateImage();
		//������ײ���ı�λ��
		handleMovement(velocity);
		
	}
	private void handleEvent()
	{
		//��������
		boolean up=InputHandler.getInstance().isKeyDown(InputHandler.KEY_UP);
		boolean down=InputHandler.getInstance().isKeyDown(InputHandler.KEY_DOWN);
		boolean left=InputHandler.getInstance().isKeyDown(InputHandler.KEY_LEFT);
		boolean right=InputHandler.getInstance().isKeyDown(InputHandler.KEY_RIGHT);
		//����
		if(down)
		{
			currentAnim=downAnim;
			this.velocity.y=speed.y;
			downAnim.resume();
		}//��
		else if(up)
		{
			currentAnim=upAnim;
			this.velocity.y=-speed.y;
			upAnim.resume();
		}
		else
		{
			this.velocity.y=0;
			downAnim.stop();
			upAnim.stop();
		}
		//��
		if(left)
		{
			currentAnim=leftAnim;
			this.velocity.x=-speed.x;
			leftAnim.resume();
		}
		//��
		else if(right)
		{
			currentAnim=rightAnim;
			this.velocity.x=speed.x;
			rightAnim.resume();
		}
		else
		{
			this.velocity.x=0;
			leftAnim.stop();
			rightAnim.stop();
		}
	}
	public void setColliableLayers(Vector<ColliableLayer> layers)
	{
		this.colliableLayers=layers;
	}
	private void handleMovement(Point velocity)
	{
		Point newPos = new Point(position);
	    // add velocity to the x position
	    newPos.x = position.x + velocity.x;
	    newPos.y = position.y + velocity.y; 
	    // check if the new x position would collide with a tile
	    if(!checkCollideTile(newPos))
	    {
	        // no collision, add to the actual x position
	        position.x = newPos.x;
	        position.y = newPos.y;
	    }
	    else
	    {
	       velocity.x = 0;
	       velocity.y = 0;
	    }
	}
	private boolean checkCollideTile(Point newPos)
	{
        for(int k=0;k<colliableLayers.size();k++)
        {
            ColliableLayer pTileLayer = colliableLayers.get(k);
            int[][] tiles = pTileLayer.getTileIDs();
            
            int tileid=tiles[(newPos.y+this.height/2)/pTileLayer.getTileSize()][(newPos.x+this.width/2)/pTileLayer.getTileSize()];
            tileid=tileid==0?0:tileid-1;
            if(tileid!=0)
            	return true;
        }
        return false;
	}
	public String toString()
	{
		return type+"\n";
	}
}
