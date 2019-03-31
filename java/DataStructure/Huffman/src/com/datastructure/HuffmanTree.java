package com.datastructure;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.Iterator;

public class HuffmanTree
{
	TriElement[] huftree;
	private String str[];
	public HuffmanTree(String[] str,int[] weight)
	{
		this.str=str;
		//n个叶子
		int n=weight.length;
		//总共2n-1个节点
		huftree=new TriElement[2*n-1];
		//构造无父母的叶子节点
		for(int i=0;i<n;i++)
			huftree[i]=new TriElement(weight[i]);
		//构造n-1的二度节点
		for(int i=n;i<2*n-1;i++)
		{
			int min1,min2;
			min1=min2=Integer.MAX_VALUE;
			//下标
			int x1=-1,x2=-1;
			for(int j=0;j<i;j++)
				if(huftree[j].parent==-1)
					if(huftree[j].data<min1)
					{
						min2=min1;
						x2=x1;
						min1=huftree[j].data;
						x1=j;
					}
					else if(this.huftree[j].data<min2)
					{
						min2=huftree[j].data;
						x2=j;
					}
			huftree[x1].parent=i;
			huftree[x2].parent=i;
			huftree[i]=new TriElement(min1+min2,-1,x1,x2);
		}
	}
	//根据s在this.str的位置来求得编码值
	public String getCode(String s)
	{
		int i=-1;
		//get i
		for(i=0;i<this.str.length;i++)
			if(str[i].equals(s))
				break;
		int n=8;
		char[] hufcode=new char[n];
		int child=i;
		int parent=this.huftree[child].parent;
		for(i=n-1;parent!=-1;i--)
		{
			hufcode[i]=(this.huftree[parent].left==child)?'0':'1';
			child=parent;
			parent=this.huftree[child].parent;
		}
		return new String(hufcode,i+1,n-1-i);
	}
	//压缩
	public static boolean encode(File file)
	{
		//二进制保存文件
		FileOutputStream binaryOutput;
		//赫夫曼树保存文件
		OutputStreamWriter passwordOutput;
		//打开的文本
		String text;
		//键值对
		String[] keys;
		int[] values;
		//全局变量
		byte gByte=0;
		int gBit=0;
		if(!file.exists())
		{
			System.out.println(file.getAbsolutePath()+"文件不存在，请重新输入");
			return false;
		}
		String fileName=file.getName().substring(0,file.getName().length()-3);
		File binaryFile=new File(fileName+"binary");
		File passwordFile=new File(fileName+"password");
		//打开输入流
		try 
		{
			//打开输出流
			binaryFile.createNewFile();
			passwordFile.createNewFile();
			//打开输出流
			binaryOutput=new FileOutputStream(binaryFile);
			passwordOutput=new OutputStreamWriter(new FileOutputStream(passwordFile));
			
			BufferedReader reader=new BufferedReader(new InputStreamReader(new FileInputStream(file)));
			//读取文本 字符串
			StringBuilder builder=new StringBuilder();
			String line;
			while((line=reader.readLine())!=null)
				builder.append(line);
			//文本读取成功
			text=builder.toString();
			System.out.println(text);
			System.out.println("文本读取成功！");
			reader.close();
			//分析数据  处理权值
			HashMap<String,Integer> hashMap=new HashMap<String,Integer>();
			//处理频率
			for(int i=0;i<text.length();i++)
			{
				Integer time=hashMap.get(""+text.charAt(i));
				
				hashMap.put(""+text.charAt(i), time==null?1:time+1);
			}
			Iterator<KeyValue<String,Integer>> iter=hashMap.iterator();
			System.out.println("size:"+hashMap.size());
			
			keys=new String[hashMap.size()];
			values=new int[hashMap.size()];
			for(int i=0;i<hashMap.size()&&iter.hasNext();i++)
			{
				KeyValue<String,Integer> keyValue = iter.next();
				keys[i]=new String(keyValue.key());
				values[i]=new Integer(keyValue.value());
				System.out.println("key:"+keyValue.key()+" value:"+keyValue.value());
			}
			//新建赫夫曼树
			HuffmanTree huffmanTree=new HuffmanTree(keys,values);
			for(int i=0;i<text.length();i++)
			{
				//获得编码
				int j=0;
				//默认8 bit
				byte bytes=0;
				//默认位数
				int bits=0;
				
				for(;j<keys.length;j++)
					if(keys[j].equals(""+text.charAt(i)))
						break;
				int child=j;
				
				int parent=huffmanTree.huftree[child].parent;
				for(j=8-1;parent!=-1;j--)
				{
					bytes|=((huffmanTree.huftree[parent].left==child)?0:1<<(7-j));
					child=parent;
					parent=huffmanTree.huftree[child].parent;
					//
					bits++;
				}
				System.out.println("bytes:"+bytes+" bits:"+bits);
				if(gBit+bits<8)
				{
					gByte=(byte) (gByte<<bits|bytes);
					gBit+=bits;
				}
				else
				{
					gByte=(byte) (gByte<<(8-gBit)|bytes>>>(bits-(8-gBit)));
					//访问数据
					//System.out.println("byte:"+gByte);
					binaryOutput.write(gByte);
					gByte=bytes;
					gBit=bits-(8-gBit);
				}
			}//end for
			//System.out.println("gByte:"+gByte+" gBit:"+gBit);
			binaryOutput.write((byte)gBit);
			binaryOutput.write(gByte);
			binaryOutput.close();
			//写入键值对
			for(int j=0;j<keys.length;j++)
			{	
				passwordOutput.write(keys[j]);
				passwordOutput.write(values[j]);
			}
			passwordOutput.close();
		}
		catch(IOException e)
		{
		}
		return true;
	}
	public static String decode(File binaryFile,File passwordFile) throws IOException
	{
		//键值对
		String[] keys;
		int[] values;
		if(!binaryFile.exists()||!passwordFile.exists())
		{
			throw new FileNotFoundException("file nout found");
		}
		FileInputStream input=new FileInputStream(binaryFile);
		//根据字节数来定义 String
		byte[] get=new byte[(int)binaryFile.length()];
		//读取
		input.read(get);
		input.close();
		String str="";
		for(int i=0;i<get.length-2;i++)
			str+=toBinaryString(get[i]);
		//解析剩下的位数
		if(get[get.length-2]!=0)
		{
			String str2=toBinaryString(get[get.length-1]);
			str2=str2.substring(str2.length()-get[get.length-2]);
		
			str+=str2;
		}
		//解析键值对，构造赫夫曼树
		InputStreamReader passwordReader=new InputStreamReader(new FileInputStream(passwordFile));
		int length=(int) (passwordFile.length()/2);
		keys=new String[length];
		values=new int[length];
		int ch;
		for(int i=0;i<length;i++)
		{
			try
			{
				ch=passwordReader.read();
				keys[i]=new String(""+(char)ch);
				ch=passwordReader.read();
				values[i]=ch;
				
			}catch(IOException e)
			{
				break;
			}
		}
		passwordReader.close();
		//建立赫夫曼树
		HuffmanTree huffmanTree=new HuffmanTree(keys,values);
		
		return huffmanTree.decode(str);
	}
	public static String toBinaryString(int i)
	{
		String temp=Integer.toBinaryString(i);
		if(temp.length()>8)
			return temp.substring(temp.length()-8);
		//不满8位，以0填充
		String str="";
		for(int j=0;j<8-temp.length();j++)
			str+="0";
		return str+temp;
	}
	public String encode(String text)
	{
		StringBuilder compressed=new StringBuilder();
		//压缩后的长度
		//int j=0;
		for(int i=0;i<text.length();i++)
		{
			compressed.append(getCode(""+text.charAt(i)));
		}
		return compressed.toString();
	}
	public String decode(String compressed)
	{
		String uncompressed="";
		int node=this.huftree.length-1;
		for(int i=0;i<compressed.length();i++)
		{
			if(compressed.charAt(i)=='0')
				node=huftree[node].left;
			else
				node=huftree[node].right;
			if(huftree[node].isLeaf())
			{
				uncompressed+=this.str[node];
				node=this.huftree.length-1;
			}
		}
		return uncompressed;
	}
	public String toString()
	{
		String s="树的节点数组：";
		for(int i=0;i<this.huftree.length;i++)
			s+=this.huftree[i].toString()+",";
		s+="\n赫夫曼树编码\n";
		for(int i=0;i<this.str.length;i++)
			s+=this.str[i]+":"+getCode(this.str[i]);
		return s;
	}
}
