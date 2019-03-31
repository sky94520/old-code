package com.datastructure;

public class LinkedQueue<T> implements Queue<T>
{
	private Node<T> head;
	private Node<T> tail;
	
	public LinkedQueue()
	{
		this.head = this.tail = null;
	}
	public  boolean isEmpty()
	{
		return this.head == null && this.tail == null;
	}
	public  boolean add(T x)
	{
		if(x == null)
			return false;
		Node<T> p = new Node<T>(x,null);
		//
		if(this.head == null)
			this.head = p;
		else
			this.tail.next = p;
		this.tail = p;
		
		return true;
	}
	public  T peek()
	{
		return this.isEmpty() == true?null:this.tail.data;
	}
	public  T poll()
	{
		if(this.isEmpty())
		return null;
		T temp = this.head.data;
		head = head.next;
		if(this.head == null)
			this.tail = null;
		return temp;
	}
}
