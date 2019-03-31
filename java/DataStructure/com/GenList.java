public class GenList<T>
{
	protected GenNode<T> head;
	public GenList()
	{
		this.head=new GenNode<T>();
	}
	boolean isEmpty()
	{
		return this.head == null;
	}
	public int size()
	{
		return 0;
	}
	public int depth()
	{
		return 0;
	}
	//在主链表插入元素，i容错
	public GenNode<T> insert(int i,T x)
	{
		if(i < 0)
			throw new IllegalArgumentException("insert(int i, T x),i < 0");
		if(x == null)
			return null;

		GenNode<T> front = this.head;
		for(int j=0;j<i&&front.next!=null;j++)
			front = front.next;
		GenNode<T> p = new GenNode<T>(x,null,front.next);
		front.next = p;

		return p;
		
	}
	public GenNode<T> insert(T x)
	{
		return this.insert(Integer.MAX_VALUE,x);
	}
	//在主链表插入子链表   i容错
	//对返回值有点疑问
	public GenNode<T> insert(int i,GenList<T> glist)
	{
		if(i < 0)
			throw new IllegalArgumentException("insert(int i, T x),i < 0");
		if(glist.isEmpty())
			return null;

		GenNode<T> p = this.head.next;
		for(int j=0;j<i&&p!=null;j++)
			p = p.next;
		p.child = glist;

		return p;
	}
	public GenNode<T> insert(GenList<T> glist)
	{
		return this.insert(Integer.MAX_VALUE,glist);
	}
	public void remove(int i)
	{
	}
	public String toString()
	{
		return toString(this.head);
	}
	private String toString(GenNode<T> head)
	{
		GenNode<T> p = head.next;
		StringBuffer buffer = new StringBuffer();

		while(p!=null)
		{
			buffer.append(" "+p);
			if(p.child != null)
				buffer.append("("+toString(p.child.head)+")");
			p=p.next;
		}
		return buffer.toString();
	}
}
