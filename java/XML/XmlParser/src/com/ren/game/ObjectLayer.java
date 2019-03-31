package com.ren.game;

import java.awt.Graphics;
import java.util.Vector;

public class ObjectLayer extends Layer
{
	private Vector<GameObject> gameObjects;
	public ObjectLayer(Vector<GameObject> gameObjects)
	{
		this.gameObjects=gameObjects;
	}
	@Override
	public void update()
	{
		for(int i=0;i<gameObjects.size();i++)
			gameObjects.get(i).update();
	}
	@Override
	public void draw(Graphics g) 
	{
		for(int i=0;i<gameObjects.size();i++)
			gameObjects.get(i).draw(g);
	}
	public boolean equals(Object obj)
	{
		if(this==obj)
			return true;
		if(obj instanceof ObjectLayer)
		{
			ObjectLayer layer=(ObjectLayer)obj;
			return this.gameObjects.equals(layer.gameObjects);
		}
		return false;
	}
	public String toString()
	{
		StringBuilder builder=new StringBuilder();
		for(int i=0;i<gameObjects.size();i++)
			builder.append(gameObjects.get(i)+"\n");
		return builder.toString();
	}
}
