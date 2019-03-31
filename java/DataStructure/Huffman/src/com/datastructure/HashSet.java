package com.datastructure;

import java.util.Iterator;

public class HashSet<T> implements Iterable<T>
{
	private SinglyList<T>[] table;
	//元素个数
	private int count=0;
	private static final float LOAD_FACTOR=0.75f;
	public HashSet()
	{
		this(16);
	}
	public HashSet(int length)
	{
		//设置最小容量
		if(length<10)
			length=10;
		table=new SinglyList[length];
		//构造空链表
		for(int i=0;i<table.length;i++)
			table[i]=new SinglyList<T>();
	}
	public HashSet(T[] value)
	{
		this(value.length);
		for(int i=0;i<value.length;i++)
			add(value[i]);
	}
	//散列函数 计算关键字为x元素的散列地址，若x==null，抛出异常
	private int hash(T x)
	{
		int key=Math.abs(x.hashCode());
		return key%this.table.length;
	}
	public T search(T key)
	{
		Node<T> find=this.table[hash(key)].search(key);
		return find==null?null:find.data;
	}
	public int size() 
	{
		return this.count;
	}
	
	public boolean isEmpty() 
	{
		return this.count==0;
	}
	public boolean contains(Object obj) 
	{
		T x=(T)obj;
		boolean yes=this.table[hash(x)].contains(x);
		return yes;
	}
	public boolean add(T x) 
	{
		//若散列表满，扩充散列表
		if(this.count>=this.table.length*LOAD_FACTOR)
		{
			//保存原来散列表
			SinglyList<T>[] temp=this.table;
			this.table=new SinglyList[table.length*2];
			for(int i=0;i<table.length;i++)
				table[i]=new SinglyList<T>();
			this.count=0;
			for(int i=0;i<temp.length;i++)
				for(Node<T>p=temp[i].head.next;p!=null;p=p.next)
				{
					add(p.data);
				}
		}
		boolean insert=this.table[hash(x)].insertDifferent(x)!=null;
		if(insert)
			this.count++;
		return insert;
	}
	
	public boolean remove(Object obj)
	{
		T x=(T)obj;
		T e=this.table[hash(x)].remove(x);
		if(e!=null)
			this.count--;
		return e==null;
	}
	public String toString()
	{
		StringBuilder builder=new StringBuilder();
		for(int i=0;i<table.length;i++)
			if(table[i]!=null)
				builder.append("line:"+i+" "+table[i].toString()+"\n");
		return builder.toString();
	}
	@Override
	public Iterator<T> iterator() 
	{
		return new HashSetIter<T>();
	}
	private class HashSetIter<T> implements Iterator<T>
	{
		private Iterator<T> iter;
		private int pInt=0;
		public HashSetIter()
		{
			for(int i=0;i<table.length;i++,pInt++)
				if(table[i]!=null)
				{
					iter=(Iterator<T>) table[i].iterator();
					break;
				}
		}
		@Override
		public boolean hasNext() 
		{
			while(iter.hasNext()==false&&pInt+1<table.length)
			{
				iter=(Iterator<T>) table[++pInt].iterator();
			}
			return iter.hasNext();
		}
		@Override
		public T next() 
		{
			return iter.next();
		}
		@Override
		public void remove() 
		{
		}
	}
}
