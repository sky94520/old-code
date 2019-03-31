package com.datastructure;
/** —≠ª∑À´¡¥±Ì¿‡
 * Date:2015-10-16
 * */
public class CirDoublyList<T> extends Object
{
	private DoubleNode<T> head;
	public CirDoublyList()
	{
		head = new DoubleNode<T>(null,null,null);
		head.prev = head;
		head.next = head;
	}
	public CirDoublyList(T[] values)
	{
		this();
		for(int i = 0;i < values.length;i++)
			this.insert(values[i]);
	}
	public DoubleNode<T> insert(int i,T x)
	{
		if(x == null)
			throw new java.lang.NullPointerException("x = null");
		DoubleNode<T> front = this.head;
		for(int j = 0;j < i&&front.next != this.head;j++)
			front = front.next;
		DoubleNode<T> p = new DoubleNode<T>(x,front,front.next);
		
		front.next.prev = p;
		front.next = p;
		
		return p;
	}
	//Œ≤≤Â»Î
	public DoubleNode<T> insert(T x)
	{
		if(x == null)
			throw new java.lang.NullPointerException("x == null");
		
		DoubleNode<T> p = new DoubleNode<T>(x,this.head.prev,this.head);
		this.head.prev.next = p;
		this.head.prev = p;
		return p;
	}
	public T get(int i)
	{
		if(i <= 0)
			throw new NumberFormatException("i <= 0");
		DoubleNode<T> front = this.head;
		for(int j = 0;j<i&&front.next!=this.head;j++)
		{
			front = front.next;
		}
		if(front.next != this.head)
			return front.data;
		return null;
	}
	public boolean set(int i,T x)
	{
		if(i <= 0)
			throw new NumberFormatException("i <= 0");
		if(x == null)
			throw new NullPointerException("x == null");
		DoubleNode<T> front = this.head;
		for(int j = 0;j<i&&front.next!=this.head;j++)
		{
			front = front.next;
		}
		if(front.next != this.head)
		{
			front.data = x;
			return true;
		}
		return false;
	}
	//“∆≥˝‘™Àÿ
	public T remove(T key)
	{
		if(key == null)
			throw new NullPointerException("x == null");
		DoubleNode<T> front = this.head;
		while(front.next != this.head)
		{
			if(front.next.data.equals(key))
			{
				T old = (T)front.next.data;
				front.next.next.prev = front;
				front.next = front.next.next;
				return old;
			}
			front = front.next;
		}

		return null;
	}
	public boolean contains(T key)
	{
		DoubleNode<T> p = this.head.next;
		while(p != this.head)
		{
			if(p.data.equals(key))
				return true;
			p = p.next;
		}
		return false;
	}
	public void clear()
	{
		this.head.next = this.head;
		this.head.prev = this.head;
	}
	public int size()
	{
		DoubleNode<T> p = this.head.next;
		int i = 0;
		while(p != this.head)
		{
			i++;
			p = p.next;
		}
		return i;
	}
	public boolean isEmpty()
	{
		return this.head == this.head.next;
	}
	public String toString()
	{
		StringBuffer buffer = new StringBuffer();
		buffer.append(this.getClass().getName() + "(");
		
		DoubleNode<T> p = this.head.next;
		if(p != this.head)
		{
			buffer.append(p.toString());
			p = p.next;
		}
		while(p != this.head)
		{
			buffer.append(","+p.toString());
			p = p.next;
		}
		buffer.append(")");
		return buffer.toString();
	}
	
}
