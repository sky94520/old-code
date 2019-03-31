package com.datastructure;

import java.io.Serializable;

//静态三岔链表存储节点
public class TriElement implements Serializable
{
	int data;
	int left;
	int right;
	int parent;
	public TriElement(int data)
	{
		this(data,-1,-1,-1);
	}
	public TriElement(int data,int parent,int left,int right)
	{
		this.data=data;
		this.left=left;
		this.right=right;
		this.parent=parent;
	}
	public boolean isLeaf()
	{
		return this.left==-1&&this.right==-1;
	}
	public String toString()
	{
		return new String("("+data+","+parent+","+left+","+right+")");
	}
}
