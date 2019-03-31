package com.datastructure;

public class KeyValue<K,V>
{
	K key;
	V value;
	public KeyValue()
	{
		this(null,null);
	}
	public KeyValue(K key,V value)
	{
		this.key=key;
		this.value=value;
	}
	public int hashCode()
	{
		return this.key.hashCode();
	}
	public K key()
	{
		return this.key;
	}
	public V value()
	{
		return this.value;
	}
	public boolean equals(Object obj)
	{
		return this==obj||obj instanceof KeyValue<?,?>&&this.key.equals(((KeyValue<K,V>)obj).key);
	}
	public String toString()
	{
		return "key:"+this.key+" value:"+this.value;
	}
}
