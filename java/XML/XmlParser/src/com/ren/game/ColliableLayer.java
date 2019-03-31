package com.ren.game;

import java.util.Vector;

public class ColliableLayer extends TiledLayer implements Colliable
{

	public ColliableLayer(int[][] data, Vector<Tileset> tilesets, int width,int height) 
	{
		super(data, tilesets, width, height);
	}
	@Override
	public void collision() 
	{
	}

}
