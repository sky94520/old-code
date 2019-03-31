package com.datastructure;
public final class SeqQueue<T> implements Queue<T>
{
	private Object[] element;
	//模拟引用
	private int m_nHead;
	private int m_nTail;
	
	public SeqQueue()
	{
		this(64);
	}
	public SeqQueue(int length)
	{
		if(length < 64)
			length = 64;
		this.element = new Object[length];
		//初始化队列为空
		this.m_nHead = this.m_nTail = 0;
	}
	public boolean isEmpty()
	{
		return this.m_nHead == this.m_nTail;
	}
	public boolean add(T x)
	{
		if(x == null)
			return false;
		//如果队列满了，则扩充
		if(this.m_nHead == (this.m_nTail + 1)%this.element.length)
		{
			Object[] temp = this.element;
			this.element = new Object[temp.length * 2];
			//从head开始赋值
			int j = 0;
			for(int i = this.m_nHead;i != this.m_nTail;i = (i+1)%temp.length)
				this.element[j++] = temp[i];
			this.m_nHead = 0;
			this.m_nTail = j;
		}
			this.element[this.m_nTail] = x;
			this.m_nTail = (this.m_nTail + 1)%this.element.length;
			return true;
	}
	public T peek()
	{
		return this.isEmpty() == true?null:(T)this.element[this.m_nHead];
	}
	public T poll()
	{
		if(this.isEmpty())
			return null;
		T old = (T)this.element[m_nHead];
		
		this.m_nHead = (this.m_nHead + 1)%this.element.length;
		return old;
	}
}
