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
	//��� ���ƹ��캯��
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
	/*���õ�i��Ԫ�أ������׳��쳣*/
	public void set(int i,T e)
	{
		//
		if(e == null)
			throw new NullPointerException("x == null");
		if(i >= 0 && i< this.length)
			this.element[i] = (T)e;//e Ϊ���������أ�
		else
			throw new java.lang.IndexOutOfBoundsException(i + "");
	}
	public int insert(int i,T e)
	{
		if(e == null)
			throw new NullPointerException("x == null");
		//����λ��i�ݴ�������ǰ��
		if(i < 0)
			i = 0;
		//�������
		if(i > this.length)
			i = length;
		Object[] source = this.element;
		//����������������˳������������
		if(this.length == element.length)
		{
			this.element = new Object[source.length * 2];
		//	System.out.println("��������:length" + this.element.length);
			for(int j = 0;j < i;j++)
				this.element[j] = source[j];
			
		}
		//��i��ʼ����β��Ԫ������ƶ�������Ӻ���ǰ
		for(int j = this.length - 1;j >= i;j--)
			this.element[j + 1] = source[j];
		this.element[i] = e;
		this.length++;
		return i;
	}
	//�ڱ�β����
	public int insert(T e)
	{
		return insert(this.length,e);
	}
	//ɾ���״γ��ֵ���key��ȵ�Ԫ�أ����ر�ɾ��Ԫ�أ����Ҳ��ɹ�ʱ����null
	public T remove(T key)
	{
		if(key == null)
			throw new NullPointerException("key == null");
		for(int i = 0;i < this.length;i++)
		        if(key.equals((T)this.element[i]))
		        {
				//delete
				T old = (T)this.element[i];
				//Ԫ��ǰ��
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
	//˳������״γ��ֵ���key��ȵ�Ԫ�أ�����Ԫ�����
	public int search(T key)
	{
		for(int i = 0;i < this.length;i++)
			if(key.equals((T)this.element[i]))
				return i;
		return -1;
	}
	//�ж��Ƿ�����ؼ���Ϊkey��Ԫ��
	public boolean contains(T key)
	{
		return this.search(key) != -1;
	}
	//���벻�ظ�Ԫ�أ����Ҳ��ɹ�ʱ��β����
	public int insertDifferent(T key)
	{
		//�ȱ���һ�飬��Ȼ�����
		if(!this.contains(key))
		{
			return this.insert(this.length,key);
		}
		return -1;
	}
	//�Ƚ�����˳����Ƿ���ȣ�����
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
	//��this֮�����list������Ԫ�ء����ϲ�
	public void addAll(SeqList<? extends T> list)
	{
		for(int i = 0;i < list.length;i++)
			this.insert(list.get(i));
	}
	public String toString()
	{
		//��������
		String str = /*this.getClass().getName() +*/ "(";
		if(this.length > 0)
			str += this.element[0].toString();
		for(int i = 1;i < this.length;i++)
		{
			//ִ��T���toString()����������ʱ��̬
			str += "," + this.element[i].toString();
		}
		return str +")";
	}
	public String toPreviousString()
	{
		return "";
	}
}
