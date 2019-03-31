package com.datastructure;

public class Node<T> extends Object
{
	//save data
	public T data;
	public Node<T> next;
	public Node()
	{
		this(null,null);
	}
	public Node(T data,Node<T> next)
	{
		this.data = data;
		this.next = next;
	}
	public boolean equals(Object obj)
	{
		if(this == obj)
			return true;
		if(obj instanceof Node<T>)
		{
			return this.data.equals(((Node<T>)obj).data);
		}
		return false;
	}
	public String toString()
	{
		if(data == null)
			return null;
		return this.data.toString();
	}
}
