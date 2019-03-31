package com.ren.game;

import java.awt.Point;
import java.util.Vector;

public class TiledLayer extends Layer
{
	//图块个数
	protected int numColumns=0;
	protected int numRows=0;
	//瓦片大小
	protected int tileSize;
	//图块数据
	protected int[][] data;
	//图块集 引用父类
	protected Vector<Tileset> tilesets;
	
	public TiledLayer(int[][] data,Vector<Tileset> tilesets,int width,int height)
	{
		this.data=data;
		this.tilesets=tilesets;
		tileSize=this.tilesets.get(0).tileWidth;
		this.numColumns=width/tileSize;
		this.numRows=height/tileSize;
	
		position=new Point();
	}
	public void draw(java.awt.Graphics g)
	{
		//暂时为0.作扩展使用
		int x=Math.abs(position.x)/tileSize;
		int y=Math.abs(position.y)/tileSize;
		int x2=Math.abs(position.x)%tileSize;
		int y2=Math.abs(position.y)%tileSize;
		
		for(int i=0;i<numRows;i++)
			for(int j=0;j<numColumns;j++)
			{
				int id=0;
				try{
					id=data[i+y][j+x];
				}catch(java.lang.ArrayIndexOutOfBoundsException e)
				{
					break;
				}
				if(id==0)
					continue;
				//if outside the viewable area then skip the tile
				if((j*tileSize -x2)-Camera.getInstance().getPosition().x<-tileSize||
						(j*tileSize -x2)-Camera.getInstance().getPosition().x>Game.getInstance().SCREEN_WIDTH)
					continue;
				Tileset tileset=getTilesetByID(id);
				id--;
				TextureManager.getInstance().drawTile(tileset.id, tileset.margin, tileset.spacing,
						(j*tileSize-x2)-Camera.getInstance().getPosition().x,
						(i*tileSize-y2) , 
						tileset.tileWidth, tileset.tileHeight,
						(id-(tileset.firstgid-1))/tileset.numColumns,
						(id-(tileset.firstgid-1))%tileset.numColumns, g);
			}
	}
	//遍历寄主的Tileset，找到并返回
	private Tileset getTilesetByID(int tileID)
	{
		for(int i=0;i<tilesets.size();i++)
		{
			if(i+1<=tilesets.size()-1)
			{
				if(tileID>=tilesets.get(i).firstgid&&tileID<tilesets.get(i+1).firstgid)
					return tilesets.get(i);
			}
			else
				return tilesets.get(i);
		}
		return null;
	}
	public int[][] getTileIDs()
	{
		return this.data;
	}
	public int getTileSize()
	{
		return this.tileSize;
	}
	public boolean equals(Object obj)
	{
		if(this==obj)
			return true;
		if(obj instanceof TiledLayer)
		{
			TiledLayer layer=(TiledLayer)obj;
			return (this.numColumns==layer.numColumns&&
					this.numRows==layer.numRows&&
					this.data.equals(layer.data));
		}
		return false;
	}
	public String toString()
	{
		StringBuilder builder=new StringBuilder();
		builder.append("numColumns:"+this.numColumns+"\n");
		builder.append("numRows:"+this.numRows+"\n");
		
		for(int i=0;i<data.length;i++)
		{
			for(int j=0;j<data[i].length;j++)
				builder.append(data[i][j]+" ");
			builder.append("\n");
		}
		return builder.toString();
	}
	@Override
	public void update()
	{
	}
}
