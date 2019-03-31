package com.datastructure;
//双链表的节点
public class DoubleNode<T>
{
	public T data;
	public DoubleNode<T> prev,next;

	public DoubleNode()
	{
		this(null,null,null);
	}
	public DoubleNode(T data)
	{
		this(data,null,null);
	}
	public DoubleNode(T data,DoubleNode<T> prev,DoubleNode<T> next)
	{
		this.data = data;
		this.prev = prev;
		this.next = next;
	}
	public String toString()
	{
		return this.data.toString();
	}
}
