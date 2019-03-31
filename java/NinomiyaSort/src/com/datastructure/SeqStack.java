package com.datastructure;

import java.util.*;

public final class SeqStack<T> implements Stack<T> 
{
	private SeqList<T> list;
	public SeqStack(int length)
	{
		this.list=new SeqList<T>(length);
	}
	public SeqStack()
	{
		this(64);
	}
	@Override
	public boolean isEmpty()
	{
		// TODO: Implement this method
		return this.list.isEmpty();
	}

	@Override
	public void push(T x)
	{
		// TODO: Implement this method
		this.list.insert(x);
	}

	@Override
	public T peek()
	{
		// TODO: Implement this method
		
		return this.list.get(list.size()-1);
	}

	@Override
	public T pop()
	{
		// TODO: Implement this method
		return list.remove(list.size()-1);
	}
}
