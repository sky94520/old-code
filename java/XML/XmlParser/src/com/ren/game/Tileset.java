package com.ren.game;
//ͼ��
public class Tileset 
{
	public int firstgid; 
	//ͼƬid ��TextureManager��id
	public String id;
	//ͼƬȫ��
	public String name;
	public int tileWidth;
	public int tileHeight;
	//�߾�
	public int spacing;
	//���
	public int margin;
	//ͼƬ��� СͼƬ����
	public int numColumns;
	
	public Tileset(int firstgid,String name,String id,int tileWidth,int tileHeight,int spacing,int margin,int numColumns)
	{
		this.firstgid=firstgid;
		this.name=name;
		this.id=id;
		this.tileWidth=tileWidth;
		this.tileHeight=tileHeight;
		this.spacing=spacing;
		this.margin=margin;
		this.numColumns=numColumns;
	}
	public String toString()
	{
		StringBuilder builder=new StringBuilder();
		builder.append("firstgid:"+firstgid);
		builder.append(" name:"+name);
		builder.append(" id:"+id);
		builder.append(" tilewidth:"+tileWidth);
		builder.append(" tileheight:"+tileHeight);
		builder.append(" spacing:"+spacing);
		builder.append(" margin:"+margin);
		builder.append(" numColumns:"+numColumns);
		builder.append("\n");
		
		return builder.toString();
	}
}
