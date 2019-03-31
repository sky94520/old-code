package com.datastructure;

import java.util.Iterator;

public class SinglyList<T> implements Iterable<T>
{
	protected Node<T> head;
	public SinglyList()
	{
		this.head = new Node<T>();
	}
	public SinglyList(T values[])
	{
		this();
		Node<T> p = this.head;
		Node<T> rare = null;
		for(int i = 0;i < values.length;i++)
		{
			rare = new Node<T>(values[i],null);
			p.next = rare;
			p = rare;
		}
	}
	//复制构造函数
	public SinglyList(SinglyList<T> list)
	{
		this();
		Node<T> p = this.head;
		Node<T> rare = null;
		//已存在链表
		Node<T> pList = list.head.next;
		while(pList != null)
		{
			rare = new Node<T>(pList.data,null);
			p.next = rare;
			p = rare;

			pList = pList.next;
		}
	}
	//增加容错机制。很不错的代码
	public Node<T> insert(int i,T x)
	{
		if(x == null)
			throw new java.lang.NullPointerException("x == null");
		Node<T> front = this.head;
		for(int j = 0;front.next != null && j < i;j++)
			front = front.next;
		front.next = new Node<T>(x,front.next);
		return front.next;
	}
	//默认尾插入
	public Node<T> insert(T x)
	{
		return insert(Integer.MAX_VALUE,x);
	}
	//delete
	public Node<T> search(T x)
	{
		Node<T> p = this.head.next;
		while(p != null)
		{
			if(x.equals(p.data))
				return p;
			p = p.next;
		}
		return p;
	}
	public boolean contains(T x)
	{
		Node<T> t = this.head.next;
		while(t != null)
		{
			if(t.data.equals(x))
				return true;
			t = t.next;
		}
		return false;
	}
	//尾插入
	public Node<T> insertDifferent(T x)
	{
		Node<T> front = this.head;
		while(front.next != null)
		{
			if(front.next.data.equals(x))
				return null;
			front = front.next;
		}
		front.next = new Node<T>(x,null);
		return front.next;
	}
	//移除区间[0,length)
	public T remove(int i)
	{
		Node<T> front = this.head;

		for(int j = 0;front.next != null && j < i;j++)
			front = front.next;
		if(i > 0 && front.next != null)
		{
			T old = front.next.data;
			front.next = front.next.next;
			return old;
		}
		return null;
		
	}
	//移除T x
	public T remove(T x)
	{
		Node<T> front = this.head;
		while(front.next != null)
		{
			if(front.next.data.equals(x))
			{
				T old = front.next.data;
				front.next = front.next.next;
				return old;
			}
			front = front.next;
		}
		return null;
	}
	//增加list，不改变list中的值
	public void addAll(SinglyList<T> list)
	{
		Node<T> p = list.head.next;
		while(p != null)
		{
			//尾插入
			this.insert(p.data);
			p = p.next;
		}
	}
	//delete all
	public void clear()
	{
		this.head = null;
	}
	public boolean isEmpty()
	{
		return this.head.next == null;
	}
	public int size()
	{
		int len = 0;
		Node<T> p = this.head.next;
		while(p != null)
		{
			len++;
			p = p.next;
		}
		return len;
	}
	public String toString()
	{
		Node<T> p = this.head.next;
		StringBuilder str = new StringBuilder();
		while(p != null)
		{
			str.append(p.toString() + " ");
			p = p.next;
		}
		return str.toString();
	}
	public boolean equals(SinglyList<T> t)
	{
		Node<T> p1 = this.head.next;
		Node<T> p2 = t.head.next;

		while(p1 != null && p2 != null)
		{
			if(!p1.data.equals(p2.data))
				return false;
			p1 = p1.next;
			p2 = p2.next;
		}
		//两链表不等长度,return false
		if(p1 != null || p2 != null)
			return false;
		return true;
	}
	@Override
	public Iterator<T> iterator() 
	{
		// TODO Auto-generated method stub
		return new Itr<T>();
	}
	private class Itr<T> implements Iterator<T>
	{
		private Node<T> p;
		public Itr()
		{
			p=(Node<T>) head;
		}
		@Override
		public boolean hasNext() 
		{
			if(p.next==null)
				return false;
			return true;
		}
		@Override
		public T next() 
		{
			p=p.next;
			T data=p.data;
			return data;
		}
		@Override
		public void remove() 
		{
		}
	}
}
