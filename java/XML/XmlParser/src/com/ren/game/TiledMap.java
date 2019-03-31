package com.ren.game;
import java.awt.Point;
import java.io.*;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Vector;

import org.jdom2.Document;
import org.jdom2.Element;
import org.jdom2.JDOMException;
import org.jdom2.input.SAXBuilder;
public class TiledMap
{
	//存储该tiled的图片集
	java.util.Vector<Tileset> tilesets;
	//总绘画层 仅负责按照顺序绘画
	private Vector<Layer> layers;
	//单纯绘图层
	private Vector<TiledLayer> tiledLayers;
	//碰撞层
	Vector<ColliableLayer> colliableLayers;
	//object
	Vector<ObjectLayer> objectLayers;
	//保存要加载的资源的name和id
	Map<String,String> sourceMap;
	//主角
	Player player=null;
	//地图大小
	private int LEVEL_WIDTH;
	private int LEVEL_HEIGHT;
	public TiledMap(String path)
	{
		layers=new Vector<Layer>();
		
		tilesets=new Vector<Tileset>();
		
		tiledLayers=new Vector<TiledLayer>();
		colliableLayers=new Vector<ColliableLayer>();
		objectLayers=new Vector<ObjectLayer>();
		sourceMap=new HashMap<String,String>();
		//获得xml解析器
		SAXBuilder builder = new SAXBuilder();
		//文件
		InputStream in=TiledMap.class.getResourceAsStream(path);
		
		Document document;
		try 
		{
			document = builder.build(in);
			//root
			Element root=document.getRootElement();
			//读取卷轴地图 宽高度
			LEVEL_WIDTH=Integer.parseInt(root.getAttributeValue("width"))
					*Integer.parseInt(root.getAttributeValue("tilewidth"));
			LEVEL_HEIGHT=Integer.parseInt(root.getAttributeValue("height"))
					*Integer.parseInt(root.getAttributeValue("tileheight"));
			//设置camera
			Camera.getInstance().setRect(new Rect(0,0,LEVEL_WIDTH,LEVEL_HEIGHT));
			//获得子元素集
			List<Element> list=root.getChildren();
			//遍历子元素集
			for(Element child:list)
			{
				if(child.getName().equals("tileset"))
					parseTilesets(child);
				if(child.getName().equals("layer"))
					parseLayers(child);
				if(child.getName().equals("objectgroup"))
					parseObjects(child);
			}
			player.setColliableLayers(colliableLayers);
			System.out.println(path+"load success!!!");
		} catch (JDOMException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	//统一加载资源
	public void loadSources(String path)
	{
		for (Entry<String, String> entry : sourceMap.entrySet())
		{
			String id=entry.getKey();
			String name=entry.getValue();
	
			TextureManager.getInstance().load(path+name, id);
		}
	}
	//解析图块
	public void parseTilesets(Element tilesetRoot)
	{
		int firstgid;
		String name="";
		String id;
		int tileWidth,tileHeight,spacing,margin;
		int numColumns=0;
		
		firstgid=Integer.parseInt(tilesetRoot.getAttributeValue("firstgid"));
		//获得所有子元素
		List<Element> parent=tilesetRoot.getChildren();
		for(Element child:parent)
		{
			name=child.getAttributeValue("source");
			//获取图片宽度 然后获得个数
			numColumns=Integer.parseInt(child.getAttributeValue("width"));
		}
		id=tilesetRoot.getAttributeValue("name");
		tileWidth=Integer.parseInt(tilesetRoot.getAttributeValue("tilewidth"));
		tileHeight=Integer.parseInt(tilesetRoot.getAttributeValue("tileheight"));
		//spacing 和margin可能会没有
		try
		{
			spacing=Integer.parseInt(tilesetRoot.getAttributeValue("spacing"));
		}
		catch(NumberFormatException ex)
		{
			spacing=0;
		}
		try
		{
			margin=Integer.parseInt(tilesetRoot.getAttributeValue("margin"));
		}
		catch(NumberFormatException ex)
		{
			margin=0;
		}
		numColumns=numColumns/(tileWidth+spacing);
		tilesets.add(new Tileset(firstgid,name,id,tileWidth,tileHeight,spacing,margin,numColumns));
		//存入map
		sourceMap.put(id,name);
	}
	//解析数据 layer
	public void parseLayers(Element layerRoot)
	{
		//图块宽 高度个数
		int width,height;
		width=Integer.parseInt(layerRoot.getAttributeValue("width"));
		height=Integer.parseInt(layerRoot.getAttributeValue("height"));
		//
		boolean isColliable=false;
		//获得所有子元素
		List<Element> parent=layerRoot.getChildren();
		for(Element child:parent)
		{
			//properties
			if(child.getName().equals("properties"))
			{
				isColliable=true;
			}
			//data
			if(child.getName().equals("data"))
			{
				String text=child.getText().trim();
				//base64 解码
				byte[] decode=Base64Utils.getFromBASE64(text);//com.ren.game.Base64.decode(text);
				//zlib解压缩
				byte[] unzip=com.ren.game.ZlibUtils.uncompress(decode);
				//作为输入流
				DataInputStream in=new DataInputStream(new ByteArrayInputStream(unzip));
				//保存数据
				int[][] data=new int[height][];
				for(int i=0;i<height;i++)
				{
					data[i]=new int[width];
					for(int j=0;j<width;j++)
					{
						try 
						{
							 //暂时保存数据
							 int[] a=new int[4];
							 a[0]=in.readByte();
							 a[1]=in.readByte();
							 a[2]=in.readByte();
							 a[3]=in.readByte();
							for(int k=0;k<a.length;k++)
							{
								if(a[k]<0)
									a[k]=256+a[k];
							}
							data[i][j]=a[0]+a[1]*256;
						} catch (IOException e) 
						{
							e.printStackTrace();
						}
					}
				}
				TiledLayer layer;
				if(isColliable)
				{
					layer=new ColliableLayer(data,tilesets,LEVEL_WIDTH,LEVEL_HEIGHT);
					//isColliable=false;
					colliableLayers.add((ColliableLayer)layer);
				}
				else
				{
					layer=new TiledLayer(data,tilesets,LEVEL_WIDTH,LEVEL_HEIGHT);
					tiledLayers.add((TiledLayer)layer);
				}
				layers.add(layer);
			}
		}//end for
	}
	public void parseObjects(Element layerRoot)
	{
		ObjectLayer objectLayer;
		Vector<GameObject> gameObjects=new Vector<GameObject>();
		List<Element> parent=layerRoot.getChildren();
		//解析所有 object
		for(Element child:parent)
		{
			Point position=new Point();
			String type;
			String id="";
			String image="";
			
			type=child.getAttributeValue("type");
			position.x=Integer.parseInt(child.getAttributeValue("x"));
			position.y=Integer.parseInt(child.getAttributeValue("y"));
			//读取附加 properties
			Element properties=child.getChild("properties");
			if(properties==null)
				System.out.println("error"+position.x+" "+position.y);
			List<Element> list=properties.getChildren();
			
			for(Element property:list)
			{
				if(property.getAttributeValue("name").equals("id"))
					id=property.getAttributeValue("value");
				else if(property.getAttributeValue("name").equals("image"))
					image=property.getAttributeValue("value");
			}
			//新建object
			GameObject entity=null;
			//主角
			if(type.equals("Player"))
			{
				entity=new Player(position.x,position.y);
				player=(Player)entity;
				player.setType("Player");
			}
			gameObjects.add(entity);
			//加载到资源成员
			sourceMap.put(id,image);
		}
		objectLayer=new ObjectLayer(gameObjects);
		objectLayers.add(objectLayer);
		layers.add(objectLayer);
	}
	public void update()
	{
		for(int i=0;i<layers.size();i++)
		{
			layers.get(i).update();
		}
	}
	public void draw(java.awt.Graphics g)
	{
		for(int i=0;layers!=null&&i<layers.size();i++)
			layers.get(i).draw(g);
	}
	
	public String toString()
	{
		StringBuilder builder=new StringBuilder();
		builder.append("图块集\n");
		for(int i=0;i<tilesets.size();i++)
			builder.append(tilesets.get(i).toString());
		builder.append("地图信息\n");
		for(int i=0;i<layers.size();i++)
		{
			builder.append(layers.get(i).toString());
		}
		return builder.toString();
	}
}
