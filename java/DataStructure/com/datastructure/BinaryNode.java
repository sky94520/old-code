package com.datastructure;

public class BinaryNode<T>
{
	public T data;
	public BinaryNode<T> left;
	public BinaryNode<T> right;
	public BinaryNode()
	{
		this(null,null,null);
	}
	public BinaryNode(T data)
	{
		this(data,null,null);
	}
	public BinaryNode(T data,BinaryNode<T> left,BinaryNode<T> right)
	{
		this.data = data;
		this.left = left;
		this.right = right;
	}
	public boolean isLeaf()
	{
		return this.left==null&&this.right==null;
	}
	public String toString()
	{
		return this.data.toString();
	}
}
