package com.datastructure;

public class SeqList<T> extends Object
{
	protected Object[] element;
	//actual size
	protected int length;
	//
	protected int capacity;
	protected int perAllocSize;
	//default
	public SeqList(int len)
	{
		this.length = 0;

		//this.capacity = (len/this.perAllocSize + 1) * this.perAllocSize;

		this.element = new Object[len];
	}
	public SeqList()
	{
		this(64);
	}
	public SeqList(T[] value)
	{
		this(value.length);
		this.length = value.length;

		for(int i = 0;i < this.length;++i)
		{
			this.element[i] = (Object)value[i];
		}
	}
	//深拷贝 复制构造函数
	public SeqList(SeqList<? extends T> list)
	{
		this.length = list.length;
		this.element = new Object[list.element.length];

		for(int i = 0;i < this.length;i++)
			this.element[i] = (Object)list.element[i];
	}
	public boolean isEmpty()
	{
		return this.length == 0;
	}
	public int size()
	{
		return this.length;
	}
	public T get(int i)
	{
		if(i >= 0 && i < this.length)
			return (T)this.element[i];
		return null;
	}
	/*设置第i个元素，出错抛出异常*/
	public void set(int i,T e)
	{
		//
		if(e == null)
			throw new NullPointerException("x == null");
		if(i >= 0 && i< this.length)
			this.element[i] = (T)e;//e 为引用类型呢？
		else
			throw new java.lang.IndexOutOfBoundsException(i + "");
	}
	public int insert(int i,T e)
	{
		if(e == null)
			throw new NullPointerException("x == null");
		//插入位置i容错，插在最前面
		if(i < 0)
			i = 0;
		//插在最后
		if(i > this.length)
			i = length;
		Object[] source = this.element;
		//若数组满，则扩充顺序表的数组容量
		if(this.length == element.length)
		{
			this.element = new Object[source.length * 2];
		//	System.out.println("数组扩充:length" + this.element.length);
			for(int j = 0;j < i;j++)
				this.element[j] = source[j];
			
		}
		//从i开始至表尾的元素向后移动，次序从后向前
		for(int j = this.length - 1;j >= i;j--)
			this.element[j + 1] = source[j];
		this.element[i] = e;
		this.length++;
		return i;
	}
	//在表尾插入
	public int insert(T e)
	{
		return insert(this.length,e);
	}
	//删除首次出现的与key相等的元素，返回被删除元素，查找不成功时返回null
	public T remove(T key)
	{
		if(key == null)
			throw new NullPointerException("key == null");
		for(int i = 0;i < this.length;i++)
		        if(key.equals((T)this.element[i]))
		        {
				//delete
				T old = (T)this.element[i];
				//元素前移
				for(int j = i;j < this.length;j++)
					this.element[j] = this.element[j + 1];

				this.element[this.length - 1] = null;
				this.length--;
				return old;
			}
		return null;
	}
	public T remove(int i)
	{
		if(this.length > 0 && i >= 0 && i < this.length)
		{
			T old = (T)this.element[i];
			for(int j = i;j < this.length - 1;j++)
				this.element[j] = this.element[j + 1];

			this.element[this.length - 1] = null;
			this.length--;
			return old;
		}
		return null;
	}
	//顺序查找首次出现的与key相等的元素，返回元素序号
	public int search(T key)
	{
		for(int i = 0;i < this.length;i++)
			if(key.equals((T)this.element[i]))
				return i;
		return -1;
	}
	//判断是否包含关键字为key的元素
	public boolean contains(T key)
	{
		return this.search(key) != -1;
	}
	//插入不重复元素，查找不成功时，尾插入
	public int insertDifferent(T key)
	{
		//先遍历一遍，再然后插入
		if(!this.contains(key))
		{
			return this.insert(this.length,key);
		}
		return -1;
	}
	//比较两个顺序表是否相等，覆盖
	public boolean equals(Object obj)
	{
		if(this == obj)
			return true;
		if(obj instanceof SeqList<?>)
		{
			SeqList<T> list = (SeqList<T>)obj;
			if(this.length == list.length)
			{
				for(int i = 0;i < this.length;i++)
					if(!(this.get(i).equals(list.get(i))))
						return false;
				return true;
			}
		}
		return false;
	}
	//在this之后添加list的所有元素。集合并
	public void addAll(SeqList<? extends T> list)
	{
		for(int i = 0;i < list.length;i++)
			this.insert(list.get(i));
	}
	public String toString()
	{
		//返回类名
		String str = /*this.getClass().getName() +*/ "(";
		if(this.length > 0)
			str += this.element[0].toString();
		for(int i = 1;i < this.length;i++)
		{
			//执行T类的toString()方法，运行时多态
			str += "," + this.element[i].toString();
		}
		return str +")";
	}
	public String toPreviousString()
	{
		return "";
	}
}
