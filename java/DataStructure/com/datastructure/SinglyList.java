package com.datastructure;

public class SinglyList<T> extends Object
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
			this.insert(values[i]);
	}
	//复制构造函数
	public SinglyList(SinglyList<T> list)
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
		rare.next = null;
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
	public boolean equals(Object obj)
	{
		if(this == obj)
			return true;
		if(!(obj instanceof SinglyList))
			return false;
		Node<T> p1 = this.head.next;
		Node<T> p2 = ((SinglyList<T>)obj).head.next;
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
	//实验题
	//begin<end,[0,length)
	public SinglyList<T> remove(int begin,int end)
	{
		if(begin<0||end<0||begin>end)
			throw new IllegalArgumentException("remove(begin,end)参数异常");
		Node<T> front1 = this.head;
		Node<T> front2 = this.head;
		for(int i=0;i<end&&front2.next!=null;i++)
		{
			if(i<begin)
			{
				front1 = front1.next;
			}
			front2 = front2.next;
		}
		Node<T> p = front1.next;
		SinglyList<T> list = new SinglyList<T>();
		list.head.next = p;
		//delete
		front1.next = front2.next;
		//做到真正意义上的割断链表
		front2.next = null;
	
		return list;
	}
	//由于不知道具体用处，所以返回子表是重新构造一个链表
	//即子表的操作不关联母表
/*	public SinglyList<T> subList(int begin,int end)
	{
		if(begin<0||end<0||begin>end)
			throw new IllegalArgumentException("subList(begin,end)参数异常");
		Node<T> p = this.head.next;
		for(int i = 0;i<begin&&p!=null;i++)
			p=p.next;
		for(int i=begin;i<end&&p!=null;i++)
		{

			p = p.next;
		}
	}
	//返回是否包含子集
/*	public boolean contains(SinglyList<T> list)
	{
		Node<T> p1 = this.head.next;
		Node<T> p2 = list.head.next;
		boolean isContain = false;
		
		for(;p1!=null&&!isContain;p1=p1.next)
		{
			for(p2=list.head.next;p2!=null;p2=p2.next)
			{
			}
		}
	}*/
}
