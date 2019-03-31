package com.datastructure;

public class SortedSeqList<T extends Comparable<? super T> > extends SeqList<T>
{
	public SortedSeqList()
	{
		super();
	}
	public SortedSeqList(int length)
	{
		super(length);
	}
	public SortedSeqList(T[] values)
	{
		super(values.length);
		for(int i = 0; i < values.length;i++)
			this.insert(values[i]);
	}
	//���ƹ��캯��
	public SortedSeqList(SortedSeqList<? extends T> list)
	{
		super(list);
	}
	public SortedSeqList(SeqList<? extends T> list)
	{
		super();
		for(int i = 0;i < list.length;i++)
			this.insert(list.get(i));
	}
	//��˳�����
	public int insert(T x)
	{
		int i = 0;
		if(this.isEmpty() || x.compareTo(this.get(size() - 1)) > 0)
			i = this.length;
		else
			while(i < this.length && x.compareTo(this.get(i)) > 0)
				i++;
		super.insert(i,x);
		return i;
	}
	public int insertDifferent(T x)
	{
		return 1;
	}
	//��֧�ָ���������������������串�ǲ��׳��쳣
	public void set(int i,T x)
	{
		throw new java.lang.UnsupportedOperationException("set(int i,T x)");
	}

	public int insert(int i,T x)
	{
		throw new java.lang.UnsupportedOperationException("insert(int i,T x)");
	}
	public int search(T key)
	{
		for(int i = 0;i < this.length && key.compareTo(this.get(i)) >= 0;i++)
			if(key.compareTo(this.get(i)) == 0)
				return i;
		return -1;
	}
	//������reomve(int i)��ʽ������̳�֮
	public T remove(T key)
	{
		return this.remove(this.search(key));
	}

}
