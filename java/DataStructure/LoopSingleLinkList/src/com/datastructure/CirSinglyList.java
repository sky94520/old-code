package com.datastructure;

public class CirSinglyList<T> extends SinglyList<T>
{
	public CirSinglyList()
	{
		this.head = new Node<T>();
		this.head.next = this.head;
	}
	public CirSinglyList(T[] values)
	{
		this();
		Node<T> p = null;
		for(int i = 0;i<values.length;i++)
			this.insert(values[i]);
	}
	//深拷贝
	public CirSinglyList(CirSinglyList<T> list)
	{
		this();
		Node<T> rare = this.head;
		//已存在链表
		Node<T> p = list.head.next;
		while(p != list.head)
		{
			rare.next = new Node<T>(p.data,null);
			rare = rare.next;
			p = p.next;
		}
		rare.next = this.head;
	}
	//覆盖父类的 复制构造函数
	public CirSinglyList(SinglyList<T> list)
	{
		this();
		Node<T> rare = this.head;
		//已存在链表
		Node<T> p = list.head.next;
		while(p != null)
		{
			rare.next = new Node<T>(p.data,null);
			rare = rare.next;
			p = p.next;
		}
		rare.next = this.head;
	}
	//插入，增加容错机制
	public Node<T> insert(int i,T x)
	{
		if(x == null)
			throw new java.lang.NullPointerException("x == null");
		Node<T> front = this.head;
		for(int j = 0;front.next != this.head && j < i;j++)
			front = front.next;
		front.next = new Node<T>(x,front.next);
		return front.next;
	}
	//尾插入
	public Node<T> insert(T x)
	{
		return this.insert(Integer.MAX_VALUE,x);
	}
	public Node<T> search(T x)
	{
		Node<T> p = this.head.next;
		while(p!=this.head)
		{
			if(x.equals(p.data))
				return p;
			p = p.next;
		}
		return null;
	}
	public boolean contains(T x)
	{
		Node<T> p = this.head.next;
		while(p!=this.head)
		{
			if(x.equals(p.data))
				return true;
			p = p.next;
		}
		return false;
	}
	public Node<T> insertDifferent(T x)
	{
		Node<T> front = this.head;
		while(front.next !=this.head)
		{
			if(x.equals(front.next.data))
				return null;
			front = front.next;
		}
		front.next = new Node<T>(x,front.next);
		return front.next;
	}
	//鍖洪棿[0,length)
	public T remove(int i)
	{
		if(i < 0)
			throw new IllegalArgumentException("i<0 i="+i);
		Node<T> front = this.head;
		for(int j=0;j<i&&front.next!=this.head;j++)
			front = front.next;
		if(front.next!=this.head)
		{
			T old = front.next.data;
			front.next = front.next.next;
			return old;
		}
		return null;
	}
	public boolean isEmpty()
	{
		return this.head.next == this.head;
	}
	public int size()
	{
		int len = 0;
		Node<T> p=this.head.next;
		while(p!=this.head)
		{
			len++;
			p=p.next;
		}
		return len;
	}
	public boolean equals(Object obj)
	{
		if(this==obj)
			return true;
		if(!(obj instanceof CirSinglyList))
			return false;
		CirSinglyList<T> list = (CirSinglyList<T>)obj;
		Node<T> p1=this.head.next;
		Node<T> p2=list.head.next;
		while(p1 != this.head && p2!=list.head)
		{
			if(!p1.data.equals(p2.data))
				return false;
			p1 = p1.next;
			p2 = p2.next;
		}
		if(p1 != this.head || p2!=list.head)
			return false;
		return true;
	}
	public String toString()
	{
		StringBuffer buffer = new StringBuffer();
		buffer.append(this.getClass().getName()+"(");
		Node<T> p = this.head.next;
		buffer.append(p.toString());
		p=p.next;
		while(p != this.head)
		{
			buffer.append(","+p.toString());
			p = p.next;
		}
		buffer.append(")");
		return buffer.toString();
	}
	
}
