public class GenNode<T>
{
	public T data;
	//子表
	public GenList<T> child;
	//后继节点地址域
	public GenNode<T> next;

	public GenNode()
	{
		this(null,null,null);
	}
	public GenNode(T data)
	{
		this(data,null,null);
	}
	public GenNode(T data,GenList<T> child,GenNode<T> next)
	{
		this.data = data;
		this.child = child;
		this.next = next;
	}
	public String toString()
	{
		return this.data.toString();
	}
}
