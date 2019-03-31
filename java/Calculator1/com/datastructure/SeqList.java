package com.datastructure;
public class SeqList<T>
{
	protected Object[] element;
	protected int n;
	
	public SeqList(int length)
	{
		this.element = new Object[length];
		this.n = 0;
	}
	public SeqList()
	{
		this(64);
	}
	public SeqList(T[] values)
	{
		this(values.length);
		for(int i = 0;i < values.length;i++)
		this.element[i] = values[i];
		this.n = values.length;
	}
	//深拷贝
	public SeqList(SeqList<? extends T> list)
	{
		this(list.size());
		for(int i=0;i<list.size();i++)
		this.element[i]=list.element[i];
		
		this.n=list.size();
	}
	//判断两顺序表是否相等
	public boolean equals(Object obj)
	{
		if(this==obj)
			return true;
		if(obj instanceof SeqList<?>)
		{
			SeqList<T> list= (SeqList<T>)obj;
			if(this.n == list.n)
			{
				for(int i=0;i<this.n;i++)
				if(!this.get(i).equals(list.get(i)))
					return false;
				return true;
			}
		}
		return false;
	}
	public boolean isEmpty()
	{
		return this.n == 0;
	}
	public int size()
	{
		return this.n;
	}
	public T get(int i)
	{
		if(i >= 0 && i< this.n)
			return (T)this.element[i];
			return null;
	}
	public int insert(int i, T x)
	{
		if(x == null)
			throw new NullPointerException("x == null");
		if(i<0)
			i = 0;
		if(i > this.n)
			i = this.n;
		Object[] source = this.element;
		if(this.n == element.length)
		{
			this.element = new Object[source.length * 2];
			for(int j = 0;j < i;j++)
			this.element[j] = source[j];
		}
		for(int j = this.n - 1; j >= i;j++)
		this.element[j+1] = source[j];
		
		this.element[i] = x;
		this.n++;
		return i;
	}
	//尾插入
	public int insert(T x)
	{
		return this.insert(this.n,x);
	}
	//移出
	public T remove(int i)
	{
		if(this.n > 0 && i>=0&&i<this.n)
		{
			T old = (T)this.element[i];
			for(int j = i;j<this.n-1;j++)
			this.element[j]=this.element[j+1];
			
			this.n--;
			return old;
		}
		return null;
	}
	//删除首次出现的key
	public T remove(T key)
	{
		for(int i=0;i<this.n;i++)
		if(this.element[i].equals(key))
		{
			T old = (T)this.element[i];
			for(int j=i;j<this.n-1;j++)
			this.element[j]=this.element[j+1];
			this.n--;
			return old;
		}
		return null;
	}
	public int search(T key)
	{
		for(int i=0;i<this.n;i++)
		if(key.equals(this.element[i]))
			return i;
		return -1;
	}
	public boolean contains(T key)
	{
		return this.search(key) != -1;
	}
	public void clear()
	{
		this.n=0;
	}
	public void set(int i, T x)
	{
		if(null == x)
			throw new NullPointerException("x == null");
		if(i >= 0 && i < this.n)
			this.element[i] = x;
		else
			throw new java.lang.IndexOutOfBoundsException(i+"");
	}
	public String toString()
	{
		StringBuffer strBuf=new StringBuffer();
		strBuf.append(this.getClass().getName()+"(");

		if(this.n > 0)
			strBuf.append(this.element[0].toString());
		for(int i = 1;i < this.n;i++)
		strBuf.append("," + this.element[i].toString());
		return strBuf.append(")").toString();
	}
}
