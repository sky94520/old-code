package com.datastructure;

import java.util.Iterator;

public class HashMap<K,V> implements Iterable<KeyValue<K,V>>
{
	private HashSet<KeyValue<K,V>> set;
	public HashMap()
	{
		this.set=new HashSet<KeyValue<K,V>>();
	}
	
	public int size()
	{
		return set.size();
	}
	
	public boolean isEmpty() 
	{
		return this.set.isEmpty();
	}
	
	public V put(K key, V value) 
	{
		if(key==null||value==null)
			throw new NullPointerException("key="+key+" value="+value);
		KeyValue<K,V> temp=new KeyValue<K,V>(key,value);
		if(!this.set.add(temp))
			this.set.search(temp).value=value;
		return value;
	}
	public V get(K key) 
	{
		KeyValue<K,V> find=this.set.search(new KeyValue<K,V>(key,null));
		return find==null?null:find.value;
	}
	public boolean containsKey(K key) 
	{
		return this.set.contains(new KeyValue<K,V>(key,null));
	}

	@Override
	public Iterator<KeyValue<K, V>> iterator() 
	{
		return set.iterator();
	}
	/*private class MapIter<K,V> implements Iterator<KeyValue<K, V>>
	{
		private java.util.Iterator<KeyValue<K, V>> iter;
		public MapIter()
		{
			iter= (Iterator<KeyValue<K, V>>)set.iterator();
		}
		@Override
		public boolean hasNext() 
		{
			return iter.hasNext();
		}
		@Override
		public KeyValue<K, V> next() 
		{
			return iter.next();
		}
		@Override
		public void remove() 
		{
		}
	}*/
}
