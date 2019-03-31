package com.datastructure;

public class TreeNode<T>
{
	public T data;
	//�ڵ���
	public int level;
	public TreeNode<T> parent;
	public TreeNode<T> child;
	public TreeNode<T> sibling;
	
	public TreeNode(T data,int level)
	{
		this(data,level,null,null,null);
	}
	public TreeNode(T data,int level,TreeNode<T> parent,TreeNode<T> child,TreeNode<T> sibling)
	{
		this.data=data;
		this.parent=parent;
		this.child=child;
		this.sibling=sibling;
		this.level=level;
	}
	//�Ƿ���Ҷ��
	public boolean isLeaf()
	{
		return this.child==null;
	}
	public String toString()
	{
		return this.data.toString();
	}
	//�ж��Ƿ����
	public boolean equals(Object obj)
	{
		if(this==obj)
			return true;
		if(obj instanceof TreeNode)
		{
			TreeNode<T> temp=(TreeNode<T>)obj;
			return this.equals(temp);
		}
		return false;
	}
}
